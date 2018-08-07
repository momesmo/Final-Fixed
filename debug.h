#ifndef _DEBUG_H    /* Guard against multiple inclusion */
#define _DEBUG_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
#define ISR_START 0x01
#define ISR_END 0x02
#define SENDFROMISR_START 0x03
#define SENDFROMISR_END 0x04
#define RECVFROMISR_START 0x05
#define RECVFROMISR_END 0x06
    
#define MOTORCALLBACK_START 0x07
#define MOTORCALLBACK_END 0x08
#define SENSORCALLBACK_START 0x09
#define SENSORCALLBACK_END 0x0A
#define LEDCALLBACK_START 0x0B
#define LEDCALLBACK_END 0x0C
    
#define MOTOR_TASK_START 0x11
#define MOTOR_INIT 0x12
#define SENDFROMTASK_START 0x13
#define SENDFROMTASK_END 0x14
#define RECVFROMTASK_START 0x15
#define RECVFROMTASK_END 0x16
#define SENDTOFB 0x17
#define MOTOR_WHILE 0x18
#define MOTOR_RX_MSG 0x19
#define MOTOR_ENCODER_MSG 0x1A
#define MOTOR_CONTROL_MSG 0x1B
#define SENDTOFB_SENSOR 0x1C
#define SENDTOFB_MOTOR 0x1D
    
#define MOTOR_STOP 0x21
#define MOTOR_FORWARD 0x22
#define MOTOR_BACK 0x23
#define MOTOR_LEFT 0x24
#define MOTOR_RIGHT 0x25
#define MOTOR_SPEED20 0x26
#define MOTOR_SPEED40 0x27
#define MOTOR_SPEED60 0x28
#define MOTOR_SPEED80 0x29
#define SET_ENCODER_30 0x2A
#define SET_ENCODER_40 0x2B
#define SET_ENCODER_50 0x2C
#define SET_ENCODER_60 0x2D
#define SET_ENCODER_70 0x2E
#define SET_ENCODER_80 0x2F
    
#define TX_MOTOR_CANT_SEND 0x30
#define TX_INIT 0x31
#define TX_TASK_START 0x32
#define GPIO_TRIGGER 0x33
#define TX_ENTER_StartSending 0x34
#define TX_MSG_RECV 0x35
#define TX_INTS_DISABLED 0x36
#define TX_ISR_START 0x37
#define TX_ENTER_StillSending 0x38
#define TX_BYTE_WRITTEN 0x39
#define TX_BUFFER_WRITTEN 0x3A
#define TX_SENSOR_MSG 0x3B
#define TX_MOTOR_MSG 0x3C
#define TX_RX_MSG 0x3D
#define TX_ACK_TIMEOUT 0x3E
#define TX_WHILE 0x3F
    
#define RX_WHILE 0x40
#define RX_ISR_START 0x41
#define RX_DATA_AVAILABLE 0x42
#define RX_END 0x43
#define RX_MSG_SENT_FROM_ISR 0x44
#define RX_TASK_RECV_FROM_ISR 0x45
#define RX_TASK_START 0x46
#define RX_INIT 0x47
#define RX_GO_RECV 0x48
#define RX_GOT_ACK 0x49
#define RX_SENDING_COMMAND 0x4A
    
#define SENSOR_TASK_START 0x51
#define SENSOR_RX_MSG 0x52
#define SENSOR_SENSOR_MSG 0x53
#define SENSOR_INIT 0x54
    
#define TIMEOUT_SENDING 0x61
#define RX_ACK_BACK 0x62
#define RX_NO_ACK_RESEND 0x63
    

#define ENCODER_DATA 0x98
    
#define ERROR_HALTED_ALL 0xFF
    
#define ERRORCODE 0xFFFF
    
//    DRV_HANDLE usartHandle;
    
    void dbgOutputVal(char outVal);
    void dbgUARTVal(unsigned char outVal);
    void dbgOutputEvent(unsigned int outVal);
    void haltAll(unsigned int code);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _DEBUG_H */

/* *****************************************************************************
 End of File
 */
