#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>  // For printf()

/* Task handles */
osThreadId_t Task1Handle;
osThreadId_t Task2Handle;

/* Task attributes */
const osThreadAttr_t Task1_attributes = {
    .name = "Task1",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityNormal  // Higher than Task2 initially
};

const osThreadAttr_t Task2_attributes = {
    .name = "Task2",
    .stack_size = 128 * 4,
    .priority = (osPriority_t) osPriorityLow
};

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void StartTask1(void *argument);
void StartTask2(void *argument);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();

    osKernelInitialize();

    Task1Handle = osThreadNew(StartTask1, NULL, &Task1_attributes);
    Task2Handle = osThreadNew(StartTask2, NULL, &Task2_attributes);

    osKernelStart();

    while (1) {}  // Should never reach here
}

void StartTask1(void *argument)
{
    for (;;)
    {
        printf("Task 1\n");
        osDelay(1000);
    }
}

void StartTask2(void *argument)
{
    for (;;)
    {
        printf("Task 2\n");
        osDelay(1000);
        osThreadTerminate(Task1Handle);  // Terminates Task1 after first round
    }
}

/* Minimal GPIO init */
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}

/* System clock: HSI, no PLL */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                 | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}

void Error_Handler(void)
{
    __disable_irq();
    while (1) {}
}
