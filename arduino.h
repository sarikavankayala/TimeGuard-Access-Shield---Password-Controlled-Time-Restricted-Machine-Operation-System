#ifndef __ARDUINO_H__
#define __ARDUINO_H__
#include "types.h"
void pinMode(u32 pinNo,u32 pindir);
void digitalWrite(u32 pinNo,u32 bit);
u32 digitalRead(u32 pinNo);
void portMode(u32 pinstartNo,u32 npins,u32 pindir);
void write2pins(u32 pinstartNo,u32 npins,u32 bit);
u32 read2pins(u32 pinstartNo,u32 npins);
#endif
