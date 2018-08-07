#include "tx.h"

void TX_Initialize ( void )
{
    dbgOutputEvent(TX_INIT);
    txQueueCreate();
    feedbackQueueCreate();
    SYS_INT_SourceDisable(INT_SOURCE_USART_1_TRANSMIT);
}

void TX_Tasks ( void )
{
    dbgOutputEvent(TX_TASK_START);
    FeedBack_Data fbd;
    ByteArray ba;
    int msgID = 1;
    int canSend = 1;
    
    FeedBack_Data wFbd;
    wFbd.source = null;
    int oldID = -1;
    
    sprintf(ba.c, "{s}");
    txQueueSend(ba);
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
    
    while(1){
        dbgOutputEvent(TX_WHILE);
        fbd = feedbackQueueRecv();
        if(fbd.source == rx){
            dbgOutputEvent(TX_RX_MSG);
            if(fbd.msg_id == oldID){
                canSend = 1;
            }
        }
        if(fbd.source == sensor){
            dbgOutputEvent(TX_SENSOR_MSG);
            sprintf(ba.c, JSON_SENSOR, msgID, SOURCE_SENSOR, fbd.sensor);
            txQueueSend(ba);
            SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
            msgID++;
        }
    }
}
