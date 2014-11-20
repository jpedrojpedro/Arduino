#include <SoftwareSerial.h>
#define STD_TX 8
#define STD_RX 7
#define PROF_TX 13
#define PROF_RX 12

// Student's Bluetooth Configuration
SoftwareSerial StudentBth(STD_RX, STD_TX); // RX, TX
// Professor's Bluetooth Configuration
SoftwareSerial ProfessorBth(PROF_RX, PROF_TX); // RX, TX
// variable to receive data from the serial port
String val = "";
// Buffer Answers
int answers[4] = {0,0,0,0};

void setup() {
    // start serial communication at 9600bps
    Serial.begin(9600);
    StudentBth.begin(9600);
    ProfessorBth.begin(9600);
    Serial.println("Communication Started");
    StudentBth.println("Communication Started -- Student");
    ProfessorBth.println("Communication Started -- Professor");
}

void loop() {
    // Check byte from Student's Bluetooth
    StudentBth.listen();
    delay(50);
    if(StudentBth.available()) { 
        while(StudentBth.available())
            val += (char)StudentBth.read();
        Serial.println("Student's Message");
        Serial.println(val);
        val = "";
    }
    // Check byte from Professor's Bluetooth
    ProfessorBth.listen();
    delay(50);
    if(ProfessorBth.available()) {
        while(ProfessorBth.available())
            val += (char)ProfessorBth.read();
        Serial.println("Professor's Message");
        Serial.println(val);
        val = "";
    }
}
