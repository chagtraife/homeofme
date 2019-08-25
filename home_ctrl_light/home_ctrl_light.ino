#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <string.h>

#define PIN_LED 5 //gpio5
#define PIN_BUTTON 0//gpio0


#define LED_ON() digitalWrite(PIN_LED, HIGH)
#define LED_OFF() digitalWrite(PIN_LED, LOW)
#define LED_TOGGLE() digitalWrite(PIN_LED, digitalRead(PIN_LED) ^ 0x01)


const char* ssid = "Trai Binh Dinh";
const char* password =  "9qca0n04";
const char* mqttServer = "192.168.1.55";
const int mqttPort = 1883;
const char* mqttUser = "homeofme";
const char* mqttPassword = "9qca0n04";



uint8_t state_buton;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {

  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  LED_OFF();
  //  delay(500);
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }

  client.subscribe("light");

}

void callback(char* topic, byte* payload, unsigned int length) {
  char s[10] = "";
  char a[10] = "";
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  //  s = "";
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    s[i] = (char)payload[i];
  }
  Serial.println();
  strncpy(a, s + 0, length);
  Serial.println(length, DEC);
  if (strcmp(a, "turn_on") == 0) {
    Serial.printf("YES");
    LED_ON();
  }
  if (strcmp(a, "turn_off") == 0) {
    Serial.printf("NO");
    LED_OFF();
  }
  Serial.println();
  Serial.println("-----------------------");

}

void loop() {
  client.loop();
  if (digitalRead(PIN_BUTTON) == 0) {
    if (state_buton == 1) {
      delay(200);
      LED_TOGGLE();
      state_buton = 0;
    };
  };
  if (digitalRead(PIN_BUTTON) == 1) {
    if (state_buton == 0) {
      delay(200);
      LED_TOGGLE();
      state_buton = 1;
    };
  };

}
