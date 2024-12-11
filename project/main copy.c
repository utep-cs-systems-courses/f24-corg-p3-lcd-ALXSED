#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switch.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

int state = 0;
//make state one be a starting screen that says something like police siren sim then press switch 2 to go to the siren
// the siren is a assembly file that just checks the time and every time a second goes by it goes from wee aka blue to woo red
// the assembly flie will call on two functions the wee method that makes the sound wee or woo 
//switch 3 goes to the end screen 
//sw1 start menu
//sw2 siren simulator
//sw3 end screen

int main(void){
  
  configureClocks();
  enableWDTInterrupts();
  led_init();
  switch_init();
  buzzer_init();

  or_sr(0x18);

}

void __interrupt_vec(PORT2_VECTOR) Port2(){
    if(P2IFG & SWITCHES){
        P2IFG &= ~SWITCHES;
        switch_interupt_handler();
    }
}


void __interrupt_vec(WDT_VECTOR) WDT(){

    switch(state){
        case 0:
            drawString11x16(20,20,"hello", COLOR_GREEN, COLOR_RED);
            break;

    }


}


