#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int buzzer = 2;
#define Tri_pin 11
#define Echo_pin 10

void setup() {
    //MOTORS
#define Right1 9
#define Right2 6
    pinMode(Right1, OUTPUT);
    pinMode(Right2, OUTPUT);
#define Left1 3
#define Left2 5
    pinMode(Left1, OUTPUT);
    pinMode(Left2, OUTPUT);

    //LCD
    //Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Guide Dog-in-Training");

    //TARGET BOARD 

    //ULTRASOUND & BUZZER 
    Serial.begin(9600);
    pinMode(Tri_pin, OUTPUT);
    pinMode(Echo_pin, INPUT);
    pinMode(buzzer, OUTPUT);

    //FUNCTIONS
    void drive(int Rspeed, int Lspeed);
}

void loop() {
    //MOTORS 
      /*//forward
      drive(200, 200);
      delay(1000);
      drive(0, 0);

      //reverse
      drive(-255, -255);
      delay(1000);
      drive(0, 0);

      //spin on the spot
      drive(-255, 255); //anticlockwise
      delay(1000);
      drive(0, 0);
      drive(255, -255); //clockwise
      delay(1000);
      drive(0, 0);

      //forward right
      drive(200, 130);
      delay(1000);
      drive(0, 0);

      //forward left
      drive(130, 200);
      delay(1000);
      drive(0, 0);

      //reverse right
      drive(-80, -180);
      delay(1000);
      drive(0, 0);

      //reverse left
      drive(-180, -80);
      delay(1000);
      drive(0, 0);

      //Stop
      drive(0, 0);
      delay(1000);*/

      //LCD 
    for (int i = 0; i < 15; i++) {
        lcd.scrollDisplayLeft();
        delay(100);
    }

    //TARGET BOARD 

    //ULTRASOUND & BUZZER 
    digitalWrite(Tri_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(Tri_pin, LOW);
    delayMicroseconds(10);
    int dis = pulseIn(Echo_pin, HIGH) / 58;
    Serial.print(dis);
    Serial.println(" cm");
    if (dis < 50 && dis>20) {
        for (int i = 0; i < 100; i++) {
            digitalWrite(buzzer, HIGH); // send high signal to buzzer 
            delay(3); // delay 1ms
            digitalWrite(buzzer, LOW); // send low signal to buzzer
            delay(3);
        }
    }
    else if (dis < 20) {
        for (int i = 0; i < 100; i++) {
            digitalWrite(buzzer, HIGH); // send high signal to buzzer 
            delay(1); // delay 1ms
            digitalWrite(buzzer, LOW); // send low signal to buzzer
            delay(1);
        }
    }
    else digitalWrite(buzzer, LOW);
}

//FUNCTIONS 
void drive(int Rspeed, int Lspeed) {
    if (Rspeed >= 0)analogWrite(Right2, Rspeed);
    else analogWrite(Right1, abs(Rspeed));
    if (Lspeed >= 0)analogWrite(Left2, Lspeed);
    else analogWrite(Left1, abs(Lspeed));
}
