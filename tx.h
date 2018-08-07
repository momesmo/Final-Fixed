#ifndef _TX_H
#define _TX_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "debug.h"

#include "queues.h"
#include <stdio.h>
#include "timers.h"
#include "rx.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END 
    
//#define HTTP_GET "GET / HTTP/1.1\r\n\
//Host: 192.168.1.100:2000\r\n\r\n"
//    
//#define TEST_GET "GET / HTTP/1.1"
//    
//#define HTTP_POST "POST / HTTP/1.1\r\n\
//Content-Type: application/json\r\n\
//Content-length: %d\r\n\
//Host: 192.168.1.100:2000\r\n\r\n\
//{\"PICNUM\": %d, \"MSGID\": %d, \"EnLeft\": %d, \"EnRight\": %d}"
//
//#define HTTP_PUT "PUT / HTTP/1.1\r\n\
//Content-Type: application/json\r\n\
//Content-length: 0\r\n\
//Host: 192.168.1.100:2000\r\n\r\n"
    
#define JSON_SENSOR "{\"MSGID\": %u, \"SOURCE\": \"%s\", \"DATA\": %u}"
#define JSON_ERROR "{\"ERROR\": , %d}"
    
#define SOURCE_SENSOR "Sensor"
    
    
    void TX_Initialize ( void );
    void TX_Tasks( void );


#endif /* _TX_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

