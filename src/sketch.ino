#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// WiFi Credentials
const char *ssid = "sachet";                           // Change to your WiFi SSID
const char *password = "sachet123";                                  // Change to your WiFi Password
const char *serverUrl = "http://192.168.4.1:5000/answer"; 


#define BUTTON_A 5   
#define BUTTON_B 4  
#define BUTTON_C 0   
#define BUTTON_D 2   

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);
    pinMode(BUTTON_D, INPUT_PULLUP);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void sendButtonPress(String button)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFiClient client;
        HTTPClient http;
        http.begin(client, serverUrl); 

        http.addHeader("Content-Type", "application/json");

        String payload = "{\"student\": \"Sachet\", \"button\": \"" + button + "\"}";
        int httpResponseCode = http.POST(payload);
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        http.end();
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }
}

void loop()
{
    if (digitalRead(BUTTON_A) == LOW)
    {
        sendButtonPress("0");
        Serial.println("Button A pressed");
        delay(500);
    }
    if (digitalRead(BUTTON_B) == LOW)
    {
        sendButtonPress("1");
        Serial.println("Button B pressed");
        delay(500);
    }
    if (digitalRead(BUTTON_C) == LOW)
    {
        sendButtonPress("2");
        Serial.println("Button C pressed");
        delay(500);
    }
    if (digitalRead(BUTTON_D) == LOW)
    {
        sendButtonPress("3");
        Serial.println("Button D pressed");
        delay(500);
    }
}
