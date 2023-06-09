/** 
 * @file EncoderSim.h
 * @brief Module that provides functionality to simulate a quadrature encoder for testing decoding algorithms
 * @author Jack Duignan (Jackpduignan@gmail.com)
 * @date 2023-06-09
 */


#ifndef ENCODERSIM_H
#define ENCODERSIM_H


// ===================================== Includes =====================================
#include <stdint.h>

// ===================================== Constants ====================================


// ===================================== Function Prototypes ==========================
// Initialization
void initEncoderSim();

// Getters
bool getLeadPinState();
bool getLagPinState();
int32_t getEncoderValue();

// Setters
void requestEncoderRotateCW();
void requestEncoderRotateCCW();

// Update
void updateEncoderSim();

#endif // ENCODERSIM_H