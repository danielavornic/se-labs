#ifndef LCD_CONTROL_H
#define LCD_CONTROL_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <stdio.h>

extern FILE lcdOutput;

#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 22
#define LCD_D5 24
#define LCD_D6 26
#define LCD_D7 28

void lcdInit();

#endif