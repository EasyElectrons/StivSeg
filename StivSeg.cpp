#include "Arduino.h"
#include "StivSeg.h"

StivSeg::StivSeg(int numD, int dp[], int sp[], bool isCath) {
    numDigits = numD;
    isComCathode = isCath;
    
    for(int i = 0; i < numDigits; i++) {
        digitPins[i] = dp[i];
        pinMode(digitPins[i], OUTPUT);
    }
    
    for(int i = 0; i <= 7; i++) {
        segPins[i] = sp[i];
        pinMode(segPins[i], OUTPUT);
    }
    
    if(!isComCathode) {
        for(int i = 0; i < numDigits; i++) {
            digitalWrite(digitPins[i], HIGH);
        }
        
        for(int i = 0; i <= 7; i++) {
            digitalWrite(segPins[i], HIGH);
        }
    }
}

StivSeg::writeInt(int n) {
    int nray[numDigits];
    
    for(int i = 0; i < numDigits; i++) {
        nray[i] = n % 10;
        n /= 10;
    }
    
    if(isComCathode) {
        for(int dig = 0; dig < numDigits; dig++) {
            digitalWrite(digitPins[dig], LOW);
        
            for(int seg = 0; seg <= 6; seg++) {
                digitalWrite(segPins[seg], SYMBOL[nray[dig]][seg]);
            }
            delay(10);
            digitalWrite(digitPins[dig], HIGH);
        }
    }
    else {
        for(int dig = 0; dig < numDigits; dig++) {
            digitalWrite(digitPins[dig], HIGH);
        
            for(int seg = 0; seg <= 6; seg++) {
                digitalWrite(segPins[seg], !SYMBOL[nray[dig]][seg]);
            }
            delay(10);
            digitalWrite(digitPins[dig], LOW);
        }
    }
}

StivSeg::writeFloat(float n) {
    int nray[numDigits];
    int pointPos = numDigits + 1;
    
    while(n > 1.0) {
        n /= 10.0;
        pointPos--;
    }
    n *= (float)pow(10.0, (float)numDigits);
    
    for(int i = 0; i < numDigits; i++) {
        nray[i] = (int)n % 10;
        n /= 10;
    }
    if(isComCathode) {
        for(int dig = 0; dig < numDigits; dig++) {
            digitalWrite(digitPins[dig], LOW);
            
            for(int seg = 0; seg <= 6; seg++) {
                digitalWrite(segPins[seg], SYMBOL[nray[dig]][seg]);
            }
            
            if(pointPos == dig + 1) {
                digitalWrite(segPins[7], HIGH);
            }
            else {
                digitalWrite(segPins[7], LOW);
            }
            delay(10);
            digitalWrite(digitPins[dig], HIGH);
        }
    }
    else {
        for(int dig = 0; dig < numDigits; dig++) {
            digitalWrite(digitPins[dig], HIGH);
            
            for(int seg = 0; seg <= 6; seg++) {
                digitalWrite(segPins[seg], !SYMBOL[nray[dig]][seg]);
            }
            
            if(pointPos == dig + 1) {
                digitalWrite(segPins[7], LOW);
            }
            else {
                digitalWrite(segPins[7], HIGH);
            }
            delay(10);
            digitalWrite(digitPins[dig], LOW);
        }
    }
}

StivSeg::clear() {
    if(isComCathode) {
        for(int dig = 0; dig < numDigits; dig++) {
            digitalWrite(digitPins[dig], LOW);
        
            for(int seg = 0; seg <= 7; seg++) {
                digitalWrite(segPins[seg], LOW);
            }
        }
    }
    else {
        for(int dig = 0; dig < numDigits; dig++) {
            digitalWrite(digitPins[dig], HIGH);
        
            for(int seg = 0; seg <= 7; seg++) {
                digitalWrite(segPins[seg], HIGH);
            }
        }
    }
}