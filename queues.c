#include "queues.h"

void motorQueueCreate(){
    motorMsgQueue = xQueueCreate(10, sizeof(MotorMsg));
    if(motorMsgQueue == NULL){
        haltAll(ERRORCODE);
    }
}

void motorQueueSendFromISR(int encoderL, int encoderR, BaseType_t *woken){
    dbgOutputEvent(SENDFROMISR_START);
    MotorMsg mMsgSend = {encoderISR, encoderL, encoderR, 0, 0};
    if(xQueueSendFromISR(motorMsgQueue, &mMsgSend, woken) != pdTRUE){
        haltAll(ERRORCODE);
    }
    dbgOutputEvent(SENDFROMISR_END);
}

void motorQueueSendFromRX(int ctrl, int val){
    dbgOutputEvent(SENDFROMTASK_START);
    MotorMsg mMsgSend = {rx, 0, 0, ctrl, val};
    if(xQueueSend(motorMsgQueue, &mMsgSend, 0) != pdTRUE){
        haltAll(ERRORCODE);
    }
    dbgOutputEvent(SENDFROMTASK_END);
}

MotorMsg motorQueueRecvBlocking(){
    dbgOutputEvent(RECVFROMTASK_START);
    MotorMsg mMsgRecv;
    if(xQueueReceive(motorMsgQueue, &mMsgRecv, portMAX_DELAY) != pdTRUE){
        haltAll(ERRORCODE);
    }
    dbgOutputEvent(RECVFROMTASK_END);
    return mMsgRecv;
}

void txQueueCreate(){
    TxQueue = xQueueCreate(10, sizeof(ByteArray));
    if(TxQueue == NULL){
        haltAll(ERRORCODE);
    }
}

void txQueueSend(ByteArray bA){
    dbgOutputEvent(SENDFROMTASK_START);
    if(xQueueSend(TxQueue, &bA, 0) != pdTRUE){
        haltAll(ERRORCODE);
    }
    dbgOutputEvent(SENDFROMTASK_END);
}

void txQueueSendFromISR(ByteArray bA, BaseType_t *woken){
    dbgOutputEvent(SENDFROMISR_START);
    if(xQueueSendFromISR(TxQueue, &bA, woken) != pdTRUE){
        haltAll(ERRORCODE);
    }
    dbgOutputEvent(SENDFROMISR_END);
}

ByteArray txQueueRecvFromISR(BaseType_t * woken){
    ByteArray msgRcv;
    if(xQueueReceiveFromISR(TxQueue, &msgRcv, woken) != pdTRUE){
        haltAll(ERRORCODE);
    }
    return msgRcv;
}

void rxQueueCreate(){
    RxQueue = xQueueCreate(10, sizeof(ByteArray));
    if(RxQueue == NULL){
        haltAll(ERRORCODE);
    }
}

void rxQueueSendFromISR(ByteArray bA, BaseType_t * woken){
    if(xQueueSendFromISR(RxQueue, &bA, woken) != pdTRUE){
        haltAll(ERRORCODE);
    }
}

ByteArray rxQueueRecv(){
    ByteArray ba;
    if(xQueueReceive(RxQueue, &ba, portMAX_DELAY) != pdTRUE){
        haltAll(ERRORCODE);
    }
    dbgOutputEvent(RX_TASK_RECV_FROM_ISR);
    return ba;
}

void feedbackQueueCreate(){
    feedBackQueue = xQueueCreate(10, sizeof(FeedBack_Data));
    if(feedBackQueue == NULL){
        haltAll(ERRORCODE);
    }
}


void feedbackQueueSendFromMotor(int ack, int encoderL, int encoderR, char move, int e, int Lp, int Li, int Ld, int Rp, int Ri, int Rd, int setV){
    dbgOutputEvent(SENDTOFB_MOTOR);
    FeedBack_Data fbd = {motor, -1, ack, encoderL, encoderR, move, 0, 0, 0, e, Lp, Li, Ld, Rp, Ri, Rd, setV};
    if(xQueueSend(feedBackQueue, &fbd, 0) != pdTRUE){
        haltAll(ERRORCODE);
    }
}

void feedbackQueueSendFromSensor(unsigned int r, unsigned int g, unsigned int b){
    dbgOutputEvent(SENDTOFB_SENSOR);
    FeedBack_Data fbd = {sensor, -1, 0, 0, 0, 0, r, g, b, 0, 0, 0, 0, 0, 0};
    if(xQueueSend(feedBackQueue, &fbd, 0) != pdTRUE){
        haltAll(ERRORCODE);
    }
}

void feedbackQueueSendFromRX(int msgID){
    dbgOutputEvent(SENDTOFB);
    FeedBack_Data fbd = {rx, msgID, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if(xQueueSend(feedBackQueue, &fbd, 0) != pdTRUE){
        haltAll(ERRORCODE);
    }
}

FeedBack_Data feedbackQueueRecv(){
    dbgOutputEvent(RECVFROMTASK_START);
    FeedBack_Data fbd;
    if(xQueueReceive(feedBackQueue, &fbd, portMAX_DELAY) != pdTRUE){
        haltAll(ERRORCODE);
    }
    return fbd;
    dbgOutputEvent(RECVFROMTASK_END);
}

void sensorQueueCreate(){
    sensorQueue = xQueueCreate(10, sizeof(SensorMsg));
    if(sensorQueue == NULL){
        haltAll(ERRORCODE);
    }
}

void sensorQueueSendFromISR(unsigned int r, unsigned int g, unsigned int b, BaseType_t *woken){
    dbgOutputEvent(SENDFROMISR_START);
    SensorMsg sm = {sensor, r, g, b, 0};
    if(xQueueSendFromISR(sensorQueue, &sm, woken) != pdTRUE){
        haltAll(ERRORCODE);
    }
    dbgOutputEvent(SENDFROMISR_END);
}

void sensorQueueSendFromRX(char signal){
    dbgOutputEvent(SENDFROMTASK_START);
    SensorMsg sm = {rx, 0, signal};
    if(xQueueSend(sensorQueue, &sm, 0) != pdTRUE){
        haltAll(ERRORCODE);
    }
    dbgOutputEvent(SENDFROMTASK_END);
}

SensorMsg sensorQueueRecv(){
    dbgOutputEvent(RECVFROMTASK_START);
    SensorMsg sm;
    if(xQueueReceive(sensorQueue, &sm, portMAX_DELAY) != pdTRUE){
        haltAll(ERRORCODE);
    }
    return sm;
    dbgOutputEvent(RECVFROMTASK_END);
}

/* *****************************************************************************
 End of File
 */
