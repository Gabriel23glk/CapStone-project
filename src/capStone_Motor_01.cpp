/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/gabea/Documents/IoT/capStone_Motor_01/src/capStone_Motor_01.ino"
/*
 * Project capStone_Motor_01
 * Description:Ball of furry is a toy designed with a motor to keep running to keep pets entertained  
 * Author:Gabriel Arnold-Jecker
 * Date:04-11-23
 */
#include "neopixel.h"
#include "Adafruit_SSD1306.h"
#include "colors.h"
void setup();
void loop();
void onDataReceived(const uint8_t* data, size_t len,const BlePeerDevice& peer, void* context);
void pixelFill(int startPix,int endPix,int color);
#line 10 "c:/Users/gabea/Documents/IoT/capStone_Motor_01/src/capStone_Motor_01.ino"
const size_t UART_TX_BUF_SIZE = 4;
uint8_t txBuf[UART_TX_BUF_SIZE];
uint8_t i;

// These UUIDs were defined by Nordic Semiconductor and are now the defacto standard for
// UART-like services over BLE. Many apps support the UUIDs now, like the Adafruit Bluefruit app.
const BleUuid serviceUuid("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid rxUuid("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid txUuid("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");

BleCharacteristic txCharacteristic("tx", BleCharacteristicProperty::NOTIFY, txUuid, serviceUuid);
BleCharacteristic rxCharacteristic("rx", BleCharacteristicProperty::WRITE_WO_RSP, rxUuid, serviceUuid, onDataReceived, NULL);
BleAdvertisingData data;
const int OLED_RESET=4;
bool OnorOff;
int startPixel=0;
int endPixel=15;
int pixelPosition;
int color1=red;
int color2=blue;
int pixelCount;
const int PIXELPIN=A3;
const int PIXELNUMBER=15;
Adafruit_NeoPixel pixel(PIXELNUMBER,PIXELPIN,WS2812B);
Adafruit_SSD1306 display(OLED_RESET);
void setup() {
 Serial.begin(9600);
  waitFor(Serial.isConnected, 15000);
    BLE.on();
    BLE.addCharacteristic(txCharacteristic);
    BLE.addCharacteristic(rxCharacteristic);
    data.appendServiceUUID(serviceUuid);
    BLE.advertise(&data);
    Serial.printf("Argon BLE Address:%s\n",BLE.address().toString().c_str());
display.begin (SSD1306_SWITCHCAPVCC, 0x3c);
  display.display();
  display.clearDisplay();
  display.display();
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.setTextSize(2);
  display.setTextColor(BLACK,WHITE);
  display.printf("PlayTime!%c",33);
  display.display();
  display.clearDisplay();
  // display.drawBitmap(16,20, myBitmap,112, 44, 1);
pinMode(D10,OUTPUT);
pixel.begin();
pixel.show();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {

}
void onDataReceived(const uint8_t* data, size_t len,const BlePeerDevice& peer, void* context) {
    uint8_t i;
    Serial.printf("received data from:%02X:%02X:%02X:%02X:%02X:%02X\n", peer.address()
    [0], peer.address()[1], peer.address()[2], peer.address()[3], peer.address()[4], peer.address()[5]);
    // Serial.printf("Bytes:");
    for (i=0; i<len; i++) {
        Serial.printf("%02X",data[i]);
}
Serial.printf("\n");
Serial.printf("Message: %s\n",(char*)data);
OnorOff=atoi((char*)data);
if (OnorOff==1){
  digitalWrite(D10,HIGH);
  Serial.printf("Turn on button%i\n",OnorOff);
  pixel.clear();
  pixelFill(startPixel,endPixel,color1);
  pixelFill(startPixel,endPixel,color2);
  pixel.show();
}
if(OnorOff==0){
  digitalWrite(D10,LOW);
  ("turn off button%i\n",OnorOff);
  pixel.clear();
}
}
void pixelFill(int startPix,int endPix,int color){
    for (pixelCount=startPix; pixelCount<=endPix; pixelCount=pixelCount+2){
      pixel.setPixelColor(pixelCount,color1);
      pixel.setPixelColor(pixelCount+1,color2); 
    }
}