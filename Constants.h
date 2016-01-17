
#pragma once

#define PWM_VALUE 63
int gamma_table[PWM_VALUE+1] = {
    0, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 9, 10,
    11, 12, 13, 15, 17, 19, 21, 23, 26, 29, 32, 36, 40, 44, 49, 55,
    61, 68, 76, 85, 94, 105, 117, 131, 146, 162, 181, 202, 225, 250,
    279, 311, 346, 386, 430, 479, 534, 595, 663, 739, 824, 918, 1023
};

// RGB FET
#define redPIN    15
#define greenPIN  13
#define bluePIN   12


// W FET
#define w1PIN     14
#define w2PIN     4

// onbaord green LED D1
#define LEDPIN    5
// onbaord red LED D2
#define LED2PIN   1

// The length of time the transition between colors takes.
#define TRANSITION_TIME 500


// note
// TX GPIO2 @Serial1 (Serial ONE)
// RX GPIO3 @Serial
