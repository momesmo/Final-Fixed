#include "system/common/sys_common.h"
#include "tx.h"
#include "rx.h"
#include "sensor.h"
#include "system_definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************
void IntHandlerDrvUsartInstance0(void)
{
    BaseType_t txHigherPriorityTaskWoken = pdFALSE;
    BaseType_t rxHigherPriorityTaskWoken = pdFALSE;
    
    dbgOutputEvent(ISR_START);
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_RECEIVE))
    {
        dbgOutputEvent(RX_ISR_START);
        static ByteArray ba;
        static int recvCount = 0;
        if(PLIB_USART_ReceiverDataIsAvailable(USART_ID_1)){
//            dbgOutputEvent(RX_DATA_AVAILABLE);
            ba.c[recvCount] = PLIB_USART_ReceiverByteReceive(USART_ID_1);
            if(ba.c[recvCount] == '}'){
//                dbgOutputEvent(RX_END);
                rxQueueSendFromISR(ba, &rxHigherPriorityTaskWoken);
                dbgOutputEvent(RX_MSG_SENT_FROM_ISR);
                recvCount = -1;
            }
            recvCount++;
        }
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_RECEIVE);
    }
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_TRANSMIT))
    {
        dbgOutputEvent(TX_ISR_START);
        enum States{stillSending, startSending};
        static enum States s = startSending;
        static ByteArray array;
        static int count = 0;
        switch(s){
            case(startSending):
                if(xQueueIsQueueEmptyFromISR(TxQueue) == pdFALSE){
                    array = txQueueRecvFromISR(&txHigherPriorityTaskWoken);//receive byte array from queue
//                    dbgOutputEvent(TX_MSG_RECV);
                    s = stillSending;
                }
                else{
                    SYS_INT_SourceDisable(INT_SOURCE_USART_1_TRANSMIT);
                    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_1_TRANSMIT);
                    break;
                }
            case(stillSending):
//                dbgOutputEvent(TX_ENTER_StillSending);
                if(!PLIB_USART_TransmitterBufferIsFull(USART_ID_1)){
                    PLIB_USART_TransmitterByteSend(USART_ID_1, array.c[count]);
//                    dbgOutputEvent(TX_BYTE_WRITTEN);
                    if(array.c[count] == '}')
                    {
                        dbgOutputEvent(TX_BUFFER_WRITTEN);
                        s = startSending;
                        count = 0;
                        array.c[0] = 0;
                    }else{
                        count++;
                    }
                }
				break;
            default:
                haltAll(ERRORCODE);
                break;
        }
    }
    portEND_SWITCHING_ISR(txHigherPriorityTaskWoken);
    portEND_SWITCHING_ISR(rxHigherPriorityTaskWoken);
}
 
 
 

 

 

 

 

 
 
 
/*******************************************************************************
 End of File
*/
