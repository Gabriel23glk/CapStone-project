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
#include "cartoon_Cat.h"
void setup();
void loop();
void onDataReceived(const uint8_t* data, size_t len,const BlePeerDevice& peer, void* context);
void pixelFill(int startPix,int endPix,int color);
#line 11 "c:/Users/gabea/Documents/IoT/capStone_Motor_01/src/capStone_Motor_01.ino"
const size_t UART_TX_BUF_SIZE = 4;
uint8_t txBuf[UART_TX_BUF_SIZE];
uint8_t h;
const byte SCAN_RESULT_MAX = 40;
BleScanResult scanResults[SCAN_RESULT_MAX];
// Declare Variables
byte count, i,j;
byte buf[BLE_MAX_ADV_DATA_LEN];
byte mac[SCAN_RESULT_MAX][6];
int8_t rssi[SCAN_RESULT_MAX];

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
SYSTEM_MODE(SEMI_AUTOMATIC);


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
  display.drawBitmap(16,20, myBitmap,112, 44, 1);
  display.display();
  // delay(1000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.setTextSize(2);
  display.setTextColor(BLACK,WHITE);
  display.printf("PlayTime!%c",33);
  display.display();
  display.clearDisplay();  
pinMode(D10,OUTPUT);
pixel.begin();
pixel.show();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    BLE.setScanTimeout(500);
    count=BLE.scan(scanResults,SCAN_RESULT_MAX);
    Serial.printf("%i devices found\n",count);
    for (int i=0; i < count; i++) {
        scanResults[i].advertisingData().get(BleAdvertisingDataType::MANUFACTURER_SPECIFIC_DATA, buf, BLE_MAX_ADV_DATA_LEN);
        for(j=0;j<6;j++){
            mac[i][j]=scanResults[i].address()[j];
            rssi[i]=scanResults[i].rssi();
        }
        if (mac[i][0]==0xFA &&mac[i][1]==0xDA){
            Serial.printf("FOUND=%02X:%02X:%02X:%02X:%02X:%02X,RSSI=%i\n",mac[i][0],mac[i][1],mac[i][2],mac[i][3],mac[i][4],mac[i][5],rssi[i]);
            if(rssi[i]>=-55){
            digitalWrite(D10,HIGH);
          
            }
            if(rssi[i]<=-60){
              digitalWrite(D10,LOW);
            }
        }
        // Serial.printf("MAC address = %02X:%02X:%02X:%02X:%02X:%02X. RSSI = %i\n",mac[i][0],mac[i][1],mac[i][2],mac[i][3],mac[i][4],mac[i][5],rssi[i]);
    }
  delay(5000);
  

  }



void onDataReceived(const uint8_t* data, size_t len,const BlePeerDevice& peer, void* context) {
    uint8_t h;
    Serial.printf("received data from:%02X:%02X:%02X:%02X:%02X:%02X\n", peer.address()
    [0], peer.address()[1], peer.address()[2], peer.address()[3], peer.address()[4], peer.address()[5]);
    // Serial.printf("Bytes:");
    for (h=0; h<len; h++) {
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
   pixelFill(startPixel,endPixel,color1);
  pixelFill(startPixel,endPixel,color2);
  pixel.clear();
}
}
void pixelFill(int startPix,int endPix,int color){
    for (pixelCount=startPix; pixelCount<=endPix; pixelCount=pixelCount+2){
      pixel.setPixelColor(pixelCount,color1);
      pixel.setPixelColor(pixelCount+1,color2); 
    }
}