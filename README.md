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

 ## Installation & Setup
- **Clone the repository:**
```bash
https://github.com/DemianaYounes/Embedded-Advanced-Tasks.git


