#include <SoftwareSerial.h>
#define STD_TX 8
#define STD_RX 7
#define PROF_TX 13
#define PROF_RX 12
#define MAX_ANSWERS 5

SoftwareSerial StudentBth(STD_RX, STD_TX);      // Student's Bluetooth Configuration
SoftwareSerial ProfessorBth(PROF_RX, PROF_TX);  // Professor's Bluetooth Configuration  
String val = "";                                // Variable to receive data from the serial port
int answers[4] = {0,0,0,0};                     // Buffer Answers
int numAnswers = 0;                             // Number of students who answered the question

typedef enum {
    WaitingQuestion,
    WaitingAnswers,
    SendingAnswers
} State;

State machineState = WaitingQuestion;

void setup() {
    // start serial communication at 9600bps
    Serial.begin(9600);
    StudentBth.begin(9600);
    ProfessorBth.begin(9600);
    Serial.println("Communication Started");
    StudentBth.println("Communication Started -- Student");
    ProfessorBth.println("Communication Started -- Professor");
}

void sendingAnswers() {
    String result = "";
    result += "A:";
    result += answers[0];
    result += ";B:";
    result += answers[1];
    result += ";C:";
    result += answers[2];
    result += ";D:"; 
    result += answers[3];
    result += "$";
    for(int i=0; i<4; i++)
        answers[i] = 0;
    ProfessorBth.println(result);
    machineState = WaitingQuestion;
}

void waitingQuestion() {
    ProfessorBth.listen();
    if(ProfessorBth.available()) {
        while(ProfessorBth.available())
            val += (char)ProfessorBth.read();
        if (val.substring(val.length() - 6, val.length()-2) == "QTN$") {
            Serial.println("Professor's Message");
            Serial.println(val);
            StudentBth.println(val);
            val = "";
            machineState = WaitingAnswers;
        }
    } 
}

void waitingAnswers() {
    StudentBth.listen();
    if(StudentBth.available()) {
        Serial.println("RECEBIDO - Student");
        while(StudentBth.available())
            val += (char)StudentBth.read();
        switch(val[0]) {
            case 'A':
                answers[0]++;
                break;
            case 'B':
                answers[1]++;
                break;
            case 'C':
                answers[2]++;
                break;
            case 'D':
                answers[3]++;
                break;
            default:
                break;
        }
        val = "";
        numAnswers++;
        Serial.println(answers[0]);
        Serial.println(answers[1]);
        Serial.println(answers[2]);
        Serial.println(answers[3]);
        if(numAnswers == MAX_ANSWERS) {
            numAnswers = 0;
            machineState = SendingAnswers;
        }
    }
}

void loop() {
    switch(machineState) {
        case WaitingQuestion:
            waitingQuestion();
            break;
        case WaitingAnswers:
            waitingAnswers();
            break;
        case SendingAnswers:
            sendingAnswers();
            break;
        default:
            break;
    }
}
