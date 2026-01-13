/*
  File Name: ESP8266_X32_TEST
  Function: All relays turn on in sequence and then turn off in sequence
  Command: on_1 - Turn on relay 1
  Command: off_1 - Turn off relay 1
  Development Environment: VS Code with PlatformIO
  Note: Clone the entire project to your local machine. If you don't have the required environment set up,
        you can use the sample code in Docs/ArduinoSampleCode.
  
  The following configurations are used in the code, you may need to replace them with your own real information:
  WiFi Configuration:
  - SSID: NewImagery
  - Password: *#01234567890
  
  MQTT Configuration:
  - Server: broker.emqx.io
  - Port: 1883
  - Username: (blank)
  - Password: (blank)
  - Topic: relay/control

  
https://mqttx.app/downloads
You can find the MQTTX download address in this link, and you can use it to test MQTT connections.

*/

#include <Arduino.h>

// HC595 Pin Definitions
#define    HC595_SI_PIN     14
#define    HC595_SCK_PIN    13
#define    HC595_RCK_PIN    12
#define    HC595_G_PIN    5

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi Configuration
const char* ssid = "NewImagery";
const char* password = "*#01234567890";

// MQTT Configuration
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;
const char* mqtt_user = "";
const char* mqtt_password = "";
const char* mqtt_topic = "relay/control"; // MQTT Topic
char mqtt_client_id[30]; // Dynamically generate client ID

WiFiClient espClient;
PubSubClient client(espClient);

// Reconnect MQTT
void reconnect() {
  while (!client.connected()) {
    // Dynamically generate client ID, add random number
    int random_number = random(0, 10000);
    sprintf(mqtt_client_id, "ESP8266_Relay_32_%d", random_number);
    
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqtt_client_id, mqtt_user, mqtt_password)) {
      Serial.print("connected as ");
      Serial.println(mqtt_client_id);
      // Subscribe to relay control topic
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

// Function Declarations
void RelayON(unsigned int number);
void RelayOFF(unsigned int number);

// MQTT Callback Function
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  // Convert payload to string
  char message[length + 1];
  for (unsigned int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';
  Serial.println(message);
  
  // Relay Control Logic
  // Message Format: on_1 or off_1
  if (strstr(message, "on_") != NULL) {
    int relay_num = atoi(message + 3);
    if (relay_num >= 1 && relay_num <= 32) {
      RelayON(relay_num);
      Serial.print("Relay ");
      Serial.print(relay_num);
      Serial.println(" ON");
    }
  } else if (strstr(message, "off_") != NULL) {
    int relay_num = atoi(message + 4);
    if (relay_num >= 1 && relay_num <= 32) {
      RelayOFF(relay_num);
      Serial.print("Relay ");
      Serial.print(relay_num);
      Serial.println(" OFF");
    }
  }
}

// WiFi Connection Function
void setupWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void HC595Init(void)
{
 pinMode(HC595_SI_PIN,  OUTPUT);      // Output Mode  
 pinMode(HC595_SCK_PIN, OUTPUT);      // Output Mode
 pinMode(HC595_RCK_PIN, OUTPUT);      // Output Mode
 pinMode(HC595_G_PIN,   OUTPUT);      // Output Mode
 digitalWrite(HC595_G_PIN, HIGH);
 digitalWrite(HC595_SI_PIN, LOW);
 digitalWrite(HC595_SCK_PIN,LOW);
 digitalWrite(HC595_RCK_PIN,LOW);
}

void HC595SendData(unsigned long OutData)
{
    unsigned char i; // Temporary variable for data sending loop
    for (i = 0; i < 32; i++) // Send 32-bit data bit by bit
    {
        digitalWrite(HC595_SCK_PIN,LOW);  // Clock line low
    if ((OutData & 0x80000000) == 0x80000000) // Check data high/low bit
    {
        digitalWrite(HC595_SI_PIN,HIGH); // Send high bit data
    }
    else
    {
        digitalWrite(HC595_SI_PIN,LOW); // Send low bit data
    }
    OutData = OutData << 1; // Shift data left by 1 bit
    digitalWrite(HC595_SCK_PIN,HIGH);  // Clock line high
    }
    // Output data on rising edge
    digitalWrite(HC595_RCK_PIN,LOW);
    digitalWrite(HC595_RCK_PIN,HIGH);
    digitalWrite(HC595_G_PIN,LOW);
}

unsigned long relay_data = 0x00000000;  // Define a variable for relay current status
void RelayON(unsigned int number)
{
  switch(number)
  {
    case 1  : relay_data = relay_data | 0x00000001; break;
    case 2  : relay_data = relay_data | 0x00000002; break;
    case 3  : relay_data = relay_data | 0x00000004; break;
    case 4  : relay_data = relay_data | 0x00000008; break;
    case 5  : relay_data = relay_data | 0x00000010; break;
    case 6  : relay_data = relay_data | 0x00000020; break;
    case 7  : relay_data = relay_data | 0x00000040; break;
    case 8  : relay_data = relay_data | 0x00000080; break;
    case 9  : relay_data = relay_data | 0x00000100; break;
    case 10 : relay_data = relay_data | 0x00000200; break;
    case 11 : relay_data = relay_data | 0x00000400; break;
    case 12 : relay_data = relay_data | 0x00000800; break;
    case 13 : relay_data = relay_data | 0x00001000; break;
    case 14 : relay_data = relay_data | 0x00002000; break;
    case 15 : relay_data = relay_data | 0x00004000; break;
    case 16 : relay_data = relay_data | 0x00008000; break;
    case 17 : relay_data = relay_data | 0x00010000; break;
    case 18 : relay_data = relay_data | 0x00020000; break;
    case 19 : relay_data = relay_data | 0x00040000; break;
    case 20 : relay_data = relay_data | 0x00080000; break;
    case 21 : relay_data = relay_data | 0x00100000; break;
    case 22 : relay_data = relay_data | 0x00200000; break;
    case 23 : relay_data = relay_data | 0x00400000; break;
    case 24 : relay_data = relay_data | 0x00800000; break;
    case 25 : relay_data = relay_data | 0x01000000; break;
    case 26 : relay_data = relay_data | 0x02000000; break;
    case 27 : relay_data = relay_data | 0x04000000; break;
    case 28 : relay_data = relay_data | 0x08000000; break;
    case 29 : relay_data = relay_data | 0x10000000; break;
    case 30 : relay_data = relay_data | 0x20000000; break;
    case 31 : relay_data = relay_data | 0x40000000; break;
    case 32 : relay_data = relay_data | 0x80000000; break;
    default : break;
  }
  HC595SendData(relay_data);
}
void RelayOFF(unsigned int number)
{
  switch(number)
  {
    case 1  : relay_data = relay_data & 0xFFFFFFFE; break;
    case 2  : relay_data = relay_data & 0xFFFFFFFD; break;
    case 3  : relay_data = relay_data & 0xFFFFFFFB; break;
    case 4  : relay_data = relay_data & 0xFFFFFFF7; break;
    case 5  : relay_data = relay_data & 0xFFFFFFEF; break;
    case 6  : relay_data = relay_data & 0xFFFFFFDF; break;
    case 7  : relay_data = relay_data & 0xFFFFFFBF; break;
    case 8  : relay_data = relay_data & 0xFFFFFF7F; break;
    case 9  : relay_data = relay_data & 0xFFFFFEFF; break;
    case 10 : relay_data = relay_data & 0xFFFFFDFF; break;
    case 11 : relay_data = relay_data & 0xFFFFFBFF; break;
    case 12 : relay_data = relay_data & 0xFFFFF7FF; break;
    case 13 : relay_data = relay_data & 0xFFFFEFFF; break;
    case 14 : relay_data = relay_data & 0xFFFFDFFF; break;
    case 15 : relay_data = relay_data & 0xFFFFBFFF; break;
    case 16 : relay_data = relay_data & 0xFFFF7FFF; break;
    case 17 : relay_data = relay_data & 0xFFFEFFFF; break;
    case 18 : relay_data = relay_data & 0xFFFDFFFF; break;
    case 19 : relay_data = relay_data & 0xFFFBFFFF; break;
    case 20 : relay_data = relay_data & 0xFFF7FFFF; break;
    case 21 : relay_data = relay_data & 0xFFEFFFFF; break;
    case 22 : relay_data = relay_data & 0xFFDFFFFF; break;
    case 23 : relay_data = relay_data & 0xFFBFFFFF; break;
    case 24 : relay_data = relay_data & 0xFF7FFFFF; break;
    case 25 : relay_data = relay_data & 0xFEFFFFFF; break;
    case 26 : relay_data = relay_data & 0xFDFFFFFF; break;
    case 27 : relay_data = relay_data & 0xFBFFFFFF; break;
    case 28 : relay_data = relay_data & 0xF7FFFFFF; break;
    case 29 : relay_data = relay_data & 0xEFFFFFFF; break;
    case 30 : relay_data = relay_data & 0xDFFFFFFF; break;
    case 31 : relay_data = relay_data & 0xBFFFFFFF; break;
    case 32 : relay_data = relay_data & 0x7FFFFFFF; break;
    default : break;
  }
  HC595SendData(relay_data);
}

void setup() 
{
  Serial.begin(115200);
  randomSeed(analogRead(0)); // Initialize random number generator
  HC595Init();
  setupWiFi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
//  HC595SendData(0x0000);  // Turn off all relays on power up
}

void loop() 
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
