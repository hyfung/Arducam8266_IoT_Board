/*
  Project Description:
  This is the demo Arduino App for Tech Carnival Smart Classroom

  Function Mappings
  A:
  B:

  Pin 16 of ESP8266 is hooked to an LED as a status indicator
  Blinking fast - Connecting to WiFi
  Solid White - Connected to WiFi
  Dimmed - Handling Process

*/

//Pin definition for different functions
#define BTN_A 2
#define BTN_B 0
#define RED 15
#define YELLOW 13
#define GREEN 12
#define LED 14

//Including some necessary library
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wifi_credentials.h"
#include "api_url.h"
#include "api.h"

//Get the wifi credentials from external file
extern const char* AP_SSID;
extern const char* AP_PW;

//Brightness of onboard LED
char brightness = 0;

//Reset vector
void(*_reset_)(void) = 0;

//Don't modify setup()
void setup()
{
  //Board Initialize
  //Set (R,Y,G) = (0,0,0)
  ESP.wdtFeed();
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(BTN_A, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);
  set_RYG(0, 0, 0);
  //---------------------------------------------------------
  digitalWrite(LED, LOW);
  Serial.begin(115200);
  Serial.println();

  //Initialize WiFi
  //Set (R,Y,G) = (1,1,0)
  WiFi.begin(AP_SSID, AP_PW);
  Serial.print("Connecting");
  int led_state = HIGH;
  set_RYG(1, 1, 0);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(50);
    Serial.print(".");
    digitalWrite(LED, led_state);
    led_state = !led_state;
  }

  Serial.println();

  //Wifi OK
  //Set (R,Y,G) = (0,0,1)
  digitalWrite(LED, HIGH);
  set_RYG(0, 0, 1);
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //Setting status LEDs
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, HIGH);

  //Update watchdog timer to prevent timeout
  ESP.wdtFeed();

  //
  brightness++;
  digitalWrite(LED, brightness > 0 ? 1 : 0);

  /*
  Detecting button event
  I could've used interrupt and to set a flag
  Having the function to check for flag instead of polling
  */

  //Polling button A
  if (digitalRead(BTN_A) == 0) {

  }

  //Polling button B
  if (digitalRead(BTN_B) == 0) {
  }

  delay(50);
}


//A simple function to update our status LEDs
void set_RYG(char R, char Y, char G) {
  digitalWrite(RED, R ? HIGH : LOW);
  digitalWrite(YELLOW, Y ? HIGH : LOW);
  digitalWrite(GREEN, G ? HIGH : LOW);
}

//A simple function to flash our onboard LED
//This function is synchronous
void flashLED() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(16, LOW);
    delay(50);
    digitalWrite(16, HIGH);
    delay(50);
  }
}
