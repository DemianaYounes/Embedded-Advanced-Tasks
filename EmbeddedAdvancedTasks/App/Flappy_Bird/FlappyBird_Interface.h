/*
 * FlappyBird_Interface.h
 *
 * Created: 11/8/2024 4:34:33 AM
 *  Author: Demiana Younes
 */ 


#ifndef FLAPPYBIRD_INTERFACE_H_
#define FLAPPYBIRD_INTERFACE_H_

/**
 * @brief Initializes the Flappy Bird game environment.
 * 
 * This function sets up all necessary components for the game, including:
 * - Configuring the digital I/O pins for inputs and outputs.
 * - Setting up external interrupts for user inputs (jump and restart).
 * - Initializing the timer for timing events.
 * - Clearing and preparing the graphical LCD (GLCD) for display.
 * - Enabling global interrupts and setting up the game state stack.
 * 
 * After calling this function, the game is ready to start and respond to user inputs.
 */
void FlappyBird_voidInit(void);

/**
 * @brief Main game loop for the Flappy Bird game.
 * 
 * Manages the current game state and transitions between states based on user input and game events.
 * The loop continuously checks if the game is paused or running and updates the state accordingly.
 */
void FlappyBird_voidRunnable(void);

#endif /* FLAPPYBIRD_INTERFACE_H_ */