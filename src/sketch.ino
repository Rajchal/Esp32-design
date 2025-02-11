#include <WiFi.h>
#include <HTTPClient.h>

// WiFi Credentials
const char *ssid = "Wokwi-GUEST";                           // Change to your WiFi SSID
const char *password = "";                                  // Change to your WiFi Password
const char *serverUrl = "http://64.227.171.4:5000/command"; // Change <RASPBERRY_PI_IP>

// Define button pins
#define BUTTON_A 12
#define BUTTON_B 14
#define BUTTON_C 27
#define BUTTON_D 26

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
        HTTPClient http;
        http.begin(serverUrl);
        http.addHeader("Content-Type", "application/json");

        String payload = "{\"action\": \"button_pressed\", \"button\": \"" + button + "\"}";
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
        sendButtonPress("A,Student-1");
        delay(500);
    }
    if (digitalRead(BUTTON_B) == LOW)
    {
        sendButtonPress("B,Student-1");
        delay(500);
    }
    if (digitalRead(BUTTON_C) == LOW)
    {
        sendButtonPress("C,Student-1");
        delay(500);
    }
    if (digitalRead(BUTTON_D) == LOW)
    {
        sendButtonPress("D,Student-1");
        delay(500);
    }
}
