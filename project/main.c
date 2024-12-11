#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switch.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "sound.h"

//author ALEJANDRO SEDENO-GONZALEZ

int state = 0;
int next = 1;
int time = 0;
int change = 0;


u_char width = screenWidth, height = screenHeight;


int main(void){
  
  configureClocks();
  enableWDTInterrupts();
  led_init();
  switch_init();
  buzzer_init();
  lcd_init();

  or_sr(0x18);

}

void __interrupt_vec(PORT2_VECTOR) Port2(){
    if(P2IFG & SWITCHES){
        P2IFG &= ~SWITCHES;
        switch_interupt_handler();
    }
}

//width x height
void __interrupt_vec(WDT_VECTOR) WDT(){

    switch(state){
        case 0:
            if(next == 1){
                fillRectangle(0,0,width,height,COLOR_BLACK);
                drawString11x16(20,20,"Welcome", COLOR_RED, COLOR_BLACK);
                drawString11x16(50,40,"To", COLOR_RED, COLOR_BLACK);
                drawString11x16(25,60,"Police", COLOR_RED,COLOR_BLACK);
                drawString11x16(35,80,"Siren",COLOR_RED,COLOR_BLACK);
                drawString11x16(43,100,"Sim",COLOR_RED,COLOR_BLACK);
                buzzer_set_period(0);
                next = 0;
            }
            break;
        case 1:
            time++;
            if(time >= 150){
                change ^= 1;
                sound(change);
                lights(change);
                time = 0;
            }
            break;
        case 2:
            if(next == 1){
                buzzer_set_period(0);
                fillRectangle(0,0,width,height,COLOR_BLACK);
                drawString11x16(25,20,"JAIL :(", COLOR_RED, COLOR_BLACK);
                drawString11x16(40,60,"THE", COLOR_RED,COLOR_BLACK);
                drawString11x16(40,80,"END",COLOR_RED,COLOR_BLACK);
                next = 0;
            }


    }


}


