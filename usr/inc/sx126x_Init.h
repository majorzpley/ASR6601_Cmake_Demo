#ifndef __SX126X_INIT_H__
#define __SX126X_INIT_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "radio.h"
#include "sx126x.h"

#define REGION_CN470
#define SN_NUM 0x0024

#if defined(REGION_AS923)

#define RF_FREQUENCY 923000000 // Hz

#elif defined(REGION_AU915)

#define RF_FREQUENCY 915000000 // Hz

#elif defined(REGION_CN470)
#if ((SN_NUM) >= 0x0001 && (SN_NUM) <= 0x0012)
#define RF_FREQUENCY 470000000                   // Hz
#elif ((SN_NUM) >= 0x0013 && (SN_NUM) <= 0x0024) // 0
#define RF_FREQUENCY 470200000                   // Hz
#elif ((SN_NUM) >= 0x0025 && (SN_NUM) <= 0x0036) // 0
#define RF_FREQUENCY 470400000                   // Hz
#elif ((SN_NUM) >= 0x0037 && (SN_NUM) <= 0x0048) // 0
#define RF_FREQUENCY 470600000                   // Hz
#elif ((SN_NUM) >= 0x0049 && (SN_NUM) <= 0x0060) // 0
#define RF_FREQUENCY 470800000                   // Hz
#elif ((SN_NUM) >= 0x0061 && (SN_NUM) <= 0x0072) // 0
#define RF_FREQUENCY 471000000                   // Hz
#elif ((SN_NUM) >= 0x0073 && (SN_NUM) <= 0x0084) // 0
#define RF_FREQUENCY 471200000                   // Hz
#elif ((SN_NUM) >= 0x0085 && (SN_NUM) <= 0x0096) // 0
#define RF_FREQUENCY 471400000                   // Hz
#elif ((SN_NUM) >= 0x0097 && (SN_NUM) <= 0x0106) // 0
#define RF_FREQUENCY 471600000                   // Hz
#endif
#elif defined(REGION_CN779)

#define RF_FREQUENCY 779000000 // Hz

#elif defined(REGION_EU433)

#define RF_FREQUENCY 433000000 // Hz

#elif defined(REGION_EU868)

#define RF_FREQUENCY 868000000 // Hz

#elif defined(REGION_KR920)

#define RF_FREQUENCY 920000000 // Hz

#elif defined(REGION_IN865)

#define RF_FREQUENCY 865000000 // Hz

#elif defined(REGION_US915)

#define RF_FREQUENCY 915000000 // Hz

#elif defined(REGION_US915_HYBRID)

#define RF_FREQUENCY 915000000 // Hz

#else
#error "Please define a frequency band in the compiler options."
#endif

#define TX_OUTPUT_POWER 0 // dBm

#if defined(USE_MODEM_LORA)

#define LORA_BANDWIDTH 0         // [0: 125 kHz,
                                 //  1: 250 kHz,
                                 //  2: 500 kHz,
                                 //  3: Reserved]
#define LORA_SPREADING_FACTOR 10 // [SF7..SF12]
#define LORA_CODINGRATE 1        // [1: 4/5,
                                 //  2: 4/6,
                                 //  3: 4/7,
                                 //  4: 4/8]
#define LORA_PREAMBLE_LENGTH 8   // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT 0    // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON false
#define LORA_IQ_INVERSION_ON false

#elif defined(USE_MODEM_FSK)

#define FSK_FDEV 25000          // Hz
#define FSK_DATARATE 50000      // bps
#define FSK_BANDWIDTH 50000     // Hz >> DSB in sx126x
#define FSK_AFC_BANDWIDTH 83333 // Hz
#define FSK_PREAMBLE_LENGTH 5   // Same for Tx and Rx
#define FSK_FIX_LENGTH_PAYLOAD_ON false

#else
#error "Please define a modem in the compiler options."
#endif

typedef enum
{
    LOWPOWER,
    RX,
    RX_TIMEOUT,
    RX_ERROR,
    TX,
    TX_TIMEOUT,
    Null
} States_t;

#define RX_TIMEOUT_VALUE 0
#define BUFFER_SIZE 5 // Define the payload size here

/*!
 * Radio events function pointer
 */
RadioEvents_t RadioEvents;

/*!
 * \brief Function to be executed on Radio Tx Done event
 */
void OnTxDone(void);

/*!
 * \brief Function to be executed on Radio Rx Done event
 */
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);

/*!
 * \brief Function executed on Radio Tx Timeout event
 */
void OnTxTimeout(void);

/*!
 * \brief Function executed on Radio Rx Timeout event
 */
void OnRxTimeout(void);

/*!
 * \brief Function executed on Radio Rx Error event
 */
void OnRxError(void);

void LoRa_Init(void);
void Radio_Send(uint8_t *pData, unsigned char len, uint16_t time_out);
#endif
