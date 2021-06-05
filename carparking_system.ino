#include <hd44780.h>
#include <LiquidCrystal_I2C.h>
#include<Servo.h>
LiquidCrystal_I2C lcd(0x27,16,2);

Servo servo;

int IR_OUT=2;
int IR_IN=4;
int buzzer=7;
int red_LED=12;
int green_LED=13;

int total_spaces=5;
int av_spaces=5;

int flg1=0; // for IR sensor outside
int flg2=0; // for IR sensor inside



void setup() {
  pinMode(IR_OUT,INPUT);
  pinMode(IR_IN,INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(red_LED,OUTPUT);
  pinMode(green_LED,OUTPUT);

  servo.attach(9);
  servo.write(20);
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(" Car Parking ");
  lcd.setCursor(0,1);
  lcd.print("system");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TOTAL SPACE = 5");
}

void loop() 
{
  servo.write(20);
  digitalWrite(red_LED,LOW);
  
  if(digitalRead(IR_OUT)==LOW && flg1==0){
        if(av_spaces>0)
        {
          flg1=1;
          if(flg2==0) // car is entering
          {
            digitalWrite(green_LED,HIGH);
            tone(buzzer,1000);
            for(int i=20;i<=90;i++) // opening parking gate
            {
              servo.write(i);
              delay(10);
            } 


            delay(1000);
            av_spaces--; // no. of parking space available is reduced by 1
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("TOTAL SPACE = 5");
            lcd.setCursor(0,1);
            lcd.print("SPACE LEFT"); 
            lcd.setCursor(11,1);
            lcd.print(av_spaces); 
            delay(1000);
          }
        }
        else
        {
          digitalWrite(red_LED,HIGH);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(" space not left");
          delay(1000);
        }
  }

  if(digitalRead(IR_IN)==LOW && flg2==0)
  {
    flg2=1;
    if(flg1==0) // condition is true if car is exiting
    {
      digitalWrite(red_LED,LOW);
      for(int i=5;i<=90;i++) // opening parking gate
      {
         servo.write(i);
         delay(10);
      }
      delay(1000);
       av_spaces++; // no. of parking space available is increased by 1
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("TOTAL SPACE = 5");
       lcd.setCursor(0,1);
       lcd.print("SPACE LEFT"); 
       lcd.setCursor(11,1);
       lcd.print(av_spaces); 
       delay(1000);
     }
   }

  if(flg1==1 && flg2==1)
    {
      noTone(buzzer);
      digitalWrite(red_LED,LOW);
      digitalWrite(green_LED,LOW);
      for(int i=90;i>=20;i--) // closing
      {
        servo.write(i);
        delay(10);
      }
       delay(1000);
      flg1=0;
      flg2=0;
    }
   
     
}
