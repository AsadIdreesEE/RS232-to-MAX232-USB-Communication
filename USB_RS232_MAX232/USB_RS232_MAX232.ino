#include <SoftwareSerial.h>

// Define software serial TX/RX pins for MAX232 (RS232)
SoftwareSerial RS232Serial(10, 11); // RX, TX

void setup() {
    Serial.begin(9600);      // USB Serial Monitor
    RS232Serial.begin(9600); // RS232 communication
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');  // Read input from Serial Monitor
        input.trim();  // Remove spaces/newlines

        if (input.length() > 0) {
            sendHexCommand(input);
        }
    }
}

// Function to convert hex string to bytes and send via RS232
void sendHexCommand(String hexString) {
    int len = hexString.length();
    for (int i = 0; i < len; i += 2) {
        String byteString = hexString.substring(i, i + 2);
        byte hexByte = strtol(byteString.c_str(), NULL, 16);
        RS232Serial.write(hexByte);
    }
    Serial.println("Hex command sent.");
}
