// main.c
// CWR_SZ project

// Created by Song Junlin on 3/21/2019
// Copyright 2019 IRIM, Inc. All right reserved.
//
/*-------------------------------Includes-------------------------------*/
/*STM32*/
#include "delay.h"
#include "led.h"
#include "sys.h"

/*FreeRTOS*/
#include "FreeRTOS.h"
#include "task.h"

/*FreeModbus*/
#include "FreeModbus.h"

/*robot*/

/*--------------------------------TASK---------------------------------*/
//任务优先级
#define START_TASK_PRIO 1
//任务堆栈大小
#define START_STK_SIZE 128
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

#define Modbus_TASK_PRIO 5
#define Modbus_STK_SIZE 256
TaskHandle_t ModbusTask_Handler;
void Modbus_task(void *pvParameters);

/*----------------------------Start Implemention-------------------------*/

int main()
{

  //设置系统中断优先级分组4
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  LED_Init();

  //创建开始任务
  xTaskCreate((TaskFunction_t)start_task,          //任务函数
              (const char *)"start_task",          //任务名称
              (uint16_t)START_STK_SIZE,            //任务堆栈大小
              (void *)NULL,                        //传递给任务函数的参数
              (UBaseType_t)START_TASK_PRIO,        //任务优先级
              (TaskHandle_t *)&StartTask_Handler); //任务句柄
  vTaskStartScheduler();                           //开启任务调度
  return 0;
}

/*------------------------------TASK Functions------------------------------*/

//开始任务任务函数
void start_task(void *pvParameters)
{
  //进入临界区
  taskENTER_CRITICAL();

  // creat modbus task
  xTaskCreate((TaskFunction_t)Modbus_task, (const char *)"Modbus_task",
              (uint16_t)Modbus_STK_SIZE, (void *)NULL,
              (UBaseType_t)Modbus_TASK_PRIO,
              (TaskHandle_t *)&ModbusTask_Handler);

  vTaskDelete(StartTask_Handler); //删除开始任务
  taskEXIT_CRITICAL();            //退出临界区
}
// Modbus task
void Modbus_task(void *pvParameters)
{
  // Modbus Init
  eMBInit(MB_RTU, 11, 0x01, 19200, MB_PAR_NONE);
  eMBEnable();
  while (1)
  {
    eMBPoll();
    vTaskDelay(50);
  }
}
