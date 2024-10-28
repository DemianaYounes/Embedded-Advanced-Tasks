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

 ## Installation & Setup
- **Clone the repository:**
```bash
https://github.com/DemianaYounes/Embedded-Advanced-Tasks.git
