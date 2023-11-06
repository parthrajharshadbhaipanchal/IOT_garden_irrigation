#pragma region HEADER FILES
#include "arduino_secrets.h"
#include "thingProperties.h"
#pragma endregion

#pragma region GLOBAL VARIABLES

//GPIO pin in which electromagnetic valve is connected to
int valvePin = 14;

//Exact time when watering started
unsigned long startMiliseconds = 0;

//time duration to water plants
unsigned long wateringDuration = 5 * 60 * 1000;

#pragma endregion

//Setup method for initializing the operations 
void setup() {
  pinMode(valvePin, OUTPUT);
  pinMode(16, OUTPUT);
  digitalWrite(valvePin, LOW);
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

//Loop method which continuously executing infinitely
void loop() {
  //Syncs cloud variables from cloud to controller
  ArduinoCloud.update();  

  //If network is not connected then turn off the valve else execute logic
  if (WiFi.status() != WL_CONNECTED) {
    if (digitalRead(16) == HIGH) {
      digitalWrite(16, LOW);
    } else {
      digitalWrite(16, HIGH);
    }
  }
  else {
    //TURN OFF LED
    digitalWrite(16, HIGH);
  }

  //Turn off the valve once timer exceeds
  if (waterValveStatus & ((millis() - startMiliseconds) > wateringDuration)) {
    Serial.println("Watering time exceeded.");
    //update variable in cloud
    StopFlow();
  }
}

#pragma region SUPPORTED METHODS

//Turns off the valve and set waterValveStatus to false
void StopFlow() {
  waterValveStatus = false;
  //stop water valve
  digitalWrite(valvePin, LOW);
  Serial.println("FLow stopped");
}

//Turns on the valve and set waterValveStatus to true
void StartFlow() {

  waterValveStatus = true;

  digitalWrite(valvePin, HIGH);
  //set current timeStamp to stop in next 3 minutes
  Serial.println("setting start miliseconds");
  startMiliseconds = millis();
  Serial.println("Flow started");

}

//Since WaterValveStatus is READ_WRITE variable, onWaterValveStatusChange() is
//executed every time a new value is received from IoT Cloud.
void onWaterValveStatusChange()  {
  if (waterValveStatus) {
    StartFlow();
  }
  else {
    StopFlow();
  }
}

//Since WateringTime is READ_WRITE variable, onWateringTimeChange() is
//executed every time a new value is received from IoT Cloud.
void onWateringTimeChange()  {
  // Add your code here to act upon WateringTime change
  wateringDuration = wateringTime * 60 * 1000;
  Serial.println("watering duration set to : " + String(wateringTime) + " minutes");
}
#pragma endregion