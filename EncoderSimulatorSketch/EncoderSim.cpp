/** 
 * @file EncoderSim.cpp
 * @brief Module that provides functionality to simulate a quadrature encoder for testing decoding algorithms
 * @author Jack Duignan (Jackpduignan@gmail.com)
 * @date 2023-06-09
 */


// ===================================== Includes =====================================
#include "EncoderSim.h"

#include "Arduino.h"

#include <stdint.h>

// ===================================== Constants ====================================
#define LEAD_CW_PIN 2   // Pin that will lead when the encoder is rotating clockwise
#define LAG_CW_PIN 3    // Pin that will lag when the encoder is rotating clockwise

// ===================================== Globals ======================================
static bool leadPinState = 0;   // State of the lead pin
static bool lagPinState = 0;    // State of the lag pin

static bool requestRotateCW = false;    // Flag to indicate that the encoder should rotate clockwise
static bool requestRotateCCW = false; // Flag to indicate that the encoder should rotate counter clockwise

static int32_t encoderValue = 0;    // Value of the encoder (Increases when rotating clockwise, decreases when rotating counter clockwise)

// ===================================== Function Definitions =========================
static void rotateCW();
static void rotateCCW();

/**
 * @brief Initialize the encoder simulator
 * 
 */
void initEncoderSim() {
    pinMode(LEAD_CW_PIN, OUTPUT);
    pinMode(LAG_CW_PIN, OUTPUT);

    digitalWrite(LEAD_CW_PIN, LOW);
    digitalWrite(LAG_CW_PIN, LOW);
}

/**
 * @brief return the state of the lead pin
 * 
 * @return true lead pin is high
 */
bool getLeadPinState() {
    return leadPinState;
}

/**
 * @brief return the state of the lag pin
 * 
 * @return true lag pin is high
 */
bool getLagPinState() {
    return lagPinState;
}

/**
 * @brief Return the value of the encoder
 * 
 * @return the value of the encoder
 */
int32_t getEncoderValue() {
    return encoderValue;
}

/**
 * @brief Request the encoder rotate clockwise by one pulse 
 * 
 */
void requestEncoderRotateCW() {
    requestRotateCW = true;
}

/**
 * @brief Request the encoder rotate counter clockwise by one pulse 
 * 
 */
void requestEncoderRotateCCW() {
    requestRotateCCW = true;
}

/**
 * @brief Update the encoder pins to simulate rotation
 * 
 * @param Delay the delay in ms between state changes
 */
void updateEncoderPins(uint32_t delay) {
    static uint32_t lastUpdateTime = millis();

    uint32_t elapsedTime = millis() - lastUpdateTime;

    if (requestEncoderRotateCW && (elapsedTime > (delay + 10))) {
        rotateCW();
    }

    if (requestEncoderRotateCCW && (elapsedTime > (delay+ 10))) {
        rotateCCW();
    }

    lastUpdateTime = millis();
}

/**
 * @brief Rotate the encoder clockwise by one pulse
 * 
 */
static void rotateCW() {
    if (leadPinState == 0) {
        if (lagPinState == 0) {
            digitalWrite(LEAD_CW_PIN, HIGH);
            leadPinState = 1;
        } else {
            digitalWrite(LAG_CW_PIN, LOW);
            lagPinState = 0;
        }
    } else if (leadPinState == 1) {
        if (lagPinState == 0) {
            digitalWrite(LAG_CW_PIN, HIGH);
            lagPinState = 1;
        } else {
            digitalWrite(LEAD_CW_PIN, LOW); 
            leadPinState = 0;
        }
    } else {
        // Error
    }

    encoderValue++;
}

/**
 * @brief Rotate the encoder counter clockwise by one pulse
 * 
 */
static void rotateCCW() {
    if (leadPinState == 0) {
        if (lagPinState == 0) {
            digitalWrite(LAG_CW_PIN, HIGH);
            lagPinState = 1;
        } else {
            digitalWrite(LEAD_CW_PIN, LOW);
            leadPinState = 0;
        }
    } else if (leadPinState == 1) {
        if (lagPinState == 0) {
            digitalWrite(LEAD_CW_PIN, HIGH);
            leadPinState = 1;
        } else {
            digitalWrite(LAG_CW_PIN, LOW); 
            lagPinState = 0;
        }
    } else {
        // Error
    }

    encoderValue--;
}