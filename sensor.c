#include "sensor.h"

void vSensorCallbackFunction( TimerHandle_t xTimer ){
    BaseType_t timerHigherPriorityTaskWoken = pdFALSE;
    dbgOutputEvent(SENSORCALLBACK_START);
    
    sensorQueueSendFromISR(sensorStateMachine(), &timerHigherPriorityTaskWoken);
    
    dbgOutputEvent(SENSORCALLBACK_END);
    portEND_SWITCHING_ISR(timerHigherPriorityTaskWoken);
}

void createAndStartSensorTimer(){
    sensorTMR = xTimerCreate
            ("Sensor_TMR", /*Text name, not used by RTOS*/
            pdMS_TO_TICKS(125), /*Timer period in MS, converts to ticks*/
            pdTRUE, /*Timer auto-reloads when expired*/
            (void * ) 0, /*Stores the count of times timer expires, starts 0*/
            vSensorCallbackFunction); /*Name of callback function*/
    if(sensorTMR == NULL){
        haltAll(ERRORCODE);
    }else{
        if(xTimerStart(sensorTMR, 0) != pdPASS){
            haltAll(ERRORCODE);
        }
    }
}

void vLEDCallbackFunction( TimerHandle_t xTimer ){
//    dbgOutputEvent(LEDCALLBACK_START);
    static int state = 1;
    switch(state){
        case 0:
            PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);
            state = 1;
            break;
        case 1:
            PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);
            state = 0;
            break;
    }
//    dbgOutputEvent(LEDCALLBACK_END);
}

void createAndStartLEDTimer(){
    ledTMR = xTimerCreate
            ("LED_TMR", /*Text name, not used by RTOS*/
            pdMS_TO_TICKS(500), /*Timer period in MS, converts to ticks*/
            pdTRUE, /*Timer auto-reloads when expired*/
            (void * ) 0, /*Stores the count of times timer expires, starts 0*/
            vLEDCallbackFunction); /*Name of callback function*/
    if(ledTMR == NULL){
        haltAll(ERRORCODE);
    }else{
        if(xTimerStart(ledTMR, 0) != pdPASS){
            haltAll(ERRORCODE);
        }
    }
}

unsigned int pollADC(){
    unsigned int val = 0;
    DRV_ADC_Start();
    val = DRV_ADC_SamplesRead(0);
    DRV_ADC_Stop();
    dbgOutputVal(val >> 8);
    dbgOutputVal(val);
    return val;
}

unsigned int sensorStateMachine(){
    unsigned int avgVal = 0;
    enum State{first, second, third, fourth};
    enum State s = first;
    switch(s){
        case first:
            avgVal = pollADC();
            s = second;
        case second:
            avgVal += pollADC();
            s = third;
        case third:
            avgVal += pollADC();
            s = fourth;
        case fourth:
            avgVal += pollADC();
            return avgVal >> 2;
        default:
            haltAll(ERRORCODE);
    }
}

void SENSOR_Initialize ( void )
{
    dbgOutputEvent(SENSOR_INIT);
    sensorQueueCreate();
    DRV_ADC_Open();
}

void SENSOR_Tasks ( void )
{
    dbgOutputEvent(SENSOR_TASK_START);
    SensorMsg sm;
    int case_begin = 0;
    while(1){
        sm = sensorQueueRecv();
        switch(case_begin){
            case 0: // Waiting for message from RX
                if(sm.source == rx && sm.signal == 'g'){
                    dbgOutputEvent(SENSOR_RX_MSG);
                    createAndStartSensorTimer();
                    createAndStartLEDTimer();
                    case_begin = 1;
                }
                break;
            case 1: // Process sensor data
                if(sm.source == sensor){
                    dbgOutputEvent(SENSOR_SENSOR_MSG);
                    feedbackQueueSendFromSensor(sm.sensor);
                }else if(sm.source == rx){
                    
                }
                break;
        }
    }
}

 

/*******************************************************************************
 End of File
 */
