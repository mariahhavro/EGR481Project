//Name: Mariah Havro
//Date: 04/27/2021
//Class: EGR 481
//Project Name: Whack a Mole

/* Based on example PeriodicTimer0AInts.c from the book:
	"Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
  Program 7.5, example 7.6
	*/


#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "../inc/PLL.h"
#include "../inc/Timer0A.h"
#include "../inc/CortexM.h"
#include "../inc/LaunchPad.h"
#include <stdlib.h>


#define WHEELSIZE 4
const uint32_t COLORWHEEL[WHEELSIZE] = {RED, BLUE+RED, BLUE, 0};
uint32_t currColor; //global to hold current color, used to check if switch is correct

uint32_t switchInput;

int score = 0; //to hold current score
const int WIN_SCORE = 1; //score user needs to win, white will show

// if desired interrupt frequency is f, Timer0A_Init parameter is busfrequency/f
#define F2HZ (80000000/20)
#define F20KHZ (80000000/20000)

void Game(void){
  static uint32_t i = 0;
	switchInput = LaunchPad_Input();
	currColor = COLORWHEEL[i];
  LaunchPad_Output(currColor);
	i = rand() % WHEELSIZE;
}

//debug code
int main(void){ 
  PLL_Init(Bus80MHz);              // bus clock at 80 MHz
  LaunchPad_Init();                // activate port F
  EnableInterrupts();
	
	while(1){
		//Timer0A_Init(&Game, F2HZ,2);  // initialize timer0A (2 Hz)
    switchInput = LaunchPad_Input();
		
		if(switchInput == 3){ //both switches hit to start game
			while(score < WIN_SCORE){
				Timer0A_Init(&Game, F2HZ,2);  // initialize timer0A (2 Hz)
				WaitForInterrupt();
				if(switchInput == 2){ //switch 1
					if(currColor == RED){
						score++;
					}
				}
				if(switchInput == 1){ //switch 2
					if(currColor == BLUE){
						score++;
					}
				}
			}
			Timer0A_Stop();
			LaunchPad_Output(WHITE);
		}
  }
}
