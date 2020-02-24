/*	Author: apham053
 *  Partner(s) Name: Steven Rodriguez
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #2
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

enum STATES { START, OUT };

unsigned char B = 0;
unsigned char limit = 1;

const unsigned char HIMYM[66]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','C','S','1','2','0','B',' ','i','s',' ','L','e','g','e','n','d','.','.','.','w','a','i','t',' ','f','o','r',' ','i','t',' ','D','A','R','Y','!',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
int tick(int state) {
  switch(state) {
    case START:
        state = OUT;
        break;
    case OUT:
    for (unsigned char i = 1; i <= 16; i++) {
      LCD_Cursor(i);
      LCD_WriteData(HIMYM[limit+i-2]);
      if (limit+i+1 == 66) {
        limit = 1;
      }
    }
    limit = limit + 1;
    break;
    default:
	break;
  }
    switch(state) {
	case START:
	break;
	case OUT:
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
           task1.period = 2;
           task1.elapsedTime = 2;
           task1.TickFct = &tick;

           TimerSet(800);
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
