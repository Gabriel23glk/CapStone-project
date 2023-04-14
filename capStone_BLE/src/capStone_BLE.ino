/*
 * Project capStone_BLE
 * Description:testing the BLE beacon and the distance measured from the Argon
 * Author:Gabriel Arnold
 * Date:04-13-23
 */

const size_t UART_TX_BUF_SIZE = 4;
uint8_t txBuf[UART_TX_BUF_SIZE];
uint8_t h;

const BleUuid serviceUuid("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid rxUuid("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");
const BleUuid txUuid("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");

BleCharacteristic txCharacteristic("tx", BleCharacteristicProperty::NOTIFY, txUuid, serviceUuid);
BleCharacteristic rxCharacteristic("rx", BleCharacteristicProperty::WRITE_WO_RSP, rxUuid, serviceUuid, onDataReceived, NULL);
BleAdvertisingData data;

// Create BLE Scanner Object
const byte SCAN_RESULT_MAX = 40;
BleScanResult scanResults[SCAN_RESULT_MAX];
// Declare Variables
byte count, i,j;
byte buf[BLE_MAX_ADV_DATA_LEN];
byte mac[SCAN_RESULT_MAX][6];
int8_t rssi[SCAN_RESULT_MAX];
SYSTEM_MODE(SEMI_AUTOMATIC);
void setup() {
    Serial.begin(9600);
    waitFor(Serial.isConnected,10000);
    BLE.on();
    BLE.addCharacteristic(txCharacteristic);
    BLE.addCharacteristic(rxCharacteristic);
    data.appendServiceUUID(serviceUuid);
    BLE.advertise(&data);
}
void loop() {
    // Only scan for 500 milliseconds
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
        }
        Serial.printf("MAC address = %02X:%02X:%02X:%02X:%02X:%02X. RSSI = %i\n",mac[i][0],mac[i][1],mac[i][2],mac[i][3],mac[i][4],mac[i][5],rssi[i]);
    }
  delay(5000);
}
void onDataReceived(const uint8_t* data, size_t len,const BlePeerDevice& peer, void* context) {
    uint8_t h;
    Serial.printf("received data from:%02X:%02X:%02X:%02X:%02X:%02X\n", peer.address()
    [0], peer.address()[1], peer.address()[2], peer.address()[3], peer.address()[4], peer.address()[5]);
    Serial.printf("Bytes:");
    for (h=0; h<len; h++) {
        Serial.printf("%02X",data[i]);
}
}