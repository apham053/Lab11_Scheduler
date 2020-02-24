/*	Author: apham053
 *  Partner(s) Name: Steven Rodriguez
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#include "scheduler.h"
#include "keypad.h"
#include "io.c"
#endif

unsigned char B;
unsigned char save;
unsigned char flag;

enum STATES { START, OUT, PRESS };

int tick(int state) {
  unsigned char keypad_input;
  keypad_input = GetKeypadKey();
  switch(state) {
    case START:
        state = OUT;
        break;
    case OUT:
    if (flag == 0) {
            B = 0x1F;
            LCD_Cursor(1);
            LCD_WriteData(B + '0');
    }
    switch(keypad_input) {
            case '1':
            flag = 1;
            B = 0x01;
            LCD_Cursor(1);
            LCD_WriteData(B + '0');
            break;
            case '2':
            flag = 1;
            B = 0x02;
            LCD_Cursor(1);
            LCD_WriteData(B + '0');
            break;
            case '3':
            flag = 1;
            B = 0x03;
            LCD_Cursor(1);
            LCD_WriteData(B + '0');
            break;
            case '4':
            flag = 1;
            B = 0x04;
            LCD_Cursor(1);
            LCD_WriteData(B + '0');
            break;
            case '5':
            B = 0x05;
            LCD_Cursor(1);
            LCD_WriteData(B + '0');
            break;
            case '6':
            flag = 1;
            B = 0x06;
            LCD_Cursor(1);
            LCD_WriteData(B + '0');
            break;
            case '7':
            flag = 1;
            B = 0x07;
            LCD_Cursor(1);
            LCD_WriteData(B + '0');
            break;
            case '8':
            flag = 1;
            B = 0x08;
            LCD_Cursor(1);
            LCD_WriteData(B + '0');
            break;
            case '9':
            flag = 1;
            B = 0x09;
            LCD_Cursor(1);
            LCD_WriteData(B + '0');
            break;
            case 'A':
            flag = 2;
            B = 0x0A;
            LCD_Cursor(1);
            LCD_WriteData(B + 0x37);
            break;
            case 'B':
            flag = 2;
            B = 0x0B;
            LCD_Cursor(1);
            LCD_WriteData(B + 0x37);
            break;
            case 'C':
            flag = 2;
            B = 0x0C;
            LCD_Cursor(1);
            LCD_WriteData(B + 0x37);
            break;
            case 'D':
            flag = 2;
            B = 0x0D;
            LCD_Cursor(1);
            LCD_WriteData(B + 0x37);
            break;
            case '*':
            flag = 3;
            B = 0x0E;
            LCD_Cursor(1);
            LCD_WriteData(B + 0x1C);
            break;
            case '0':
            flag = 1;
            B = 0x00;
            LCD_Cursor(1);
            LCD_WriteData(B + '0');
            break;
            case '#':
            flag = 4;
            B = 0x0F;
            LCD_Cursor(1);
            LCD_WriteData(B + 0x14);
            break;
            default:
            break;
    }
    state = PRESS;
    PORTB = B;
    save = B;
    break;
    case PRESS:
    LCD_Cursor(1);
    switch(flag) {
      case 1:
      LCD_WriteData(save + '0');
      break;
      case 2:
      LCD_WriteData(save + 0x37);
      break;
      case 3:
      LCD_WriteData(save + 0x1C);
      break;
      case 4:
      LCD_WriteData(save + 0x14);
      break;
    }
    if (keypad_input != NULL) {
      state = OUT;
    } else {
      state = PRESS;
    }
    break;
  }
  switch(state) {
    case START:
      break;
    case OUT:
      break;
    case PRESS:
      break;
    default:
      break;
  }
  return state;
}
int main(void) {
  
    DDRA = 0xF0;
    DDRB = 0xFF;
    DDRC = 0xFF;
    DDRD = 0xFF;
    PORTA = 0x0F;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    
    static task task1;
    task *tasks[] = { &task1};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

     task1.state = 0;
     task1.period = 30;
     task1.elapsedTime = 10;
     task1.TickFct = &tick;

     TimerSet(100);
     TimerOn();
     LCD_init();

    unsigned short i; 
    while(1) {
      for ( i = 0; i < numTasks; i++ ) {
        if ( tasks[i]->elapsedTime == tasks[i]->period ) {
          tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
          tasks[i]->elapsedTime = 0;
        }
        tasks[i]->elapsedTime += 1;
      }
      while(!TimerFlag){}
      TimerFlag = 0;
    }
    return 0;
}
