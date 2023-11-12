#include "SimplyCommand.h"
#include <WiFi.h>


const char* ssid = "ENTER NETWORK ID";    // Replace with your WiFi network name
const char* password = "ENTER NETWORK PASSWORD";  // Replace with your WiFi password

WiFiServer server(1234);
WiFiClient client;
SimplyCommand commander;
Servo servoOne;
Servo servoTwo;
String message = "";

void setupToReceiveTraffic() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  delay(3000);
}

void loopToReceiveTraffic() {
  if (!client.connected()) {
    client = server.available();
  }
  if (client.connected()) {
    if (client.available()) {
      String data = client.readStringUntil('\n');
      data.trim();
      Serial.println(data);
      message = data;
      commander.executeInstruction(message);
    }
  } else {
    // Serial.println("There is no connection...");
  }
}
void setup() {

  String motorName[] = { "M1" };
  int motorPins[] = { 4 };

  commander.defineControlScheme(2,motorName,motorPins ,"PARAMESH", "ESP32", "AUTHENT");
  setupToReceiveTraffic();
  // put your setup code here, to run once:
}

void loop() {
  loopToReceiveTraffic();


  // put your main code here, to run repeatedly:
}
