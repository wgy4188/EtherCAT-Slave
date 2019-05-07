#include "main.h"


//创建任务堆栈
__align(8) static OS_STK SignalTaskStk[SIGNAL_TASK_STACK_SIZE];
__align(8) static OS_STK ModbusTaskStk[MODBUS_TASK_STACK_SIZE];	
__align(8) static OS_STK MainTaskStk[MAIN_TASK_STACK_SIZE];

//声明任务
static void ModbusTask(void *p_arg);
static void SignalTask(void *p_arg);
static void MainTask(void *p_arg);

//OS_EVENT *RecF;/*recv data event*/

int main(void)
{
		INT8U  err;
	
    CPU_IntDis();
		OSInit(); 
	
		BSP_Init();
		SerPrintf("Start...\n");
	
#if (OS_TASK_STAT_EN > 0)
		OSStatInit();//配置要使用统计任务，先初始化
#endif
	
//		RecF = OSSemCreate(0);/*event*/	

		/*creat signal task*/
		OSTaskCreateExt(SignalTask,	
										(void *)0,
										(OS_STK *)&SignalTaskStk[SIGNAL_TASK_STACK_SIZE - 1],
										SIGNAL_TASK_PRIO,	
										SIGNAL_TASK_PRIO,
										(OS_STK *)&SignalTaskStk[0],
										SIGNAL_TASK_STACK_SIZE, 
										(void *)0,
										OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
		 
		OSTaskNameSet(SIGNAL_TASK_PRIO, (INT8U*)"SignalTask", &err);
										
		/*creat modbus task*/
		OSTaskCreateExt(ModbusTask,	
										(void *)0,
										(OS_STK *)&ModbusTaskStk[MODBUS_TASK_STACK_SIZE - 1],
										MODBUS_TASK_PRIO,	
										MODBUS_TASK_PRIO,
										(OS_STK *)&ModbusTaskStk[0],
										MODBUS_TASK_STACK_SIZE, 
										(void *)0,
										OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
		 
		OSTaskNameSet(MODBUS_TASK_PRIO, (INT8U*)"ModbusTask", &err);			
										
		/*creat main task*/
		OSTaskCreateExt(MainTask,	
										(void *)0,
										(OS_STK *)&MainTaskStk[MAIN_TASK_STACK_SIZE - 1],
										MAIN_TASK_PRIO,	
										MAIN_TASK_PRIO,
										(OS_STK *)&MainTaskStk[0],
										MAIN_TASK_STACK_SIZE, 
										(void *)0,
										OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
										
		OSTaskNameSet(MAIN_TASK_PRIO, (INT8U*)"MainTask", &err);
										
		OSTimeSet(0);	
		OSStart();
	
    return (0);	
	
}

static void SignalTask(void *p_arg)
{	
	 (void)p_arg;
	
	 for(;;)
	 {	  	  		
				Dout(1,1);
				OSTimeDlyHMSM(0, 0, 0, 100);
				Dout(1,0);
				OSTimeDlyHMSM(0, 0, 0, 100); 
	 }
}

static void ModbusTask(void *p_arg)
{  
		(void)p_arg;
		 		
		for(;;)
		{
				Dout(2,1);
				OSTimeDlyHMSM(0, 0, 0, 100);
				Dout(2,0);
				OSTimeDlyHMSM(0, 0, 0, 100); 	 
		}
}

static void MainTask(void *p_arg)
{	
	 (void)p_arg;

	 for(;;)
	 {	  	  		 
				Dout(3,1);
				OSTimeDlyHMSM(0, 0, 0, 100);
				Dout(3,0);
				OSTimeDlyHMSM(0, 0, 0, 100); 
	 }
}


#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  while (1)
  {
				
  }
}
#endif

