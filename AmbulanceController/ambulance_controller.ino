#include <esp_now.h>
#include <WiFi.h>

#define BUTTON_1 25  
#define BUTTON_2 26  
#define BUTTON_3 27  

uint8_t receiverMAC[] = {0x5C, 0x01, 0x3B, 0x33, 0x29, 0x24};

typedef struct {
    int signal;
} Message;
Message message;

void sentCallback(const uint8_t *macAddr, esp_now_send_status_t status) {
    Serial.print("Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);

    pinMode(BUTTON_1, INPUT_PULLUP);
    pinMode(BUTTON_2, INPUT_PULLUP);
    pinMode(BUTTON_3, INPUT_PULLUP);

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW initialization failed!");
        return;
    }
    esp_now_register_send_cb(sentCallback);

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, receiverMAC, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    esp_now_add_peer(&peerInfo);
}

void loop() {
    if (digitalRead(BUTTON_1) == LOW) {
        message.signal = 1;
        esp_now_send(receiverMAC, (uint8_t*)&message, sizeof(message));
        delay(500);
    }
    if (digitalRead(BUTTON_2) == LOW) {
        message.signal = 2;
        esp_now_send(receiverMAC, (uint8_t*)&message, sizeof(message));
        delay(500);
    }
    if (digitalRead(BUTTON_3) == LOW) {
        message.signal = 3;
        esp_now_send(receiverMAC, (uint8_t*)&message, sizeof(message));
        delay(500);
    }
}
