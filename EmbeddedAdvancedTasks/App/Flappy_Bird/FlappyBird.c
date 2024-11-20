/*
 * FlappyBird.c
 *
 * Created: 11/8/2024 4:34:19 AM
 *  Author: Demiana Younes
 */ 

#define F_CPU   8000000
#include "avr/delay.h"
#include "StdTypes.h"
#include "Utils.h"
#include "MemMap.h"

#include "DIO_Interface.h"

#include "Ex_Interrupt_Interface.h"
#include "Timer_Interface.h"
#include "Graphical_LCD_Interface.h"

#include "FixedPoint_Interface.h"

#include "Stack_Interface.h" 
#include "Queue_Interface.h"

#include "FlappyBird_Interface.h"
#include "FlappyBird_Private.h"
#include "FlappyBird_Config.h"



// Global variables
static volatile s8 BirdFlag = START_PAGE_FOR_BIRD; // Current vertical position of the bird
static volatile u8 Flag = 0; // Flag to indicate a jump action
static volatile u8 PauseStartFlag = PAUSE_VALUE; // Flag to control game pause and start
static volatile u16 ObstacleStart[4] = {50, 90, 80, 100}; // Starting positions of the obstacles
static volatile u16 ObstacleEnd[4] = {70, 100, 90, 110}; // Ending positions of the obstacles
static volatile u8 ObstacleTop[2] = {6, 2}; // Heights of the obstacles
static volatile u8 TotalScore = 0; // Player's score

extern void(*currentState)(void); // Pointer to the current game state function
CircularQueue_type Queue; // Queue for managing game events

/**
 * @brief Callback for external interrupt 0 (INT0).
 * 
 * Decreases the bird's vertical position (makes it "fly up") when the interrupt is triggered.
 * Ensures the bird does not move out of bounds (below the top of the screen).
 */
static void CallBack_INT0()
{
    BirdFlag--; // Move bird up
    if (BirdFlag < 0)
    {
        BirdFlag = 0; // Keep bird within screen bounds
    }
    Flag = 1; // Set jump flag
}

/**
 * @brief Callback for external interrupt 1 (INT1).
 * 
 * Resets the game score and prepares the game to start over.
 */
static void CallBack_INT1()
{
    TotalScore = 0; // Reset the score
    PauseStartFlag = 5; // Set the flag to indicate game start
    Stack_Pop(); // Pop the current state from the stack
}

/**
 * @brief Callback for Timer1 Compare Match interrupt.
 * 
 * Adds an event to the queue every 1 second.
 * This function is called periodically based on timer settings.
 */
static void CallBack_Timer1()
{
    static u8 Local_u8Counter = 0; // Counter for timing events
    if (Local_u8Counter == 3)
    {
        Enqueue(&Queue, 1); // Add an event to the queue
        Local_u8Counter = 0; // Reset counter
    }
    Local_u8Counter++; // Increment counter
}

/**
 * @brief Initializes the Flappy Bird game environment.
 * 
 * Configures peripherals such as GPIO, interrupts, timers, and the graphical LCD (GLCD).
 * Initializes data structures and sets the initial game state.
 */
void FlappyBird_voidInit()
{
    DIO_Init(); // Initialize the digital I/O
    EXI_TriggerEdge(EX_INT0, FALLING_EDGE); // Configure external interrupt 0
    EXI_TriggerEdge(EX_INT1, FALLING_EDGE); // Configure external interrupt 1
    EXI_SetCallBack(EX_INT0, CallBack_INT0); // Set callback for INT0
    EXI_SetCallBack(EX_INT1, CallBack_INT1); // Set callback for INT1
    Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE, TIMER1_SCALER_64); // Initialize Timer1
    Timer1_OCRA1Mode(OCRB_NON_INVERTING); // Set output compare mode
    OCR1A = 124999; // Set Timer1 to trigger every 1 second
    Timer1_OCA_SetCallBack(CallBack_Timer1); // Set Timer1 callback
    GLCD_voidInit(); // Initialize the graphical LCD
    sei(); // Enable global interrupts
    EXI_Enable(EX_INT0); // Enable external interrupt 0
    EXI_Enable(EX_INT1); // Enable external interrupt 1
    Timer1_OCA_InterruptEnable(); // Enable Timer1 interrupt
    CircularQueue_Init(&Queue); // Initialize the queue
    Stack_Push(FlappyBird_voidGameOver); // Push game over state onto the stack
    Stack_Push(FlappyBird_voidStartGame); // Push start game state onto the stack
}

/**
 * @brief Main game loop for the Flappy Bird game.
 * 
 * Manages the current game state and transitions between states based on user input and game events.
 * The loop continuously checks if the game is paused or running and updates the state accordingly.
 */
void FlappyBird_voidRunnable()
{
    while (1)
    {
        if (READ_BIT(PauseStartFlag, 0) == 1) // Check if game is running
        {
            if (currentState != NULL) // If a state function is set
            {
                currentState(); // Call the current state function
            }
            else
            {
                /* Do Nothing */
            }
        }
        else
        {
            FlappyBird_voidPressButtonWaiting(); // Display waiting message
        }
    }
}


/**
 * @brief Starts the game loop for Flappy Bird.
 * 
 * Handles game mechanics such as bird movement, obstacle updates, and collision detection.
 * Continuously updates the game state until a game-over condition is met.
 */
static void FlappyBird_voidStartGame()
{
    u8 Local_u8Iterator, Local_u8GameOver = 0;
    u8 Local_u8Offest = 0; // Offset for obstacles
    u8 Local_u8StartCounter = 0; // Counter for game state
    u8 Local_u8BirdSpeed = 0; // Speed of the bird
    GLCD_voidClear(); // Clear the GLCD for a fresh frame
    while (READ_BIT(PauseStartFlag, 2) == START_VALUE) // Continue while game is active
    {   
        Local_u8BirdSpeed = FlappyBird_voidBirdSpeed(); // Get current bird speed
        if (IsEmpty(&Queue) != QUEUE_EMPTY) // Check if there are events in the queue
        {
            DeQueue(&Queue, &Local_u8StartCounter); // Dequeue the next event
        }
        if (Local_u8StartCounter == 1) // If a new game event is triggered
        {
            FlappyBird_ClearObstacles(); // Clear existing obstacles
            FlappyBird_ResetObstacles(); // Reset obstacle positions
            FlappyBird_voidUpdateObstcales(0); // Update obstacle positions
            Local_u8StartCounter = 0; // Reset start counter
        }
        Local_u8Offest = 0; // Reset offset for obstacles
        for (Local_u8Iterator = 1; Local_u8Iterator < 128; Local_u8Iterator++) // Loop through screen width
        {
            if (Local_u8Iterator % 30 == 0) // Check if it's time to update obstacles
            {
                Local_u8Offest += 10; // Increment offset
                FlappyBird_voidUpdateObstcales(Local_u8Offest); // Update obstacles
                TotalScore++; // Increment score
            }
            Local_u8GameOver = FlappyBird_CheckObstacles(Local_u8Offest, Local_u8Iterator); // Check for collisions
            if (Local_u8GameOver == 1) // If a collision occurs
            {
                CLR_BIT(PauseStartFlag, 2); // Set flag to indicate game over
                break; // Exit the loop
            }
            FlappyBird_voidMovementBird(Local_u8Iterator, Local_u8BirdSpeed); // Move the bird
        }
        GLCD_voidClearDot(BirdFlag, Local_u8Iterator); // Clear the bird's previous position
        if (Local_u8GameOver == 1) // If game over
        {
            SET_BIT(PauseStartFlag, 1); // Set the pause flag
            Stack_Pop(); // Pop the current state
            Stack_Push(FlappyBird_voidGameOver); // Push game over state onto the stack
            Stack_Push(FlappyBird_voidStartGame); // Push start game state onto the stack
            break; // Exit the game loop
        }
    }    
}

/**
 * @brief Updates the positions of obstacles on the screen.
 * 
 * This function handles the movement of obstacles from right to left and clears previous positions.
 * 
 * @param Copy_u8Offest Current offset applied to obstacle positions.
 */
static void FlappyBird_voidUpdateObstcales(u8 Copy_u8Offest)
{
    ObstacleStart[0] += 10;
    ObstacleEnd[0] += 10; 
    GLCD_voidClearBox((ObstacleStart[0] - 10) % 127, (ObstacleEnd[0] - 10) % 127, ObstacleTop[0], 7);
    GLCD_voidDrawBox((ObstacleStart[0] % 127), (ObstacleEnd[0] % 127), ObstacleTop[0], 7); 

    ObstacleStart[2] += 10; 
    ObstacleEnd[2] += 10; 
    GLCD_voidClearBox((ObstacleStart[2] - 10) % 127, (ObstacleEnd[2] - 10) % 127, 0, ObstacleTop[1]);
    GLCD_voidDrawBox((ObstacleStart[2] % 127), (ObstacleEnd[2] % 127), 0, ObstacleTop[1]); 
  
    ObstacleStart[1] += 10; 
    ObstacleEnd[1] += 10;  
    GLCD_voidClearBox((ObstacleStart[1] - 10) % 127, (ObstacleEnd[1] - 10) % 127, ObstacleTop[0], 7); 
    GLCD_voidDrawBox((ObstacleStart[1] % 127), (ObstacleEnd[1] % 127), ObstacleTop[0], 7);
	
    ObstacleStart[3] += 10; 
    ObstacleEnd[3] += 10; 
    GLCD_voidClearBox((ObstacleStart[3] - 10) % 127, (ObstacleEnd[3] - 10) % 127, 0, ObstacleTop[1]); 
    GLCD_voidDrawBox((ObstacleStart[3] % 127), (ObstacleEnd[3] % 127), 0, ObstacleTop[1]);
}

/**
 * @brief Updates the bird's position on the GLCD based on its speed.
 * 
 * This function handles the movement of the bird, including jumping and falling.
 * 
 * @param Copy_u8Iterator Current X-coordinate of the bird on the screen.
 * @param Local_u8BirdSpeed Speed factor for bird movement.
 */
static void FlappyBird_voidMovementBird(u8 Copy_u8Iterator, u8 Local_u8BirdSpeed)
{
    GLCD_voidPrintBird(BirdFlag, Copy_u8Iterator); // Print the bird at its current position
    _delay_ms(2); // Delay for rendering
    GLCD_voidClearDot(BirdFlag, Copy_u8Iterator - 1); // Clear the bird's previous position
    if (Copy_u8Iterator % Local_u8BirdSpeed == 0) // Check if it's time to move the bird down
    {
        GLCD_voidClearBird(BirdFlag, Copy_u8Iterator); // Clear the bird's current position
        BirdFlag++; // Move the bird down
        if (BirdFlag > 7) // Ensure the bird doesn't go off the screen
        {
            BirdFlag = 7; // Limit to the maximum height
        }
    }
    if (Flag == 1) // If a jump was triggered
    {
        GLCD_voidClearBird(BirdFlag + 1, Copy_u8Iterator - 1); // Clear the bird's next position
        Flag = 0; // Reset jump flag
    }
}

/**
 * @brief Checks for collisions between the bird and obstacles.
 * 
 * This function iterates through all obstacles and checks if the bird's position
 * intersects with any obstacle.
 * 
 * @param Copy_u8Offest Current offset applied to obstacle positions.
 * @param Copy_u8birdX Current X-coordinate of the bird.
 * @return u8 Returns 1 if there is a collision, 0 otherwise.
 */
static u8 FlappyBird_CheckObstacles(u8 Copy_u8Offest, u8 Copy_u8birdX)
{
    u8 Local_u8Iterator, Local_u8GameOver = 0; // Local variables for iteration and game over status
    for (Local_u8Iterator = 0; Local_u8Iterator < 4; Local_u8Iterator++) // Check each obstacle
    {
        Local_u8GameOver = FlappyBird_CheckObstacles2((ObstacleStart[Local_u8Iterator] % 127), (ObstacleEnd[Local_u8Iterator] % 127), Copy_u8birdX, Local_u8Iterator);
        if (Local_u8GameOver == 1) // If a collision is detected
        {
            break; // Exit the loop
        }
    }
    return Local_u8GameOver; // Return collision status
}

/**
 * @brief Resets the positions of the obstacles to their initial values.
 * 
 * This function resets the starting and ending positions of the obstacles
 * and adjusts their heights for the next game round.
 */
static void FlappyBird_ResetObstacles()
{
    static u8 ObstacleReset = 0; // Static variable to track obstacle resetting
    // Reset obstacle positions
    ObstacleStart[0] = 0; ObstacleEnd[0] = 10 + ObstacleReset;
    ObstacleStart[1] = 50; ObstacleEnd[1] = 60 + ObstacleReset;
    ObstacleStart[2] = 70; ObstacleEnd[2] = 80 + ObstacleReset;
    ObstacleStart[3] = 10; ObstacleEnd[3] = 20 + ObstacleReset;
    ObstacleTop[0] = 5; ObstacleTop[1] = 2; // Set obstacle heights
    ObstacleReset += 5; // Increment reset value
    if (ObstacleReset >= 25) // Reset condition
    {
        ObstacleReset = 0; // Reset the obstacle reset value
    }
}

/**
 * @brief Clears the current obstacles from the GLCD.
 * 
 * This function removes the obstacles from the display, preparing for the next frame.
 */
static void FlappyBird_ClearObstacles()
{
    // Clear each obstacle from the display
    GLCD_voidClearBox((ObstacleStart[0]) % 127, (ObstacleEnd[0]) % 127, ObstacleTop[0], 7);
    GLCD_voidClearBox((ObstacleStart[1]) % 127, (ObstacleEnd[1]) % 127, ObstacleTop[0], 7);
    GLCD_voidClearBox((ObstacleStart[2]) % 127, (ObstacleEnd[2]) % 127, 0, ObstacleTop[1]);
    GLCD_voidClearBox((ObstacleStart[3]) % 127, (ObstacleEnd[3]) % 127, 0, ObstacleTop[1]);
}

/**
 * @brief Displays the game over screen.
 * 
 * Clears the screen and shows a sad face along with the final score.
 * Waits for user input to restart the game.
 * 
 * @return u8 Returns 0 after displaying the game over screen.
 */
static u8 FlappyBird_voidGameOver()
{
    GLCD_voidClear(); // Clear the GLCD
    GLCD_voidDrawSadFace(20, 1); // Draw a sad face
    GLCD_voidWriteString(1, 70, "Game Over"); // Display "Game Over"
    GLCD_voidWriteString(3, 60, "Total Score"); // Display "Total Score"
    GLCD_voidWriteString(4, 60, "="); // Display "="
    GLCD_voidWriteNumber(4, 70, TotalScore); // Display the final score
    while (READ_BIT(PauseStartFlag, 1) == 1) // Wait for user to restart
    {
        GLCD_voidCryMoving(20, 3); // Animate the sad face
        BirdFlag = 3; // Reset bird position
        _delay_ms(20); // Delay for animation
    }
    return 0; // Return after game over screen
}

/**
 * @brief Checks for specific collisions between the bird and obstacles.
 * 
 * This function determines if the bird's position intersects with any of the obstacles based on
 * the bird's height and the obstacle's height.
 * 
 * @param Copy_u8Start Start position of the obstacle.
 * @param Copy_u8End End position of the obstacle.
 * @param Copy_u8Iterator Current X-coordinate of the bird.
 * @param Copy_u8Part Part index of the obstacle being checked.
 * @return u8 Returns 1 if there is a collision, 0 otherwise.
 */

static u8 FlappyBird_CheckObstacles2(u8 Copy_u8Start,u8 Copy_u8End ,u8 Copy_u8Iterator,u8 Copy_u8Part)
{
	u8 Local_u8Status=0;
	if( ((BirdFlag>=ObstacleTop[0] && Copy_u8Part<2) || (BirdFlag<=ObstacleTop[1] && Copy_u8Part>=2)) && (Copy_u8Iterator>=Copy_u8Start && Copy_u8Iterator<=Copy_u8End) )
	{
		Local_u8Status=1;
	}
	return Local_u8Status;
}

/**
 * @brief Displays a waiting message until the user presses a button.
 * 
 * This function is called when the game is paused, indicating that the user
 * needs to press a button to continue or restart the game.
 */
static void FlappyBird_voidPressButtonWaiting()
{
	GLCD_voidWriteString(1,40,"Press to start");
	GLCD_voidBigBirdMoving(20,3);
}


/**
 * @brief Calculates the bird's speed and updates it over time.
 * 
 * This function computes the current speed of the bird, starting at a set value and
 * gradually increasing it as the game progresses. The speed is adjusted using fixed-point
 * arithmetic to maintain precision during calculations.
 * 
 * @return u8 Returns the current bird speed as an 8-bit unsigned integer.
 */
static u8 FlappyBird_voidBirdSpeed()
{
    static float Local_BirdSpeed = 3.5; // Initial speed of the bird
    static u8 Local_u8IncreaseValue = 10; // Incremental value for speed increase
    u32 Local_u8BirdSpeed; // Variable to store the computed bird speed

    // Subtract a fraction of the increase value from the current bird speed
    Local_u8BirdSpeed = FixedPoint_Subtraction(Local_BirdSpeed, ((float)Local_u8IncreaseValue / 100.0));
    
    // Convert the speed to an appropriate format for the game
    Local_u8BirdSpeed = FixedPoint_ConvertFixedPointToFloatMultipleInTen(Local_u8BirdSpeed);
    
    // Increase the increase value for the next speed computation
    Local_u8IncreaseValue += 10;

    return Local_u8BirdSpeed; // Return the computed bird speed
}

