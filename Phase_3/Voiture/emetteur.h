#include <VirtualWire.h>
#define RF_TX_PIN 8

/* --- Prototype --- */
void sendResult(int, int, float, float);

/* --- Sent data to the receiver --- */
void sendResult(int x, int y, float parkingWidth, float currentSpeed)
{
  char bufferedMessage[25];
  char tempPW[6], tempCS[6];
  dtostrf(parkingWidth, 4, 2, tempPW);
  dtostrf(currentSpeed, 4, 2, tempCS);
  sprintf(bufferedMessage, "G4>[%d][%d][%s][%s]", x, y, tempPW, tempCS);

  Serial.println(bufferedMessage);

  vw_send((uint8_t *)bufferedMessage, strlen(bufferedMessage));
} 
