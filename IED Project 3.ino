#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);
// addr,en,rw,rs,d4,d5,d6,d7,bl,blpol
// addr can be 0x3F or 0x27


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
  
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Scrolling Texttttttttt");


}

void loop() {

    for (int i = 0; i < 15; i++) {
        lcd.scrollDisplayLeft();
        delay(200);
    }
    for (int i = 0; i < 15; i++) {
        lcd.scrollDisplayRight();
        delay(200);
    }



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
    

}

void drive(int Rspeed, int Lspeed) {
    if (Rspeed >= 0)analogWrite(Right2, Rspeed);
    else analogWrite(Right1, abs(Rspeed));
    if (Lspeed >= 0)analogWrite(Left2, Lspeed);
    else analogWrite(Left1, abs(Lspeed));
}