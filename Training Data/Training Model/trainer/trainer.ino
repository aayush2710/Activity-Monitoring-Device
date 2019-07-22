#include <CurieBLE.h>
#include "CurieIMU.h"

BLEPeripheral blePeripheral;       // BLE Peripheral Device (the board you're programming)
BLEService ActivityMonitor("180D"); // BLE Heart Rate Service

// BLE Heart Rate Measurement Characteristic"
BLECharacteristic activityChar("2A37",  // standard 16-bit characteristic UUID
    BLERead | BLENotify, 2);  
    

long previousMillis = 0;  

void setup() {
  Serial.begin(9600);    // initialize serial communication
  pinMode(13, OUTPUT);   // initialize the LED on pin 13 to indicate when a central is connected

  /* Set a local name for the BLE device
     This name will appear in advertising packets
     and can be used by remote devices to identify this BLE device
     The name can be changed but maybe be truncated based on space left in advertisement packet */
  blePeripheral.setLocalName("ActivityMonitor");
  blePeripheral.setAdvertisedServiceUuid(ActivityMonitor.uuid());  // add the service UUID
  blePeripheral.addAttribute(ActivityMonitor);   // Add the BLE Heart Rate service
  blePeripheral.addAttribute(activityChar); // add the Heart Rate Measurement characteristic

  /* Now activate the BLE device.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */
  blePeripheral.begin();
  CurieIMU.begin();
  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
    // turn on the LED to indicate the connection:
    digitalWrite(13, HIGH);

    // check the Activity measurement every 200ms
    // as long as the central is still connected:
    while (central.connected()) {
      long currentMillis = millis();
      // if 200ms have passed, check the Activity measurement:
      if (currentMillis - previousMillis >= 200) {
        previousMillis = currentMillis;
        updateActivity();
      }
    }
    // when the central disconnects, turn off the LED:
    digitalWrite(13, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}

void updateActivity() {
  /* Read the current voltage level on the A0 analog input pin.
     This is used here to simulate the activity measurement.
  */
  int raw[3];
  if (CurieIMU.dataReady()) {
  CurieIMU.readAccelerometer(raw[0], raw[1], raw[2]);
  int AccX = map(raw[0], -32768, 32767, 0, 255);
       // if the Activity measurment has changed
    Serial.print("Accelerometer is now: "); // print it
    Serial.println(AccX);
    const unsigned char activityCharArray[2] = { 0, (char)AccX };
    activityChar.setValue(activityCharArray, 2);  // 
            // save the level for next comparison
  
  }
}
