
#include "rtt_cmd.h"
#include "pwm.h"

#define  RTT_BUF_SIZE 32
uint8_t RTT_Buf[RTT_BUF_SIZE] = {0};
uint32_t RTT_buf_Length = 0;

static void RTT_Cmd(uint8_t* _data, uint16_t _len)
{
    int cycle = 0, pulse = 0, type = 0, state = 0;
    int ret = 0;

    switch (_data[0])
    {
        case 'p':
        {
            ret = sscanf((char*) _data, "p %d %d %d",&type, &cycle, &pulse);
            if (ret < 3)
            {
                #if RTTV_DEBUG_EN
                rttv_debug("[error] Command format error!\r\n");
                #endif
            } 
            else if (ret == 3)
            {
								switch(type)
								{
									case 0:PWM0_Start(cycle, pulse);break;
									case 1:PWM1_Start(cycle, pulse);break;
									case 2:PWM2_Start(cycle, pulse);break;
									case 3:PWM3_Start(cycle, pulse);break;
								}
								
								#if RTTV_DEBUG_EN
								rttv_debug("pulse,type:%d, cycle:%d, pulse:%d\n",type, cycle,pulse);
                #endif
            }            
        }
        break;
				
        case 'e':
        {
            ret = sscanf((char*) _data, "e %d %d",&type, &state);
            if (ret < 2)
            {
                #if RTTV_DEBUG_EN
                rttv_debug("[error] Command format error!\r\n");
                #endif
            } 
            else if (ret == 2)
            {
								switch(type)
								{
									case 0:EN0(state);break;
									case 1:EN1(state);break;
									case 2:EN2(state);break;
									case 3:EN3(state);break;
								}
								
								#if RTTV_DEBUG_EN
								rttv_debug("enable, type:%d, state:%d\n",type, state);
                #endif
            }            
        }
        break;
				
        case 'd':
        {
            ret = sscanf((char*) _data, "d %d %d",&type, &state);
            if (ret < 2)
            {
                #if RTTV_DEBUG_EN
                rttv_debug("[error] Command format error!\r\n");
                #endif
            } 
            else if (ret == 2)
            {
								switch(type)
								{
									case 0:DIR0(state);break;
									case 1:DIR1(state);break;
									case 2:DIR2(state);break;
									case 3:DIR3(state);break;
								}
								
								#if RTTV_DEBUG_EN
								rttv_debug("direction, type:%d, state:%d\n",type, state);
                #endif
            }            
        }
        break;
				
        default:
            break;      
    }
}

void RTT_CMD_Process(void)
{
    uint32_t bytes = 0;

    if(SEGGER_RTT_HasData(0))//not empty
    {
        bytes = SEGGER_RTT_Read(0, RTT_Buf, 32);
        if(bytes > 0)
        {
            RTT_Cmd(RTT_Buf, RTT_buf_Length);
        }
    } 
}

