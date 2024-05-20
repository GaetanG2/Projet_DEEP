/*
 * servo.c
 *
 *  Created on: 26 sept. 2023
 *      Author: Personnel
 */
#include "servo.h"
#define PERIOD_TIMER 10
static uint16_t current_position;

 void SERVO_init(void){
 //initialisation et lancement du timer1 à une période de 10 ms
 TIMER_run_us(TIMER1_ID, PERIOD_TIMER*1000, FALSE); //10000us = 10ms
 //activation du signal PWM sur le canal 1 du timer 1 (broche PA8)
 TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_1, 150, FALSE, FALSE);
 //rapport cyclique reglé pour une position servo de 50%
 SERVO_set_position(100);
 }
 /*void SUN_TRACKER_set_new_pos(double latitude, double longitude){
	 loc.latitude;

 }*/

 //position est exprimée de 0 à 100.
 void SERVO_set_position(uint16_t position){
 if(position > 100){
 position = 100;
 current_position = position;

 //écretage si l'utilisateur demande plus de 100%
 //TODO : mise à jour du rapport cyclique.
 //duty doit être exprimé ici de 100 à 200 (sur 1000) (pour un rapport cyclique
 //de 10% à 20%, cest-à-dire une durée de pulse de 1 à 2ms dans la période de 10ms)
 //Donc on additionne 100 à position.
  }
 position+=100;
 TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_1, position);
 }

 void SERVO_process_test(void)
 {
 static uint16_t position = 50;
 static bool_e previous_button = FALSE;
 bool_e current_button;
 //lecture du bouton bleu
 current_button = !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
 if(current_button && !previous_button) //si appui bouton
 {
      position = (position > 99)?0:(position+5); //de 0 à 100%, par pas de 5%
      SERVO_set_position(position);
 }
 previous_button = current_button; //sauvegarde pour le prochain passage
 HAL_Delay(10); //anti-rebond "de fortune" en cadencant la lecture du bouton
 }
