# Event-Driven Architecture for Embedded Systems

## Introduction

- Event-driven architectures are particularly well-suited for real-time embedded applications and applications concerned with energy consumption. In an event-driven architecture, the system remains in an idle or low-power state until an event triggers an action to be performed.

- This project implements an event-driven architecture using an ATmega microcontroller to manage button press events through interrupts and a circular queue. The system is designed to be energy-efficient, responsive, and scalable, making it suitable for real-time embedded applications.
 ![EventDrivenArc](https://github.com/user-attachments/assets/99944726-4ff0-4d9b-9538-db1cfd279a95)

## Architectural Considerations

The event-driven architecture can be implemented in different ways, depending on the performance requirements of the system:

1. **Central Message Processor**: In this approach, the event processing is offloaded to a central message processor, which handles the incoming events and dispatches them to the appropriate event handlers. This approach introduces some overhead and complexity, but it provides a more scalable and reusable architecture.
2. **Direct Event Handling**: For applications with strict performance requirements, the architecture can be designed to handle certain events directly, without going through the central message processor. This approach can reduce latency and complexity, but it may sacrifice some of the benefits of the event-driven architecture, such as scalability and reusability.

## Key Features

- **Energy Efficiency**: The system operates in a low-power idle state until an event occurs, conserving battery life.
- **Immediate Event Response**: External interrupts allow for quick responses to button presses.
- **Scalability**: New events can be easily added by extending the event handling logic.
- **High Cohesion and Low Coupling**: The modular design promotes maintainability and reduces dependencies between components.

## How It Works

1. **Initialization**: The `EventBased_Init` function sets up digital I/O, interrupts, and timers.
2. **Event Handling**: Events are enqueued via interrupt callbacks when buttons are pressed.
3. **Event Processing**: The `EventBased_Runnable` function processes events by dequeuing and executing associated actions.

## Potential Improvements

- Implement tiered event handling to optimize critical event processing.
- Monitor system performance to ensure efficiency.
