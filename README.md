# FreeRTOS Task Scheduling Demo

A compact **FreeRTOS** demo on the **STM32F303RE Nucleo** that highlights real‑time **multitasking, priority‑based scheduling, and runtime task control**. Console output is streamed live over **SWO/ITM** using `printf`.

---

## Problem

How can a microcontroller run **multiple tasks concurrently**, enforce **priority‑based scheduling**, and allow one task to **terminate another** — without complex bare‑metal state machines?

---

## Method

- **Two Tasks:** `Task1` and `Task2` created with `osThreadNew()`.
- **Scheduler Control:** `osDelay()` yields CPU time so the RTOS can preempt/schedule fairly.
- **Task Termination:** `osThreadTerminate(Task1Handle)` demonstrates runtime task control from another task.
- **Console Output:** `printf()` is redirected via `ITM_SendChar` (SWO/ITM) for real‑time viewing.
- **Key init (from main.c):** `Task1Handle = osThreadNew(StartTask1, NULL, &Task1_attributes);` and `Task2Handle = osThreadNew(StartTask2, NULL, &Task2_attributes);`

---

## Result

Three scenarios make scheduling behavior obvious in the console:

1) **Task1 Higher Priority** — `Task1: Normal`, `Task2: Low`  
   Output pattern:  
   Task 1  
   Task 2  
   Task 1  
   Task 2  
   …

2) **Task2 Higher Priority** — `Task1: Low`, `Task2: Normal`  
   Output pattern:  
   Task 2  
   Task 1  
   Task 2  
   Task 1  
   …

3) **Task1 Terminated by Task2** — `Task2` calls `osThreadTerminate(Task1Handle)`  
   Output pattern:  
   Task 1  
   Task 2  
   Task 2  
   Task 2  
   …

These confirm **priority‑based scheduling**, **cooperative multitasking via delays**, and **runtime task termination**.

---

## Hardware

- **STM32F303RE** Nucleo board  
- **ST‑Link** (power / program / debug)  
- **Host PC** with **STM32CubeIDE**

---

## SWO/ITM Output Setup (CubeIDE)

1. Start a Debug session.  
2. Open **SWV ITM Console**.  
3. Enable **Stimulus Port 0**.  
4. Click **Start Trace** to watch `Task 1` / `Task 2` messages in real time.

---

## Takeaways (Recruiter‑Friendly)

- Shows **RTOS fundamentals**: preemption, priorities, and task lifecycle control.  
- Cleaner, modular design vs. bare‑metal superloops.  
- Real‑time visibility with **SWO/ITM logging** on resource‑constrained MCUs.

---
