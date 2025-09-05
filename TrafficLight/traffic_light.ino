#include <esp_now.h>   
#include <WiFi.h>

#define RED_LED    25
#define YELLOW_LED 26  
#define GREEN_LED  27  

typedef struct {
    int signal;  
} Message;
Message message;

bool signalReceived = false;

void onReceive(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
    memcpy(&message, incomingData, sizeof(message));
    if (message.signal >= 1 && message.signal <= 3) {
        Serial.printf("Signal received! Turning Traffic Light %d...\n", message.signal);
        signalReceived = true;
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW initialization failed!");
        return;
    }

    esp_now_register_recv_cb(onReceive);
}

void handleEmergencySignal(int signal) {
    switch (signal) {
        case 1: // Force Green
            digitalWrite(RED_LED, LOW);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(GREEN_LED, HIGH);
            break;
        case 2: // Force Red
            digitalWrite(RED_LED, HIGH);
            digitalWrite(YELLOW_LED, LOW);
            digitalWrite(GREEN_LED, LOW);
            break;
        case 3: // Force Yellow
            digitalWrite(RED_LED, LOW);
            digitalWrite(YELLOW_LED, HIGH);
            digitalWrite(GREEN_LED, LOW);
            break;
    }

    delay(10000);

    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    delay(2000);

    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(3000);

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    signalReceived = false;
}

void normalTrafficSequence() {
    Serial.println("Normal Traffic Sequence");

    digitalWrite(RED_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    delay(3000);

    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    delay(2000);

    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    delay(3000);

    digitalWrite(GREEN_LED, LOW);
}

void loop() {
    if (signalReceived) {
        handleEmergencySignal(message.signal);
    } else {
        normalTrafficSequence();
    }
}
