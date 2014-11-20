#include <SoftwareSerial.h>
#define TX 13
#define RX 12

SoftwareSerial BthConn(RX, TX); //RX,TX

void setup() {
    Serial.begin(9600);
    BthConn.begin(9600);
    Serial.println("Communication Started");
    BthConn.println("Communication Started");
}

void loop() {
    char c;
    if(Serial.available()) {
        c = Serial.read();
        BthConn.write(c);
        Serial.write(c);
    }
    if(BthConn.available()) {
        c = BthConn.read();
        Serial.write(c);
    }
}
