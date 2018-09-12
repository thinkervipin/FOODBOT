#include <SoftwareSerial.h>


char incomingByte = 0;   // for incoming serial data

SoftwareSerial SR1(3,2);
void setup() {
        Serial.begin(500000);
        
        SR1.begin(500000);     // opens serial port, sets data rate to 9600 bps
}

void loop() {

        // send data only when you receive data:
        if (SR1.available() > 0) {
                // read the incoming byte:
                incomingByte = (char)SR1.read();

                // say what you got:
               Serial.print(incomingByte);
               if (incomingByte == '\n')
               {
                Serial.println();
               }
            
        }
}
