#include <WiFi.h>
#include <HTTPClient.h>

const char* serverUrl = "http://192.168.0.220:5000/data";
const char* ssid = "SSID";
const char* password = "Password";

    float temp = 0;
    float Amps = 0;
    float Volt = 0;


void setup() {
    WiFi.begin(ssid, password);
    Serial.begin(115200);
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
    }

    Serial.println("Connected!");
}


void loop() {

    
    if (temp >= 100){
       temp = 0; 
    }
    else if(Volt >= 48)
    {
        Volt = 0;
    }
    else if(Amps >= 100){
        Amps = 0;
    }
    else{    
    temp = temp + 1;
    Volt = Volt + 2;
    Amps = Amps + 5;
    }

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverUrl);
        http.addHeader("Content-Type", "application/json");

        // Full JSON body
        String jsonData = "{\"temp\": " + String(temp) + ", \"Amps\": " + String(Amps) + ", \"Volt\": " + String(Volt) + "}";

        int httpResponseCode = http.POST(jsonData);

        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        http.end();
    } 
    else {
        Serial.println("WiFi not connected");
    }
    
    delay(1000); 
    
}
