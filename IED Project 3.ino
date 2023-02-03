//combined stuff 1 GLOBAL VARIABLES ETC 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define Hit_aPin 4  
#define Left1 6
#define Left2 9
#define Right1 5
#define Right2 3
#define Tri_pinR 11
#define Echo_pinR 10
#define Tri_pinL 8
#define Echo_pinL 7

int counterA = 1;
int buzzer = 2;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    //TARGET BOARD 
    Serial.begin(9600);
    pinMode(4, INPUT_PULLUP);
    PCICR |= B00000100;
    PCMSK2 |= B00010000;

    //LCD
    lcd.init();
    lcd.begin(16, 2);
    lcd.backlight();
    lcd.clear();

    //MOTORS
    pinMode(Left1, OUTPUT);
    pinMode(Left2, OUTPUT);
    pinMode(Right1, OUTPUT);
    pinMode(Right2, OUTPUT);

    //ULTRA SOUND
    pinMode(Tri_pinR, OUTPUT);
    pinMode(Echo_pinR, INPUT);
    pinMode(Tri_pinL, OUTPUT);
    pinMode(Echo_pinL, INPUT);
    pinMode(buzzer, OUTPUT);

    //FUNCTIONS
    void drive(int Rspeed, int Lspeed);
    void obstacle(int dis, char side);
    void buzz(int a, int b);
    void charge(int count);
}

void loop() {
    // ULTRA SOUND 
    digitalWrite(Tri_pinL, HIGH);
    delayMicroseconds(10);
    digitalWrite(Tri_pinL, LOW);
    delayMicroseconds(10);
    int disL = pulseIn(Echo_pinL, HIGH) / 58;
    digitalWrite(Tri_pinR, HIGH);
    delayMicroseconds(10);
    digitalWrite(Tri_pinR, LOW);
    delayMicroseconds(10);
    int disR = pulseIn(Echo_pinR, HIGH) / 58;
    Serial.print("disL: ");
    Serial.println(disL);
    Serial.print("disR: ");
    Serial.println(disR);
    if (disL < 40) {
        obstacle(disL, 'L');
    }
    else if (disR < 40) {
        obstacle(disR, 'R');
    }
    else {
        drive(170, 220);
        delay(100);
    }

    //LCD + Target Board 
    lcd.setCursor(0, 0); //set cursor to left top corner
    Serial.print("hit a score is ");
    Serial.println(counterA);
    charge(counterA);
    while (counterA == 0)drive(0, 0);
}

//FUNCTIONS 

//LCD + Target Board
void charge(int count) {
    switch (count) {
    case 0: lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Charging");
        lcd.setCursor(0, 1);
        lcd.print("Reset to restart");
        break;
    default: lcd.clear();
        lcd.print("Guide Dog");
        drive(0, 0);
        break;
    }
}

ISR(PCINT2_vect) {
    if (!digitalRead(4)) {
        counterA--;
        if (counterA < 0) {
            counterA = 1;
        }
    }
}


void drive(int Rspeed, int Lspeed) {
    if (Rspeed >= 0) {
        analogWrite(Right1, Rspeed);
        analogWrite(Right2, 0);
    }
    else {
        analogWrite(Right2, abs(Lspeed));
        analogWrite(Right1, 0);
    }

    if (Lspeed >= 0) {
        analogWrite(Left1, Lspeed);
        analogWrite(Left2, 0);
    }
    else {
        analogWrite(Left2, abs(Rspeed));
        analogWrite(Left1, 0);
    }
}

void buzz(int a, int b) {
    int i;
    for (i = a; i > 0; i--) {
        digitalWrite(buzzer, HIGH);
        delay(b);
        digitalWrite(buzzer, LOW);
        delay(b);
    }
}

void obstacle(int dis, char side) {
    drive(0, 0);
    buzz(200, 1);
    delay(1000);
    Serial.println("reverse");
    drive(-150, -150);
    delay(500);
    int count = 0;
    if (side == 'R') {
        Serial.println("Ob right");
        while (dis < 40) {
            drive(200, 0);//turn left
            delay(500);
            count++;
            Serial.println("turn left");
            Serial.println(count);
            digitalWrite(Tri_pinR, HIGH);
            delayMicroseconds(10);
            digitalWrite(Tri_pinR, LOW);
            delayMicroseconds(10);
            dis = pulseIn(Echo_pinR, HIGH) / 58;
            Serial.print("dis: ");
            Serial.println(dis);
        }
        Serial.println("forward");
        drive(150, 150);
        delay(1000);
        drive(0, 200);
        delay(500 * count);
        Serial.println("turn right");
        return 0;
    }
    else if (side == 'L') {
        Serial.println("ob left");
        while (dis < 40) {
            drive(0, 200);//turn right
            delay(500);
            count++;
            Serial.println("turn right");
            Serial.println(count);
            digitalWrite(Tri_pinL, HIGH);
            delayMicroseconds(10);
            digitalWrite(Tri_pinL, LOW);
            delayMicroseconds(10);
            dis = pulseIn(Echo_pinL, HIGH) / 58;
            Serial.print("dis: ");
            Serial.println(dis);
        }
        Serial.println("forward");
        drive(150, 150);
        delay(1000);
        drive(200, 0);
        delay(300);
        Serial.println("turn left");
        return 0;
    }
    drive(0, 0);
    delay(1000);
}