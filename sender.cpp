#include "sender.h"
#include "secrets.h"

#include <WiFi.h>
#include <HTTPClient.h>

sender::sender() = default;

bool sender::begin()
{
    return connectToWiFi();
}

bool sender::connectToWiFi()
{
    if (WiFi.status() == WL_CONNECTED)
        return true;

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to WiFi");

    int attempts = 0;

    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi connected");
        Serial.print("ESP32 IP: ");
        Serial.println(WiFi.localIP());
        return true;
    }

    Serial.println("WiFi failed");
    return false;
}

String sender::createScoreJson(int score, int lines)
{
    String json = "{";
    json += "\"score\":" + String(score) + ",";
    json += "\"lines\":" + String(lines);
    json += "}";

    return json;
}

bool sender::sendScore(int score, int lines)
{
    if (!connectToWiFi())
    {
        Serial.println("Score not sent. WiFi failed.");
        return false;
    }

    HTTPClient http;

    http.begin(API_URL);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("X-API-Key", API_KEY);

    String json = createScoreJson(score, lines);

    Serial.print("Sending JSON: ");
    Serial.println(json);

    int responseCode = http.POST(json);

    Serial.print("POST code: ");
    Serial.println(responseCode);

    http.end();

    return responseCode >= 200 && responseCode < 300;
}