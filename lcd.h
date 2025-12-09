#ifndef __LCD_H__
#define __LCD_H__
#include "types.h"
void WriteLCD(u8 byte);
void CmdLCD(u8 CmdByte);
void Init_LCD(void);
void CharLCD(u8 asciiVal);
void StrLCD(s8*);
void U32LCD(u32);
void S32LCD(s32);
void F32LCD(f32,u32);
void BuildCGRAM(u8 *,u8);
#endif
