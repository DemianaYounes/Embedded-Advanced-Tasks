# Embedded-Advanced-Tasks

This repository focuses on evaluating different tasks related to the performance, memory usage, and precision for embedded systems. Each task compares two or more methods for solving a specific problem.

## Task 1: Traffic light controller using a stack based state machine
This project implements a traffic light system using three LEDs (green, yellow, and red) on an ATmega32 microcontroller. The stack-based state machine is managed via Timer1 in CTC mode to control the light transitions based on traffic rules.

<img src="https://github.com/user-attachments/assets/ceba3574-69ee-4328-9a69-fa5f74c28f57" alt="Traffic Light" width="800" height="400"/>

## State Machine Designs
### 1. Switch Case State Machine
### Pros:
- **Simplicity:** The switch-case structure is straightforward and easy to understand for simple state machines.
- **Directness:** Clear visibility of the state and event handling logic within the same structure.
- **Ease of Debugging**: Debugging can be simpler because all state logic is located in one place.
### Cons:
- **Scalability:** As the number of states and events increases, the nested switch statements become cumbersome and hard to maintain.
- **Monolithic Structure:** All logic is contained within a single structure, making code difficult to navigate and modify.
- **Limited Flexibility:** Changing state transitions or events requires modifying the code, which can introduce errors.
## 2. Table of Pointers to Functions
### Pros:
- **Modularity:** The logic is separated into functions, which enhances code organization and readability.
- **Dynamic Transitions:** Easier to change state transitions by modifying the table rather than the code itself.
- **Scalability:** Handles larger state machines better as the table can accommodate more states and events without becoming unwieldy.
### Cons:
- **Complexity in Implementation:** Initial setup requires more code and understanding of function pointers.
- **Indirect Control Flow:** Can be harder to trace through the execution flow, as it involves jumping to different functions rather than following a linear path.
- **Memory Overhead:** Requires additional memory to store the function pointer table.
## 3. Stack-Based State Machine
### Pros:
- **Dynamic State Management:** Supports multiple states and sub-states, allowing for more complex behavior without cluttering the code.
- **Better Readability:** Reduces code size and improves readability by managing states with a stack.
- **Reusability:** States can be reused across different contexts, and the stack allows for easy transitions between states.
### Cons:
- **Overhead of Stack Management:** Requires careful management of the stack to ensure correct state transitions, which can complicate implementation.
- **Potential for Stack Overflow:** If the stack grows too large due to too many nested states, it can lead to overflow issues.
- **Complex Debugging:** Tracing through a stack-based state machine can be more challenging, especially with many nested states.
## Practical (Output)
- **Red Led**
 <img src="https://github.com/user-attachments/assets/d5ef5464-fbd4-476e-8bc3-12b951725ce4" alt="Traffic Light" width="600" height="300"/>
 
- **Yellow Led**
 <img src="https://github.com/user-attachments/assets/0b659254-b564-45f5-80ef-e53f1f85bcd0" alt="Traffic Light" width="600" height="300"/>

- **Green Led**
 <img src="https://github.com/user-attachments/assets/fd4ef7c0-268c-4347-b7de-234b42021828" alt="Traffic Light" width="600" height="300"/>

## Task 2: Using Fixed-Point Math for Floating-Point Operations
In this task, we use fixed-point math to handle floating-point operations such as addition, subtraction, multiplication, and division. Fixed-point arithmetic offers several advantages in terms of speed, memory usage, and predictability, particularly in systems where floating-point units (FPUs) are not available.
### 1. Fixed Point Math 
Fixed-point math represents fractional values using integers, ideal for embedded systems without a Floating Point Unit (FPU). Rather than performing true floating-point calculations, fixed-point math scales numbers by a constant factor to simulate decimal precision. In formats like Q16.16 or Q8.8, the integer’s bits are divided to represent the integer and fractional parts. For instance, in Q16.16, the upper 16 bits hold the integer portion, and the lower 16 bits store the fractional part, effectively multiplying numbers by 2<sup>16</sup> (65,536). This method provides efficient, resource-saving decimal calculations on simpler hardware.
### 2. Advantages of Fixed-Point Math
- **Speed:** Fixed-point operations are significantly faster than floating-point because they rely on integer arithmetic rather than complex floating-point calculations. This advantage is particularly noticeable on systems without FPUs.
- **Memory Efficiency:** Fixed-point math uses less memory since it doesn’t require floating-point libraries or large variables. This makes it ideal for memory-constrained environments in embedded systems.
- **Deterministic Timing:** Fixed-point operations have constant and predictable execution times, crucial for real-time systems where timing consistency is essential.
- **No FPU Required:** Fixed-point math can operate on simple microcontrollers like the ATmega32, which lack FPUs. It bypasses the need for floating-point emulation, saving considerable CPU cycles.
- **Precision Control:** By adjusting the scaling factor, fixed-point math allows precise control over the balance between range and decimal accuracy, which can be tailored to the application’s specific needs.

### 3. Disadvantages of Fixed-Point Math
- **Limited Range:** Fixed-point math has a narrower range and precision compared to floating-point, which may be limiting in some applications.
- **Scaling Complexity:** Requires careful scaling management, especially with multiplication and division.
- **Code Complexity:** Additional handling for scaling can add complexity to the code.
- **Less Adaptable:** Not as flexible as floating-point for diverse applications.
- **Overflow and Underflow Risks:** Without careful scaling, it’s prone to overflow and underflow.

### 4. Handling Arithmetic with Fixed-Point Math
- **Addition and Subtraction:** Fixed-point addition and subtraction follow integer arithmetic since values are scaled similarly.
- **Multiplication:** After multiplying two fixed-point numbers, the result must be shifted right by the scaling factor (e.g., 16 bits for Q16.16) to avoid -overflow and return to the correct scale.
- **Division:** To maintain precision in division, a left shift is applied to the dividend before dividing by the divisor.
## Task3: Event-Driven Architecture for Embedded Systems
### Introduction
- Event-driven architectures are particularly well-suited for real-time embedded applications and applications concerned with energy consumption. In an event-driven architecture, the system remains in an idle or low-power state until an event triggers an action to be performed.
- This project implements an event-driven architecture using an ATmega microcontroller to manage button press events through interrupts and a circular queue. The system is designed to be energy-efficient, responsive, and scalable, making it suitable for real-time embedded applications.
<div style="text-align: center;">
    <img src="https://github.com/user-attachments/assets/99944726-4ff0-4d9b-9538-db1cfd279a95" alt="Traffic Light" width="900" height="400"/>
</div>

### Architectural Considerations
The event-driven architecture can be implemented in different ways, depending on the performance requirements of the system:
1. **Central Message Processor**: In this approach, the event processing is offloaded to a central message processor, which handles the incoming events and dispatches them to the appropriate event handlers. This approach introduces some overhead and complexity, but it provides a more scalable and reusable architecture.
2. **Direct Event Handling**: For applications with strict performance requirements, the architecture can be designed to handle certain events directly, without going through the central message processor. This approach can reduce latency and complexity, but it may sacrifice some of the benefits of the event-driven architecture, such as scalability and reusability.
### Key Features
- **Energy Efficiency**: The system operates in a low-power idle state until an event occurs, conserving battery life.
- **Immediate Event Response**: External interrupts allow for quick responses to button presses.
- **Scalability**: New events can be easily added by extending the event handling logic.
- **High Cohesion and Low Coupling**: The modular design promotes maintainability and reduces dependencies between components.
### How It Works
1. **Initialization**: The `EventBased_Init` function sets up digital I/O, interrupts, and timers.
2. **Event Handling**: Events are enqueued via interrupt callbacks when buttons are pressed.
3. **Event Processing**: The `EventBased_Runnable` function processes events by dequeuing and executing associated actions.
### Potential Improvements
- Implement tiered event handling to optimize critical event processing.
- Monitor system performance to ensure efficiency.


## Task 4:Flappy Bird Game on ATmega32 with Graphical LCD

## Overview
This project implements a Flappy Bird game on the ATmega32 microcontroller with a graphical LCD. The game is built using three important concepts:

1. **Stack State Machine**: The game uses a stack-based state machine to manage different game states, such as game start, game over, and game paused.
2. **Event-Driven Architecture**: The system responds to events such as button presses and timer interrupts to control the game flow.
3. **Floating Point Unit**: Floating point operations are utilized for movement and speed calculations to ensure smooth gameplay.
### UML Diagram
<div style="text-align: center;">
    <img src="https://github.com/user-attachments/assets/4ce4a8fa-2c02-4d69-9432-f6c32d8fd4b6" alt="Traffic Light" width="900" height="400"/>
</div>

## Problem: Tearing Issue

In embedded systems, specifically with ATmega32 and graphical displays, a common problem is "tearing." This issue occurs when an image is updated while it is being displayed, causing visual artifacts where part of the screen shows an outdated image while the other part shows the updated content.
### Cause of Tearing in This Project
In the Flappy Bird game, tearing happens when obstacles are frequently updated without synchronization, leading to a mismatch between the updated and old parts of the display.
## Possible Solutions for Tearing
There are several solutions that can address the tearing issue in embedded systems like ATmega32. Below are a few strategies and their relevance to this project:
#### 1. Ping-Pong Buffering
- **What it is**: Use two separate regions (buffers) in memory. One buffer is actively being displayed while the other is updated. Once the update is complete, the roles of the buffers are swapped.
- **Pros**:
  - Ensures no tearing occurs, as updates are done off-screen.
  - Can be scaled to a partial buffer model for specific regions.
- **Cons**:
  - Memory intensive—requires space for at least two buffers.
  - Adds complexity in buffer swapping logic.
- **Suitability**: Works well for ATmega32 if implemented with small partial buffers to save memory.
#### 2. Time-Sliced Screen Updates
- **What it is**: Divide the screen into multiple sections (e.g., top, middle, bottom) and update them sequentially using a timer.
- **Pros**:
  - Prevents tearing by limiting visible updates to small regions.
  - Efficient use of memory and processing time.
- **Cons**:
  - Requires complex logic for section updates.
- **Suitability**: Ideal for systems with strict memory limits, providing smooth animations.
#### 3. Adaptive Frame Rate
- **What it is**: Dynamically adjust the frame update rate based on system load.
- **Pros**:
  - Balances performance and rendering quality.
  - Prevents overloading the CPU.
- **Cons**:
  - May cause slightly jerky animations during high load.
- **Suitability**: Excellent for ATmega32, where CPU resources are limited.
#### 4. Interrupt-Driven Dynamic Regions
- **What it is**: Use interrupts to track regions requiring updates (e.g., bird movement or obstacles).
- **Pros**:
  - Efficiently uses processing time.
  - Minimizes unnecessary updates.
- **Cons**:
  - Requires logic to handle overlapping updates.
- **Suitability**: Ideal for event-driven architectures like your project
#### 5. Vertical Alignment of Updates
- **What it is**: Align updates to specific rows or columns to ensure orderly updates.
- **Pros**:
  - Simplifies logic for partial updates.
  - Reduces visual artifacts.
- **Cons**:
  - Requires tight control over rendering logic.
- **Suitability**: Feasible for ATmega32, particularly with time-sliced updates.
## Enhancements to Existing Solutions

#### Critical Section Updates
- Combine with **Partial Screen Updates** to ensure no concurrent modifications.
- Use event flags to safely manage updates in critical sections.
#### Partial Screen Updates
- Maintain a **dirty region tracker** to log and prioritize regions requiring updates.
#### Timer Interrupts
- Use timers to create predictable update windows (e.g., 60 Hz refresh rate).
- Synchronize timer events with event-driven tasks for reduced latency.

 ## Installation & Setup
- **Clone the repository:**
```bash
https://github.com/DemianaYounes/Embedded-Advanced-Tasks.git


