#include <Keypad.h>
#include <stdlib.h>
#include <string.h>

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

// https://circuitdigest.com/microcontroller-projects/arduino-calculator-using-4x4-keypad

char keys[ROWS][COLS] = {
    {'1','2','3','X'},
    {'4','5','6','/'},
    {'7','8','9','+'},
    {'C','0','=','-'}
};

byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};


Keypad keypad = Keypad(makeKeymap(keys),rowPins, colPins,ROWS, COLS);
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13; //Pins to which LCD is connected
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

long Num1,Num2,Number;
char key,action;
boolean result = false;
 
void setup() {
    Serial.begin(9600);
}

void loop() {
    key = keypad.getKey(); //storing pressed key value in a char
    if (key!=NO_KEY){
      Serial.println(key);
      DetectButtons();
    }    
    if (result==true) {
      CalculateResult();
    }
    DisplayResult();   
    result=false;

}

// Good heavens
long char_to_long(char c)
{
  char temp[2];
  temp[0] = c;
  temp[1] = '\0';
  return atol(temp);
}

void DetectButtons()
{ 
//     lcd.clear(); //Then clean it
    if (key=='C') //If cancel Button is pressed
    {
      Serial.println ("Button Cancel"); 
      Number=Num1=Num2=0;
      result=false;
    }

    // Numeric buttons
    if (key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' )
    {
      Serial.println("Button pressed ");
      Serial.println(key);
      // Could alternatively save all the chars to a buffer and do the atol when an operator
      // is pressed instead of converting it on every char
      if (Number == 0) {
        Number = char_to_long(key);
      }
      else {
        // Buttons have been pressed multiple times without an operator, e.g. entering 232
        Number = (Number*10)+char_to_long(key);
      }
    }
  
    if (key == '=')
    {
      Serial.println ("Button Equal"); 
      Num2 = Number;
      result = true;
    }

    // Operator buttons
    if (key == '+' || key == '-' || key == 'X' || key == '/')
    {
      Num1 = Number;    
      Number = 0;
      if (key == '+') {
        Serial.println ("Addition"); action = '+';
      }
      if (key == '-') {
        Serial.println ("Subtraction"); action = '-'; 
      }
      if (key == 'X') {
        Serial.println ("Multiplication"); action = '*';
      }
      if (key == '/') {
        Serial.println ("Division"); action = '/';
      }  
      delay(100);
    }
  
}

void CalculateResult()
{
  if (action=='+')
    Number = Num1+Num2;

  if (action=='-')
    Number = Num1-Num2;

  if (action=='*')
    Number = Num1*Num2;

  if (action=='/')
    Number = Num1/Num2; 
}

void DisplayResult()
{
  //lcd.setCursor(0, 0);   // set the cursor to column 0, line 1
//  lcd.print(Num1); lcd.print(action); lcd.print(Num2); 
  
  if (result==true)
  {
    Serial.println("displayresult");
    Serial.println( Num1);
    Serial.println( action);
    Serial.println( Num2);
    Serial.println( "=");
    Serial.println(Number);
    //lcd.print(" ="); lcd.print(Number);} //Display the result
  
  //lcd.setCursor(0, 1);   // set the cursor to column 0, line 1
  //lcd.print(Number); //Display the result
  }
}
