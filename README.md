# 🔍 FreeRTOS Task Scheduling Demo – STM32F303RE

This project showcases the power of **FreeRTOS** on the STM32F303RE Nucleo board. It demonstrates how real-time operating systems enable multitasking and priority-based scheduling — capabilities that are difficult or impossible to achieve in bare-metal embedded systems.

---

## 🎯 Project Goal

To demonstrate the versatility of FreeRTOS through:

- Cooperative multitasking using `osDelay()`
- Task priority control and preemption
- Runtime task termination from another task

---

## 🔧 Hardware Used

- **STM32F303RE** Nucleo Board  
- **ST-Link** USB interface (for power, programming, and debugging)  
- **Host PC** running **STM32CubeIDE**

---

## 🚦 How It Works

The project defines two tasks, `Task1` and `Task2`, both of which print to the **ITM/SWO debug console** using `printf()` routed through `ITM_SendChar()`. Their priorities and behavior are adjusted to demonstrate three different scheduling outcomes.

Task creation in `main.c`:

```c
Task1Handle = osThreadNew(StartTask1, NULL, &Task1_attributes);
Task2Handle = osThreadNew(StartTask2, NULL, &Task2_attributes);
```

---

## 📊 Demo Scenarios

### ✅ Scenario 1: Task1 Has Higher Priority

- `Task1`: `osPriorityNormal`  
- `Task2`: `osPriorityLow`

🔁 Output:
```
Task 1
Task 2
Task 1
Task 2
...
```

This shows standard preemption, where the higher-priority task (`Task1`) always runs first but still shares CPU time thanks to `osDelay()`.

---

### ✅ Scenario 2: Task2 Has Higher Priority

- `Task1`: `osPriorityLow`  
- `Task2`: `osPriorityNormal`

🔁 Output:
```
Task 2
Task 1
Task 2
Task 1
...
```

Changing just the task priorities reverses the order of execution — showing the power of the scheduler without changing any task logic.

---

### ✅ Scenario 3: Task1 Is Terminated by Task2

- `Task1`: Any priority  
- `Task2`: Any priority  
- `Task2` contains: `osThreadTerminate(Task1Handle);`

🔁 Output:
```
Task 1
Task 2
Task 2
Task 2
...
```

Here, `Task2` terminates `Task1` after the first run, demonstrating **dynamic runtime control** between tasks.

---

## 💻 Output Configuration

All `printf()` output is routed through **SWO (Serial Wire Output)** using `ITM_SendChar()` defined in `syscalls.c`.

To view output in **STM32CubeIDE**:
1. Enable SWV trace.
2. Open the **SWV ITM Console**.
3. Enable Stimulus Port 0 (channel 0).
4. Run the debugger and watch the real-time task activity.

---

## 🧠 Why Use FreeRTOS?

This project illustrates key advantages of using an RTOS:

| Feature                  | Bare-Metal | FreeRTOS |
|--------------------------|------------|----------|
| Concurrent task handling | ❌ No       | ✅ Yes    |
| Task priority control     | ❌ No       | ✅ Yes    |
| Runtime task termination  | ❌ Manual workaround | ✅ Built-in |
| Code modularity           | ❌ Messy    | ✅ Structured |

Even with only two tasks, the flexibility and clarity FreeRTOS provides makes it ideal for robust embedded system design.

---
