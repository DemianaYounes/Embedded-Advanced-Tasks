/*
 * FlappyBird_Private.h
 *
 * Created: 11/8/2024 4:34:46 AM
 *  Author: Demiana Younes
 */ 


#ifndef FLAPPYBIRD_PRIVATE_H_
#define FLAPPYBIRD_PRIVATE_H_

/**
* @brief Callback for external interrupt 0 (INT0).
*
* Decreases the bird's vertical position (makes it "fly up") when the interrupt is triggered.
* Ensures the bird does not move out of bounds (below the top of the screen).
*/
static void CallBack_INT0(void);
/**
 * @brief Callback for external interrupt 1 (INT1).
 * 
 * Resets the game score and prepares the game to start over.
 */
static void CallBack_INT1(void);
/**
 * @brief Callback for Timer1 Compare Match interrupt.
 * 
 * Adds an event to the queue every 1 second.
 * This function is called periodically based on timer settings.
 */
static void CallBack_Timer1(void);
/**
 * @brief Updates the bird's position on the GLCD based on its speed.
 * 
 * This function handles the movement of the bird, including jumping and falling.
 * 
 * @param Copy_u8Iterator Current X-coordinate of the bird on the screen.
 * @param Local_u8BirdSpeed Speed factor for bird movement.
 */
static void FlappyBird_voidMovementBird(u8 Copy_u8Iterator,u8 Local_u8BirdSpeed);
/**
* @brief Displays a waiting message until the user presses a button.
*
* This function is called when the game is paused, indicating that the user
* needs to press a button to continue or restart the game.
*/
static void FlappyBird_voidPressButtonWaiting(void);
/**
 * @brief Starts the game loop for Flappy Bird.
 * 
 * Handles game mechanics such as bird movement, obstacle updates, and collision detection.
 * Continuously updates the game state until a game-over condition is met.
 */
static void FlappyBird_voidStartGame(void);
/**
 * @brief Displays the game over screen.
 * 
 * Clears the screen and shows a sad face along with the final score.
 * Waits for user input to restart the game.
 * 
 * @return u8 Returns 0 after displaying the game over screen.
 */
static u8 FlappyBird_voidGameOver(void);
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
static u8 FlappyBird_CheckObstacles2(u8 Copy_u8Start,u8 Copy_u8End ,u8 Copy_u8Iterator,u8 Copy_u8Part);
/**
 * @brief Resets the positions of the obstacles to their initial values.
 * 
 * This function resets the starting and ending positions of the obstacles
 * and adjusts their heights for the next game round.
 */
static void FlappyBird_ResetObstacles(void);
/**
 * @brief Clears the current obstacles from the GLCD.
 * 
 * This function removes the obstacles from the display, preparing for the next frame.
 */
static void FlappyBird_ClearObstacles(void);
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
static u8 FlappyBird_CheckObstacles(u8 Copy_u8Offest, u8 Copy_u8birdX);
/**
 * @brief Calculates the bird's speed and updates it over time.
 * 
 * This function computes the current speed of the bird, starting at a set value and
 * gradually increasing it as the game progresses. The speed is adjusted using fixed-point
 * arithmetic to maintain precision during calculations.
 * 
 * @return u8 Returns the current bird speed as an 8-bit unsigned integer.
 */
static u8 FlappyBird_voidBirdSpeed(void);
/**
 * @brief Updates the positions of obstacles on the screen.
 * 
 * This function handles the movement of obstacles from right to left and clears previous positions.
 * 
 * @param Copy_u8Offest Current offset applied to obstacle positions.
 */
static void FlappyBird_voidUpdateObstcales(u8 Copy_u8Offest);


#endif /* FLAPPYBIRD_PRIVATE_H_ */