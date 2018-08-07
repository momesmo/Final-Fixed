#include "rx.h"

void RX_Initialize ( void )
{
    dbgOutputEvent(RX_INIT);
    rxQueueCreate();
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_RECEIVE);
}

void RX_Tasks ( void )
{
    dbgOutputEvent(RX_TASK_START);
    ByteArray ba;
    int once = 0;
    
    while(1){
        dbgOutputEvent(RX_WHILE);
        ba = rxQueueRecv();
        
//        if(((ba.c[1] == 'G' && ba.c[2] == 'O') || PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_3) == 0) && once == 0){
        switch(once){
            case 0:
                if(ba.c[1] == 'G' && ba.c[2] == 'O' && once == 0){
                    dbgOutputEvent(RX_GO_RECV);
                    sensorQueueSendFromRX('g');
                    once = 1;
                }
                break;
            case 1:
                if(jRead_int(ba.c, "{'MSG_TYPE'", NULL) == 0){ //ACK
                    dbgOutputEvent(RX_GOT_ACK);
                    feedbackQueueSendFromRX(jRead_int(ba.c, "{'MSG_ID'", NULL));
                }
                break;
        }
   }
}
