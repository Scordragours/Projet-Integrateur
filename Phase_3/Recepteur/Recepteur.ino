/*
 * Code realized by Pierre Forques A1
 * Goals : Receiving data from our group transmitter
 */
 
#include <VirtualWire.h>

/*--------------Setup variable--------------*/
//int code[4] = {97, 95, 119, 62}; 
int RF_RX_PIN = 8;
int code[3] = {71, 52, 62}; //G4>
int EOT[3] = {69, 79, 52}; //EO4
char ASCII[67] = {'.', '[', ']', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',/*--*/'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' /*--*/, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '>' };
int Decimal[67] = {46, 91, 93, 32, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,/*--*/65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, /*--*/ 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 62};

/*--------------Setup function--------------*/
void setup(){
  Serial.begin(9600);
  Serial.println("setup");
  vw_set_rx_pin(RF_RX_PIN);  // Setup receive pin.
  vw_setup(2000); // Transmission speed in bits per second.
  vw_rx_start(); // Start the PLL receiver.
}

/*--------------loop function--------------*/
void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if(vw_get_message(buf, &buflen)) // non-blocking I/O
  {   
    int j=0;
    boolean test=false;
    for(int i = 0; i < buflen; ++i)
    {
      //Protocole communication
      if(buf[i]==code[i] || test==true){ 
        j++;
        
        //Translate the decimal code in ASCII language
        for(int k = 0; k < 67 ; k++){
          if(buf[i]==Decimal[k]){
            Serial.print(ASCII[k]);
            Serial.println("EO4"); 
          }
        }
        
        //Allow the message to be received after our code
        if(j==3){
          test = true;
        }
       }    
     }    

    //Reset for the next message
    Serial.println(""); //retour à la ligne
      
    test=false; 
  }
}







      /*Serial.print("code =");
      Serial.print(code[i]);
      Serial.print(" ");
      Serial.print("buf =");
      Serial.print(buf[i]);
      Serial.print(" ");*/


          /*for(int i = 0; i < buflen; ++i)
    {
 
        if(buf[i]==code[i]){
          j++;
          Serial.print(buf[i], DEC);
          Serial.print(" ");
        if(j==4){
          for(i=4 ;i < buflen; ++i){
            Serial.print(buf[i], DEC);
            Serial.print(" ");
          }
        }
      }    
    }*/
