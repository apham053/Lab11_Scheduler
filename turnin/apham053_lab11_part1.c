/*	Author: apham053
 *  Partner(s) Name: Steven Rodriguez
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #1
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
#endif

enum STATES { START, OUT };

unsigned char B = 0;

int tick(int state) {
  unsigned char keypad_input;
  keypad_input = GetKeypadKey();
  switch(state) {
    case START:
	state = OUT;
	break;
    case OUT:
    switch(keypad_input) {
      case '\0':
      	                B = 0x1F;
                        break;
                        case '1':
                        B = 0x01;
                        break;
                        case '2':
                        B = 0x02;
                        break;
                        case '3':
                        B = 0x03;
                        break;
                        case '4':
                        B = 0x04;
                        break;
                        case '5':
                        B = 0x05;
                        break;
                        case '6':
                        B = 0x06;
                        break;
                        case '7':
                        B = 0x07;
                        break;
                        case '8':
                        B = 0x08;
                        break;
                        case '9':
                        B = 0x09;
                        break;
                        case 'A':
                        B = 0x0A;
                        break;
                        case 'B':
                        B = 0x0B;
                        break;
                        case 'C':
                        B = 0x0C;
                        break;
                        case 'D':
                        B = 0x0D;
                        break;
                        case '*':
                        B = 0x0E;
                        break;
                        case '0':
                        B = 0x00;
                        break;
                        case '#':
                        B = 0x0F;
                        break;
                        default:
                        B = 0x1B;
                        break;

    }
  }
    switch(state) {
        case START:
        break;
        case OUT:
        break;
        default:
        break;
    }

   state = OUT;
   PORTB = B;
   return state;
}

int main(void) {
    DDRA = 0xF0;
    DDRB = 0xFF;
    DDRD = 0xFF;
    PORTA = 0x0F;
    PORTB = 0x00;
    PORTD = 0x00;

    static task task1;
    task *tasks[] = { &task1};
    const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
    task1.state = 0;
    task1.period = 2;
    task1.elapsedTime = 2;
    task1.TickFct = &tick;
    TimerSet(100);
    TimerOn();

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
