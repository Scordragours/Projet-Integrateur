#include <SharpIR.h>

#define model 1080
#define PIN 1
#define led 13
#define I2C_ADDRESS 0x0f
#define PI 3.1415926535897932384626433832795
#define NOTCH 20
#define DIAMETER 0.064
#define SPEEDSENSOR 5

/*------------------------Prototypes------------------------*/
float calcul();
float getTimeTraveled();
void checkDistance();
float getTime();
void speedCalculator();


/* --- Setup Speed Calculation Variables --- */
unsigned long speedTimer;
int currentState = 0;
int previousState = 0;
int notchCounter = 0; 
float currentRevolutions = 0; 
float revolutionPerMinute = 0;
float currentSpeed = 0; 


/*                  Code Arduino C++ 
    Goals of this code : calculate the distance in meter
    of a parking space
    19/06/19 by Pierre FORQUES
                                                        */



/*------------------Setup Variable------------------*/
SharpIR IR_Sensor_1(PIN, model);            //Sensor distance 
float t[2];                                 //Time
int a = 0;                                  //declaration : count lap
int previousRange;                      //previous range detected
unsigned long lastTimeDistanceChecked = 0;

/*------------------Calculation Distance Function------------------*/  
float calcul(){ //v=d/t :: D=V*t
  float distance = currentSpeed * getTimeTraveled();
  Serial.println(distance);
  return distance;
}

/*------------------Gets Subtraction Time------------------*/
float getTimeTraveled(){
  return t[1] - t[0];
}

/*---------------Check if there is a parking space---------------*/
void checkDistance(){
  if(millis() - lastTimeDistanceChecked >= 100)
  {
    int currentRange = IR_Sensor_1.distance();
    if(currentRange - previousRange > previousRange/2 || previousRange - currentRange > currentRange/2)
    {
      //digitalWrite(led, HIGH);
      t[a] = getTime();
      a++;
    }else{
      //digitalWrite(led, LOW);
    }
    previousRange = currentRange;
    lastTimeDistanceChecked = millis();
  }
}

/*void checkDistance(){
  int range = IR_Sensor_1.distance();
  delay(150);
  int new_range = IR_Sensor_1.distance();
  if(new_range - range > range/2 || range - new_range > new_range/2){ 
    //digitalWrite(led, HIGH);
    t[a] = getTime();
    a++;
  }else{
    //digitalWrite(led, LOW);
  }
}*/

/*--------------Gets the time in second--------------*/
float getTime(){ 
  return micros()/1000000;
}

/*--------------Calculate the speed over 5 seconds--------------*/
void speedCalculator()
{
  currentState = digitalRead(SPEEDSENSOR);
  
  if(currentState == HIGH && previousState == LOW)
  {
    previousState = currentState;
    notchCounter++; 
  }
  else if (currentState == LOW && previousState == HIGH)
  {
    previousState = currentState;
  }
  
  if(notchCounter == NOTCH)
  {
    Serial.println("1 tour");
    currentRevolutions++; 
    notchCounter = 0;
  }
  if(millis()-speedTimer >= 5000)
  {
    if(notchCounter != NOTCH)
    {
      revolutionPerMinute = (currentRevolutions + (notchCounter/NOTCH))*12;
    }else{
      revolutionPerMinute = currentRevolutions*12;
    }
    currentSpeed = (revolutionPerMinute*(DIAMETER*PI)/60);
    
    Serial.print(revolutionPerMinute);
    Serial.print(" RPM || ");
    Serial.print(currentSpeed);
    Serial.println(" m/s");
    notchCounter = 0;
    currentRevolutions = 0;
    speedTimer = millis();
  }
}
