#include "debug.h"

void dbgOutputVal(char outVal){
    (outVal & 0b10000000) ? PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_10, 1) : PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_10, 0);
    (outVal & 0b01000000) ? PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5, 1) : PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5, 0);
    (outVal & 0b00100000) ? PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_11, 1) : PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_11, 0);
    (outVal & 0b00010000) ? PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_13, 1) : PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_13, 0);
    (outVal & 0b00001000) ? PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12, 1) : PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12, 0);
    (outVal & 0b00000100) ? PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_8, 1) : PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_8, 0);
    (outVal & 0b00000010) ? PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_10, 1) : PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_10, 0);
    (outVal & 0b00000001) ? PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0, 1) : PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0, 0);
    
    PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6);
}

//void dbgUARTVal(unsigned char outVal){
//    if(!DRV_USART_TransmitBufferIsFull(usartHandle)){
//        DRV_USART_WriteByte(usartHandle, outVal);
//    }
//}

void dbgOutputEvent(unsigned int outVal){
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, outVal);
}

// demo by using a counter or, even better, a GPIO that goes high to trigger
void haltAll(unsigned int code){
    if(code == ERRORCODE){
        // disable interrupts
        // suspend all threads - enter infinite while loop
        // display error code
        taskENTER_CRITICAL();
        vTaskSuspendAll();
        dbgOutputEvent(ERROR_HALTED_ALL);
        PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_3, 0);
        while(1);
    }
}


/* *****************************************************************************
 End of File
 */
