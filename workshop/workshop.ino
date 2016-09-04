#include <NewTone.h> 
#include <IRremote.h>

const int irPin = 9;
IRrecv irrecv(irPin);
decode_results irResult;

const int buttonPin = 2;
const int ledPin =  3;
const int piezoPin = 6;
const int ldrPin = 0;

int buttonState = 0;
const long keyOK = 0x1009293;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(piezoPin, OUTPUT);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&irResult)){
    if( irResult.value == keyOK ){
      alarm(true);
    } else {
      alarm(false);
    }
    irrecv.resume();
  }
  
  int ldrValue = analogRead(ldrPin);
  if(ldrValue > 500) {
    alarm(true);
  } else {
    alarm(false);
  }
  
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
   alarm(true); 
  } else {
    alarm(false);
  }
}

void alarm( bool active ){
  if ( !active ){
    digitalWrite(ledPin, LOW);
    noNewTone(piezoPin);
  } else {
   float sinVal;
   int toneVal;
  
    for (int x=0; x<180; x++) {
      sinVal = (sin(x*(3.1412/180)));
      toneVal = 2000+(int(sinVal*1000));
      NewTone(piezoPin, toneVal);
      int blink = x < 90 ? HIGH : LOW;
      digitalWrite(ledPin, blink);
      delay(2);
    }
  }
}

