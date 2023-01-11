#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);
// addr,en,rw,rs,d4,d5,d6,d7,bl,blpol
// addr can be 0x3F or 0x27

const char message[] = "This is a scrolling message on an LCD"; // message to scroll


int messageLen = sizeof(message) - 1; // length of message
int pos = 0; // position of scrolling message
unsigned long time = 0;
unsigned long interval = 100;


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
    //INFRARED
    Serial.begin(9600);

    //FUNCTIONS
    void drive(int Rspeed, int Lspeed);

    //LCD
    lcd.init();            // initialize the lcd
    lcd.backlight();       // turn on the backlight


}

void loop() {
    int a;
    Serial.println(analogRead(A1));

    //forward
    drive(200,200);
    delay(1000);
    drive(0,0);
     
    //reverse
    drive(-255,-255);
    delay(1000);
    drive(0,0);
  
    //spin on the spot
    drive(-255,255);//anticlockwise
    delay(1000);
    drive(0,0);
    drive(255,-255);//clockwise
    delay(1000);
    drive(0,0);
    
    //forward right
    drive(200,130);
    delay(1000);
    drive(0,0);
    
    //forward left
    drive(130,200);
    delay(1000);
    drive(0,0);
    
    //reverse right
    drive(-80,-180);
    delay(1000);
    drive(0,0);
 
    //reverse left
    drive(-180,-80);
    delay(1000);
    drive(0,0);

    //Stop
    drive(0,0);
    delay(1000);
    //LCD
    if (millis() - time > interval) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(message + pos);

        if (pos < messageLen - 16) {
            pos++;
        }
        else {
            pos = 0;
        }
        time = millis();
    }

}

void drive(int Rspeed, int Lspeed) {
    if (Rspeed >= 0)analogWrite(Right2, Rspeed);
    else analogWrite(Right1, abs(Rspeed));
    if (Lspeed >= 0)analogWrite(Left2, Lspeed);
    else analogWrite(Left1, abs(Lspeed));
}