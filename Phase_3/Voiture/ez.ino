#include <Scheduler.h>

#include <ArduinoSTL.h>

#include "library_T.h"
#include "Distance.h"
#include <Grove_I2C_Motor_Driver.h>
#include "emetteur.h"
#define I2C_ADDRESS 0x0f

int vitesse = 90;
int signalPinMilieu = 4;
int signalPinDroit = 3;
int signalPinGauche = 2;
boolean run=true;
int state = 0;
bool isArrived = false; 


void setup(){
  vw_set_tx_pin(RF_TX_PIN); // Setup transmit pin
  vw_setup(2000); // Transmission speed in bits per second.
  Serial.begin(9600);
  Trajet(Depart);
  Serial.println(State_Vehicule.size());
  for(int i = 0; i < State_Vehicule.size(); i++){
    Serial.println(State_Vehicule.at(i));
  }
  
  pinMode(signalPinMilieu, INPUT);
  pinMode(signalPinDroit, INPUT);
  pinMode(signalPinGauche, INPUT);
  boolean interruption=true;
  Motor.begin(I2C_ADDRESS);
  Serial.begin(9600);
  Serial.println("xx11");


  previousRange = IR_Sensor_1.distance();
  Scheduler.startLoop(loopMoving);
  
}

void loop(){
  speedCalculator();
  if(a != 2){
    checkDistance();
  }else{
    sendResult(5, 11, calcul(), currentSpeed);
    a = 0;
  }
  yield();
}

void loopMoving(){
  //checkCapteur();
  Serial.println("je bouge");
  Motor.speed(MOTOR2, 100);
  Motor.speed(MOTOR1, 100);

  /*while(isArrived)
  {
    Motor.speed(MOTOR2, 0);
    Motor.speed(MOTOR1, 0);

    delay(10000);
  }*/

  
  delay(5000);
}

/*---------------------------*/
void checkCapteur(){
  
  if((digitalRead(signalPinDroit) == HIGH)&&(digitalRead(signalPinMilieu) == HIGH)&&(digitalRead(signalPinGauche) == HIGH)){
    if(State_Vehicule.size() <= state)
    {
      isArrived = true;
      return;
    }
    switch(State_Vehicule.at(state))
    {
      case 'D':
        state++;
        tournerGauche(false);
        break;
      case 'G':
        state++;
        tournerDroite(false);
        break;
      case 'A':
        state++;
        avancer();
        delay(200);
        break;
    }
  }else if((digitalRead(signalPinGauche) == HIGH)&&(digitalRead(signalPinDroit) == HIGH)){
    if(State_Vehicule.size() <= state)
    {
      isArrived = true;
      return;
    }
    switch(State_Vehicule.at(state))
    {
      case 'D':
        state++;
        tournerGauche(false);
        break;
      case 'G':
        state++;
        tournerDroite(false);
        break;
      case 'A':
        break;
    }
  }else if((digitalRead(signalPinGauche) == HIGH)&&(digitalRead(signalPinMilieu) == HIGH)){
    if(State_Vehicule.size() <= state)
    {
      isArrived = true;
      return;
    }
    switch(State_Vehicule.at(state))
    {
      case 'D':
        state++;
        tournerGauche(false);
        break;
      case 'G':
        break;
      case 'A':
        state++;
        avancer();
        delay(200);
        break;
    }
  }else if((digitalRead(signalPinDroit) == HIGH)&&(digitalRead(signalPinMilieu) == HIGH)){
    if(State_Vehicule.size() <= state)
    {
      isArrived = true;
      return;
    }
    switch(State_Vehicule.at(state))
    {
      case 'D':
        break;
      case 'G':
        state++;
        tournerDroite(false);
        break;
      case 'A':
        state++;
        avancer();
        delay(200);
        break;
    }
  }else if((digitalRead(signalPinGauche) == HIGH)){
      tournerGauche(true);
  }else if((digitalRead(signalPinDroit) == HIGH)){
    tournerDroite(true);
  }else if((digitalRead(signalPinMilieu) == HIGH)){
    avancer();
  }
}

void rattraperGauche()
{
    Motor.speed(MOTOR1, vitesse);
    Motor.speed(MOTOR2, 0-vitesse);

    delay(40);
}

void rattraperDroite()
{
    Motor.speed(MOTOR2, vitesse);
    Motor.speed(MOTOR1, 0-vitesse);

    delay(40);
}

/*---------------------------*/
void avancer(){
    Motor.speed(MOTOR1, vitesse);
    Motor.speed(MOTOR2, vitesse);
}

/*--------------------------*/
void tournerGauche(bool isAmbiguous){
    Motor.speed(MOTOR2, vitesse);
    Motor.speed(MOTOR1, 0-vitesse*0.9);

    if(isAmbiguous)
    {
      for(int i = 0; i < 2000; i++)
      {
        if((digitalRead(signalPinMilieu) == HIGH))
        {
          rattraperGauche();
          return;
        }
        delay(0.5);
      }
      /*if(State_Vehicule.at(state) == 'D'){
        state++;
      }*/
    }else{
      /*delay(50);
     while(digitalRead(signalPinMilieu) == LOW)
      {
        delay(0.5);
      }*/
      delay(500);
    }
}

/*--------------------------*/
void tournerDroite(bool isAmbiguous){
    Motor.speed(MOTOR1, vitesse);
    Motor.speed(MOTOR2, 0-vitesse*0.9);

    if(isAmbiguous)
    {
      for(int i = 0; i < 2000; i++)
      {
        if((digitalRead(signalPinMilieu) == HIGH))
        {
          rattraperDroite();
          return;
        }
        delay(0.5);
      }
      /*if(State_Vehicule.at(state) == 'G'){
        state++;
      }*/
    }else{
      /*delay(50);
      while(digitalRead(signalPinMilieu) == LOW)
      {
        delay(0.5);
      }*/
      delay(500);
    }
}
