/** 
 * @file EncoderSimulatorSketch.ino
 * @brief Encoder Simulator main Sketch
 * @author Jack Duignan (Jackpduignan@gmail.com
 * @date 2023-04-29
 */


// ===================================== Includes =====================================
#include <stdint.h>
#include <Arduino.h>


// ===================================== Constants ====================================
#define ENCODER_CHA_PIN 2
#define ENCODER_CHB_PIN 3

#define ENCODER_CLOCKWISE_BUTTON_PIN 4
#define ENCODER_COUNTERCLOCKWISE_BUTTON_PIN 5

#define ENCODER_SPEED_PIN A0
#define ENCODER_SPEED_MAX 505

// ===================================== Globals ======================================
uint8_t channelAState = 0;
uint8_t channelBState = 0;

// ===================================== Function Definitions =========================
/**
 * @brief rotate the encoder clockwise
 * 
 * @param encoderSpeed speed that the encoder will rotate at (delay in ms till next pulse can be sent)
 */
void rotateEncoderClockwise(uint32_t encoderSpeed) {
    // Rotate the encoder clockwise by one pulse

    if (channelBState == 0) {
        if (channelAState == 0) {
            digitalWrite(ENCODER_CHB_PIN, HIGH);
            channelBState = 1;
        } else {
            digitalWrite(ENCODER_CHA_PIN, LOW);
            channelAState = 0;
        }
    } else if (channelBState == 1) {
        if (channelAState == 0) {
            digitalWrite(ENCODER_CHA_PIN, HIGH);
            channelAState = 1;
        } else {
            digitalWrite(ENCODER_CHB_PIN, LOW); 
            channelBState = 0;
        }
    } else {
        // Error
    }

    delay(ENCODER_SPEED_MAX - encoderSpeed + 10);
}

/**
 * @brief rotate the encoder counter clockwise
 * 
 * @param encoderSpeed speed that the encoder will rotate at (delay in ms till next pulse can be sent)
 */
void encoder_rotateCounterClockwise(uint32_t encoderSpeed) {
    // Rotate the encoder counter clockwise by one pulse

    if (channelBState == 0) {
        if (channelAState == 0) {
            digitalWrite(ENCODER_CHA_PIN, HIGH);
            channelAState = 1;
        } else {
            digitalWrite(ENCODER_CHB_PIN, HIGH);
            channelBState = 1;
        }
    } else if (channelBState == 1) {
        if (channelAState == 0) {
            digitalWrite(ENCODER_CHB_PIN, LOW);
            channelBState = 0;
        } else {
            digitalWrite(ENCODER_CHA_PIN, LOW); 
            channelAState = 0;
        }
    } else {
        // Error
    }

    delay(ENCODER_SPEED_MAX - encoderSpeed + 10);
}

void setup() {
    // put your setup code here, to run once:
    // Pin Setup
    pinMode(ENCODER_CHA_PIN, OUTPUT);
    pinMode(ENCODER_CHB_PIN, OUTPUT);
    digitalWrite(ENCODER_CHA_PIN, LOW);
    digitalWrite(ENCODER_CHB_PIN, LOW);

    pinMode(ENCODER_CLOCKWISE_BUTTON_PIN, INPUT_PULLUP);
    pinMode(ENCODER_COUNTERCLOCKWISE_BUTTON_PIN, INPUT_PULLUP);

    pinMode(ENCODER_SPEED_PIN, INPUT);

    // Serial Setup
    Serial.begin(9600);
    Serial.println("Encoder Simulator");
}

void loop() {
    // put your main code here, to run repeatedly:
    // Read the encoder speed
    uint32_t encoderSpeed = analogRead(ENCODER_SPEED_PIN);

    // move the encoder
    if (digitalRead(ENCODER_CLOCKWISE_BUTTON_PIN) == LOW) {
        rotateEncoderClockwise(encoderSpeed);
    } else if (digitalRead(ENCODER_COUNTERCLOCKWISE_BUTTON_PIN) == LOW) {
        encoder_rotateCounterClockwise(encoderSpeed);
    } else {
        // Do nothing
    }

    // Print the encoder speed
    char string[100];

    snprintf(string, 100, "Encoder Value: %1d%1d, Encoder Speed %4d", channelAState, channelBState, encoderSpeed);
    Serial.println(string);
}
