
/********************************************************************************
 *                  ___ ____    ____        _  __  __
 *                 |_ _|  _ \  / ___| _ __ (_)/ _|/ _| ___ _ __
 *                  | || |_) | \___ \| '_ \| | |_| |_ / _ \ '__|
 *                  | ||  _ <   ___) | | | | |  _|  _|  __/ |
 *                 |___|_| \_\ |____/|_| |_|_|_| |_|  \___|_|
 *
 ********************************************************************************
 *              Copyright (C) Gustavo Celani - All Rights Reserved
 *    Written by Gustavo Celani <gustavo_celani@hotmail.com>, July 2020
 ********************************************************************************
 * Creation Date: 09/07/2020
 * Creation Time: 19:21:55
 *
 * Version:  1.0
 * Compiler: gcc
 *
 * Author:   Gustavo Pasqua de Oliveira Celani
 * Social:   GC - Gustavo Celani (@gustavo_celani)
 * Email:    gustavo_celani@hotmail.com
 * Linkedin: https://br.linkedin.com/in/gustavocelani
 * Github:   https://github.com/gustavocelani
 *
 *******************************************************************************/

/**
 * Raw Samsung Send Example
 * 
 * unsigned int freq = 38;
 * unsigned int raw[] = {
 *     4500, 4500,  560, 1680,  560, 1680,  560, 1680,  560,  560,  560,  560,  560,  560,  560,  560,  560,
 *      560,  560, 1680,  560, 1680,  560, 1680,  560,  560,  560,  560,  560,  560,  560,  560,  560,  560,
 *      560,  560,  560, 1680,  560,  560,  560,  560,  560,  560,  560,  560,  560,  560,  560,  560,  560,
 *     1680,  560,  560,  560, 1680,  560, 1680,  560, 1680,  560, 1680,  560, 1680,  560, 1680,  560,  46946
 * };
 */

/**
 * Please, include the custom lib available on this project.
 * This custom IRremote library was modified to expose raw values
 */
#include <IRremote2.h>

// Digital Pin for 38B3v Ro7346 data
#define RECV_PIN 2
// General Input/Output Pins
#define GREEN_LED_PIN 12
#define RED_LED_PIN   13

// IRremote initialization
IRrecv irrecv(RECV_PIN);
// IRremote result structure
decode_results results;

/**
 * printResults
 */
void printResults(decode_results *results) {
    Serial.print("\nDecode Type................ ");
    switch (results->decode_type) {
        case NEC:
            Serial.println("NEC");
            break;
        case SONY:
            Serial.println("SONY");
            break;
        case RC5:
            Serial.println("RC5");
            break;
        case RC6:
            Serial.println("RC6");
            break;
        case DISH:
            Serial.println("DISH");
            break;
        case SHARP:
            Serial.println("SHARP");
            break;
        case PANASONIC:
            Serial.println("PANASONIC");
            break;
        case JVC:
            Serial.println("JVC");
            break;
        case SANYO:
            Serial.println("SANYO");
            break;
        case MITSUBISHI:
            Serial.println("MITSUBISHI");
            break;
        case SAMSUNG:
        case SAMSUNG2:
            Serial.println("SAMSUNG");
            break;
        case UNKNOWN:
        default:
            Serial.println("UNKNOWN");
            break;
    }

    Serial.print("Hex Value.................. 0x");
    Serial.println(results->value, HEX);

    Serial.print("Bits....................... ");
    Serial.println(results->bits, DEC);

    Serial.print("Raw Lenght................. ");
    Serial.println(results->rawlen, DEC);

    /**
     * Some libs drop the first value because they consider it like a "time gap"
     * Converts the data from ticks to microseconds
     * Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
     */
    Serial.println("\nRaw Pattern");

    Serial.print("Dec........................ [ ");
    for (int i = 0; i < results->rawlen; i++) {
        Serial.print(results->rawbuf[i], DEC);
        Serial.print(" ");
    }
    Serial.println("]");

    Serial.print("Hex........................ [ ");
    for (int i = 0; i < results->rawlen; i++) {
        Serial.print(results->rawbuf[i], HEX);
        Serial.print(" ");
    }
    Serial.println("]");

    Serial.print("Oct........................ [ ");
    for (int i = 0; i < results->rawlen; i++) {
        Serial.print(results->rawbuf[i], OCT);
        Serial.print(" ");
    }
    Serial.println("]");

    Serial.print("Time Based................. [ ");
    for (int i = 0; i < results->rawlen; i++) {
        Serial.print(((results->rawbuf[i] * USECPERTICK) - MARK_EXCESS), DEC);
        Serial.print(" ");
    }
    Serial.println("]");

    Serial.println("\n-----------------------------------------------------------------------------------------------------------");
}

/**
 * invertLedState
 */
void invertLedState() {
    digitalWrite(RED_LED_PIN,   !digitalRead(RED_LED_PIN));
    digitalWrite(GREEN_LED_PIN, !digitalRead(GREEN_LED_PIN));
}

/**
 * setup
 */
void setup() {
    // Starting serial communication
    Serial.begin(9600);

    // Pin definition
    pinMode(RED_LED_PIN,   OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);

    Serial.println("\n");
    Serial.println("\n-----------------------------------------------------------------------------------------------------------");
    Serial.println("                                ___ ____    ____        _  __  __                                            ");
    Serial.println("                               |_ _|  _ \\  / ___| _ __ (_)/ _|/ _| ___ _ __                                 ");
    Serial.println("                                | || |_) | \\___ \\| '_ \\| | |_| |_ / _ \\ '__|                             ");
    Serial.println("                                | ||  _ <   ___) | | | | |  _|  _|  __/ |                                    ");
    Serial.println("                               |___|_| \\_\\ |____/|_| |_|_|_| |_|  \\___|_|                                 ");
    Serial.println("\n-----------------------------------------------------------------------------------------------------------");

    // LED Initial state
    digitalWrite(RED_LED_PIN,   LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);

    // Enabling IR Input
    irrecv.enableIRIn();
}

/**
 * Main Loop
 */
void loop() {

    /**
     * This is not a block function
     */
    if (irrecv.decode(&results)) {
        invertLedState();
        printResults(&results);
        irrecv.resume();
        invertLedState();
    }
}
