# FreeRTOS Task Scheduling Demonstration – STM32F303RE

This project showcases the power and versatility of **FreeRTOS** on the STM32F303RE Nucleo board through dynamic task scheduling, priority control, and task termination. Unlike bare-metal looping logic, FreeRTOS enables real-time, responsive multitasking that scales cleanly as embedded systems grow more complex.

---

## 🎯 Objective

To demonstrate:
- How task **prioritization** affects execution order
- How **preemption** and **scheduling** work in FreeRTOS
- How one task can **terminate** another
- Why FreeRTOS is more maintainable, scalable, and responsive than traditional embedded approaches

---

## 🛠️ Hardware Requirements

- STM32F303RE Nucleo board  
- USB (for power + SWO debug output)  
- STM32CubeIDE (or compatible build system)  

---

## ⚙️ How It Works

The project defines **two tasks**, `Task1` and `Task2`, each printing its name over SWO. The execution pattern changes over **three phases**, demonstrating FreeRTOS features step-by-step:

---

### ✅ Phase 1 – Task1 Priority is Higher

```c
Task1: priorityNormal
Task2: priorityLow
```

### 🔄 Output:
```
Task 1
Task 2
Task 1
Task 2
...
```
Task1 always executes first due to higher priority. Task2 waits until Task1 yields with `osDelay()`.

---

### ✅ Phase 2 – Task2 Priority is Raised

```c
Task1: priorityLow
Task2: priorityNormal
```

### 🔄 Output:
```
Task 2
Task 1
Task 2
Task 1
...
```
Now Task2 dominates the schedule and prints first.

---

### ✅ Phase 3 – Task1 is Terminated by Task2

```c
// inside Task2:
osThreadTerminate(Task1Handle);
```

### 🔄 Output:
```
Task 1
Task 2
Task 2
Task 2
...
```
After the first cycle, Task1 is terminated and only Task2 continues running.

---

## 🧠 Key FreeRTOS Concepts Demonstrated

| Concept                | Description |
|------------------------|-------------|
| `xTaskCreate()` / `osThreadNew()` | Dynamic task creation with priorities |
| `osDelay()`            | Cooperative delay yielding CPU to scheduler |
| `osThreadTerminate()`  | Task A can terminate Task B cleanly |
| Preemptive scheduling  | Higher-priority tasks interrupt lower-priority ones |
| Modular design         | Clear separation of task logic for scalability |

---
