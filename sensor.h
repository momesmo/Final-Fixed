#ifndef _SENSOR_H
#define _SENSOR_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"

#include "queues.h"
#include "debug.h"
#include "timers.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END
    
    typedef struct sensorData {
        
    } SensorData;
    
    TimerHandle_t sensorTMR;
    TimerHandle_t ledTMR;
    SensorData sData;
    
    void vSensorCallbackFunction( TimerHandle_t xTimer );
    void createAndStartSensorTimer();
    void vLEDCallbackFunction( TimerHandle_t xTimer );
    void createAndStartLEDTimer();
    
    unsigned int pollADC();
    unsigned int sensorStateMachine();
    
    void SENSOR_Initialize ( void );
    void SENSOR_Tasks( void );


#endif /* _SENSOR_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

