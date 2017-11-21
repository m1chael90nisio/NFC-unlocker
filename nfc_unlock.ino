#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myservo; 
int pos = 0;  
int ledPin = 6;
int deniedPin = 5;
void setup() {
    Serial.begin(9600); // Initialize serial communications with the PC
    SPI.begin();   
      myservo.attach(3); // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card
    mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max); 
    pinMode(ledPin, OUTPUT);
    Serial.println("Scan PICC to see UID and type...");
}

void loop() {
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;
    }

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
    }
   
    
if (mfrc522.uid.uidByte[0] == 0x36 && 
     mfrc522.uid.uidByte[1] == 0xDB &&
     mfrc522.uid.uidByte[2] == 0x3A &&
     mfrc522.uid.uidByte[3] == 0xD5) {
      Serial.println("code is OK!Access Granted!!");
        digitalWrite(ledPin, HIGH);
        delay(1000);
        digitalWrite(ledPin, LOW);
        delay(1000);
     // turn your LED on


///our loops to unlock and after some miliseconds lock again
     for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
        // in steps of 1 degree
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(10);                       // waits 10ms for the servo to reach the position
      }
	delay(1000);          // waits 1000ms until the user opens the door
        for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
                               
      }
     
}

else {
  Serial.println("uid is not correct!wrong key");
        digitalWrite(deniedPin, HIGH);
        delay(1000);
        digitalWrite(deniedPin, LOW);
        delay(1000);
         
  
}


  
}