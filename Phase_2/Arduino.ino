#include <Grove_I2C_Motor_Driver.h>
#define I2C_ADDRESS 0x0f

 int vitesse = 255;

int signalPinMilieu = 4;
int signalPinDroit = 3;
int signalPinGauche = 2;
boolean run=true;

void setup(){
  pinMode(signalPinMilieu, INPUT);
  pinMode(signalPinDroit, INPUT);
  pinMode(signalPinGauche, INPUT);
  boolean interruption=true;
  Motor.begin(I2C_ADDRESS);
  Serial.begin(9600);
  Serial.println("xx11");
}

void loop(){
  checkCapteur();
}

/*---------------------------*/
void checkCapteur(){
  int PathFinding = random(1,3);
  if((digitalRead(signalPinDroit) == HIGH)&&(digitalRead(signalPinMilieu) == HIGH)&&(digitalRead(signalPinGauche) == HIGH)){
    PathFinding = random(1,4);
    Serial.println(PathFinding);
    switch(PathFinding){
      case 1:
        tournerDroite(false);
        break;
      case 2:
        avancer();
        break;
      case 3:
        tournerGauche(false);
        break;
    }
  }else if((digitalRead(signalPinGauche) == HIGH)&&(digitalRead(signalPinDroit) == HIGH)){
    Serial.println(PathFinding);
    switch(PathFinding){
      case 1:
        tournerGauche(false);
        break;
      case 2:
        tournerDroite(false);
        break;
    }
  }else if((digitalRead(signalPinGauche) == HIGH)&&(digitalRead(signalPinMilieu) == HIGH)){
    Serial.println(PathFinding);
    switch(PathFinding){
      case 1:
        tournerGauche(false);
        break;
      case 2:
        avancer();
        break;
    }
  }else if((digitalRead(signalPinDroit) == HIGH)&&(digitalRead(signalPinMilieu) == HIGH)){
    Serial.println(PathFinding);
    switch(PathFinding){
      case 1:
        tournerDroite(false);
        break;
      case 2:
        avancer();
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
    Motor.speed(MOTOR1, 0-vitesse);

    if(isAmbiguous)
    {
      for(int i = 0; i < 200; i++)
      {
        if((digitalRead(signalPinMilieu) == HIGH))
        {
          rattraperGauche();
          return;
        }
        delay(0.5);
      }
    }else{
      delay(100);
    }
}

/*--------------------------*/
void tournerDroite(bool isAmbiguous){
    Motor.speed(MOTOR1, vitesse);
    Motor.speed(MOTOR2, 0-vitesse);

    if(isAmbiguous)
    {
      for(int i = 0; i < 200; i++)
      {
        if((digitalRead(signalPinMilieu) == HIGH))
        {
          rattraperDroite();
          return;
        }
        delay(0.5);
      }
    }else{
      delay(100);
    }
}
