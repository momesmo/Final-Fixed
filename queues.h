#ifndef _QUEUES_H    /* Guard against multiple inclusion */
#define _QUEUES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"

#include "queue.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
    
    typedef enum {null, motor, sensor, rx, sensorISR, encoderISR}SentFromThread;
   
    QueueHandle_t motorMsgQueue;
    typedef struct motorMsg{
        SentFromThread source;
        int encoderLeft;
        int encoderRight;
        int ctrl;
        int val;
    } MotorMsg;
    void motorQueueCreate();
    void motorQueueSendFromISR(int encoderL, int encoderR, BaseType_t *woken);
    void motorQueueSendFromRX(int ctrl, int val);
    MotorMsg motorQueueRecvBlocking();

    
    QueueHandle_t TxQueue;
    QueueHandle_t RxQueue;
    typedef struct byteArray{
        unsigned char c[1024];
    } ByteArray;
    void txQueueCreate();
    void txQueueSend(ByteArray bA);
    ByteArray txQueueRecvFromISR(BaseType_t * woken);
    void rxQueueCreate();
    void rxQueueSendFromISR(ByteArray bA, BaseType_t * woken);
    ByteArray rxQueueRecv();
    
    
    QueueHandle_t feedBackQueue;
    typedef struct feedBack_data{
        SentFromThread source;
        int msg_id;
        int ack;
        int enL;
        int enR;
        char move;
        unsigned int sensor_r;
        unsigned int sensor_g;
        unsigned int sensor_b;
        int err;
        int Lp;
        int Li;
        int Ld;
        int Rp;
        int Ri;
        int Rd;
        int setV;
    } FeedBack_Data;
    void feedbackQueueCreate();
    void feedbackQueueSendFromMotor(int ack, int encoderL, int encoderR, char move, int e, int Lp, int Li, int Ld, int Rp, int Ri, int Rd, int setV);
    void feedbackQueueSendFromSensor(unsigned int r, unsigned int g, unsigned int b);
    void feedbackQueueSendFromRX(int msgID);
    FeedBack_Data feedbackQueueRecv();
    
    QueueHandle_t sensorQueue;
    typedef struct sensorMsg{
        SentFromThread source;
        unsigned int r, g, b;
        char signal;
    } SensorMsg;
    void sensorQueueCreate();
    void sensorQueueSendFromISR(unsigned int r, unsigned int g, unsigned int b, BaseType_t *woken);
    void sensorQueueSendFromRX(char signal);
    SensorMsg sensorQueueRecv();
    

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _QUEUES_H */

/* *****************************************************************************
 End of File
 */
