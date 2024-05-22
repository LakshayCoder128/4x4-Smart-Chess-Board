#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>
#include <SPI.h>

// final lakshay CHess code

// Queen Detection Code
#define RST_PIN 5  // Configurable, see typical pin layout above
#define SS_PIN 53  // Configurable, see typical pin layout above

// initialisation
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
byte queen_uid[] = { 0x2a, 0x9f, 0x21, 0xb0 };
byte pawn_id[] = { 0xc3, 0xd0, 0x22, 0xac };
bool queenFlag = false;
bool PawnFlag = false;

int hallSignal = 0;
const int hallPin = A0;
const int hallPin2 = A8;
const int hallPin3 = A1;
const int hallPin4 = A2;

const int led_00 = 22;
const int led_01 = 23;
const int led_02 = 24;
const int led_03 = 25;
const int led_10 = 26;
const int led_11 = 27;
const int led_12 = 28;
const int led_13 = 30;
const int led_20 = 31;
const int led_21 = 32;
const int led_22 = 33;
const int led_23 = 34;
const int led_30 = 35;
const int led_31 = 36;
const int led_32 = 37;
const int led_33 = 38;


int led_matrix[4][4] = { { led_00, led_01, led_02, led_03 },

                         { led_10, led_11, led_12, led_13 },

                         { led_20, led_21, led_22, led_23 },

                         { led_30, led_31, led_32, led_33 } };

int x = -1; 
int y = -1;

// C3 D0 22 AC
// 2A 9F 21 B0

void setup() {
  Serial.begin(9600);  // Initialize serial communications with the PC
  while (!Serial)
    return;
  // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();                        // Init SPI bus
  mfrc522.PCD_Init();                 // Init MFRC522
  delay(4);                           // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details

  pinMode(hallPin, INPUT);
  pinMode(hallPin2, INPUT);
  pinMode(hallPin3, INPUT);
  pinMode(hallPin4, INPUT);
  pinMode(led_00,OUTPUT);
  pinMode(led_01,OUTPUT);
  pinMode(led_02,OUTPUT);
  pinMode(led_03,OUTPUT);
  pinMode(led_10,OUTPUT);
  pinMode(led_11,OUTPUT);
  pinMode(led_12,OUTPUT);
  pinMode(led_13,OUTPUT);
  pinMode(led_20,OUTPUT);
  pinMode(led_21,OUTPUT);
  pinMode(led_22,OUTPUT);
  pinMode(led_23,OUTPUT);
  pinMode(led_30,OUTPUT);
  pinMode(led_31,OUTPUT);
  pinMode(led_32,OUTPUT);
  pinMode(led_33,OUTPUT);

  Serial.println(F("Scan PICC ..."));
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // read the UID of the tag
    byte uidBytes[4];
    for (int i = 0; i < 4; i++) {
      uidBytes[i] = mfrc522.uid.uidByte[i];
    }
    // compare the UID with the queen's UID
    if (memcmp(uidBytes, queen_uid, 4) == 0) {
      queenFlag = true;
      Serial.println("Queen piece detected! on ");  // print message if UID matches queen's UID
      delay(2000);
      Serial.println("Placing the piece : ");
      delay(5000);
      
      if (digitalRead(hallPin) == LOW) {
        // Serial.print("first pin");
        hallSignal = digitalRead(hallPin);
        Serial.print("A3");
        x = 1;
        y = 0;
        delay(5000);
        // Serial.println(hallSignal);
      } else if (digitalRead(hallPin2) == LOW) {
        hallSignal = digitalRead(hallPin2);
        x = 1;
        y = 1;
        Serial.print("B3");
        delay(5000);

        // Serial.println(hallSignal);
      } else if (digitalRead(hallPin3) == LOW) {
        hallSignal = digitalRead(hallPin3);
        Serial.print("C3");
        x = 1;
        y = 2;
        delay(5000);
        // Serial.println(hallSignal);
      } else if (digitalRead(hallPin4) == LOW) {
        hallSignal = digitalRead(hallPin4);
        Serial.print("D3");
        x = 1;
        y = 3;
        delay(5000);
        // Serial.println(hallSignal);
      }
      delay(1000);
    } else if (memcmp(uidBytes, pawn_id, 4) == 0) {
      PawnFlag = true;
      Serial.println("pawn piece detected.");  // print message if UID does not match queen's UID
      delay(2000);
      Serial.println("Placing the piece : ");
      delay(5000);
      
      if (digitalRead(hallPin) == LOW) {
        // Serial.print("first pin");
        hallSignal = digitalRead(hallPin);
        Serial.print("A3");
        x = 1;
        y = 0;
        delay(5000);
        // Serial.println(hallSignal);
      } else if (digitalRead(hallPin2) == LOW) {
        hallSignal = digitalRead(hallPin2);
        x = 1;
        y = 1;
        Serial.print("B3");
        delay(5000);

        // Serial.println(hallSignal);
      } else if (digitalRead(hallPin3) == LOW) {
        hallSignal = digitalRead(hallPin3);
        Serial.print("C3");
        x = 1;
        y = 2;
        delay(5000);

        // Serial.println(hallSignal);
      } else if (digitalRead(hallPin4) == LOW) {
        hallSignal = digitalRead(hallPin4);
        Serial.print("D3");
        x = 1;
        y = 3;
        delay(5000);
        // Serial.println(hallSignal);
      }
      delay(1000);
    } else {
      Serial.println("Unknown piece detected.");  // print message if UID does not match queen's UID
    }
    // halt the RFID tag
    Serial.println();
    Serial.print("lights on : " );
    Serial.print(x);
    Serial.print(y);

    if (x != -1 && y != -1 && queenFlag) {

      // row light up
      // for (int i = x; i < 3; i++) {
        for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
          digitalWrite(led_matrix[i][j],LOW);
        }
      }

      delay(2000);

        for (int j = 0; j <= 3; j++) {
          // horizontal row
             digitalWrite(led_matrix[3-x][j], HIGH);
        }

        // vertical 
        for(int i=0;i<4;i++){
          digitalWrite(led_matrix[i][3-y],HIGH);
        }

        // diagonal 
        int i=3-x,j=3-y;

        while(i<4 && j<4){
          digitalWrite(led_matrix[i][j],HIGH);
          i++;
          j++;
        }
        i=3-x;j=3-y;
        while(i>=0 && j>=0){
          digitalWrite(led_matrix[i][j],HIGH);
          i--;
          j--;
        }
        i=3-x;j=3-y;
        while(i>=0 && j<4){
          digitalWrite(led_matrix[i][j],HIGH);
          i--;
          j++;
        }
        i=3-x;j=3-y;
        while(i<4 && j>=0){
          digitalWrite(led_matrix[i][j],HIGH);
          i++;
          j--;
        }
        queenFlag = false;
      // }
    }
    else if(x!=-1 && y!=-1 && PawnFlag){
      for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
          digitalWrite(led_matrix[i][j],LOW);
        }
      }  

      delay(2000);
      for(int i=0;i<2;i++){
          digitalWrite(led_matrix[i][3-y],HIGH);
        }
        PawnFlag = false;
    }
    mfrc522.PICC_HaltA();
  }
}