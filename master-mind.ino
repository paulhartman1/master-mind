/***********************************************************
File name: Lesson_23_4x4_matrix_keyboard.ino
Description: when you click the button on the 4x4 matrix 
             keyboard,you can see the serial monitoring 
             of water level data.
Website: www.uctronics.com 
E-mail: sales@uctronics.com 
Author: Lee
Date: 2017/06/12
***********************************************************/
#include <Keypad.h>
 
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
const byte idPins[4][3] = {
  {22,23,24},
  {25,26,27},
  {28,29,30},
  {31,32,33}
};

const byte RED = 0;
const byte GREEN = 1;
const byte BLUE = 2;

const int red_pin_1 = 22;
const int green_pin_1 = 23;
const int blue_pin_1 = 24;

const int red_pin_2 = 25;
const int green_pin_2 = 26;
const int blue_pin_2 = 27;

const int red_pin_3 = 28;
const int green_pin_3 = 29;
const int blue_pin_3 = 30;

const int red_pin_4 = 31;
const int green_pin_4 = 32;
const int blue_pin_4 = 33;

int counter = 0;

char game_value;
char guess;

//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = 
{
   {1,2,3, 'x'},
  {4,5,6, 'x'},
  {7,8,9, 'x'},
  {'x', 0, 'x', 'x'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

byte gameNums[4] = { 2,2,1,3 };
byte userNums[4];
 
//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
 
void setup(){
  Serial.begin(9600);//Open serial
  for(int i = 22; i <=33; i++){
    pinMode(i, OUTPUT);
  }
}
   
int setResp(int a, int b){
  Serial.print("SetResp: ");
  Serial.print(a);
  Serial.print("  ");
  Serial.println(b);
  if(a == b){
    return GREEN;
  } 
  for(int i = 0; i < 4; i++){
    if(gameNums[i] == a){
      return BLUE;
    }
  }
  return RED;
}
void loop(){

  char input = customKeypad.getKey();//Read Key data 
  if(input) {
       userNums[counter] = input;
  counter++;
  Serial.print("Input: ");
  Serial.println(input);
  Serial.print("Counter: ");
  Serial.println(counter);
  }

  if(counter == 4){
    for(int i = 22; i <= 33; i++) {
      digitalWrite(i, LOW);
    }
    for(int i = 0; i < 4; i++) {
      digitalWrite(idPins[i][setResp(userNums[i],gameNums[i])], HIGH);
    }
    delay(10000);
    counter = 0;
  } else {
    for(int i = 22; i <= 33; i++) {
      digitalWrite(i, LOW);
    }
  }
}
