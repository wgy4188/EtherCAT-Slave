
#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

#define OS_TASK_TMR_PRIO  (OS_LOWEST_PRIO-2)

/*define prioty*/
#define  SIGNAL_TASK_PRIO      5
#define  MODBUS_TASK_PRIO      6
#define  MAIN_TASK_PRIO				 7

/*define task stack size*/
#define SIGNAL_TASK_STACK_SIZE 256
#define MODBUS_TASK_STACK_SIZE 256
#define MAIN_TASK_STACK_SIZE   256


#endif
