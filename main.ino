/*
#Description:       Arduino Code "Bad USB" inspired project. Device emulates a keyboard.
                    When plugged in, it checks its 4 dip switches to see what program has been
                    selected. It displays the program to the screen and then waits for the play
                    button to be pressed. If the play button is pressed it runs the selected 
                    script.

#Author:            Aaron Hickman
#Version/Date:      11/18/21

#Note:              Uses some code from the Adafruit SSD1306 Example.
 */


//LIBS
#include <Keyboard.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//DEFS
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define KEY_LEFT_CTRL   0x80
#define KEY_LEFT_SHIFT  0x81
#define KEY_LEFT_ALT    0x82
#define KEY_LEFT_GUI    0x83
#define KEY_RIGHT_CTRL  0x84
#define KEY_RIGHT_SHIFT 0x85
#define KEY_RIGHT_ALT   0x86
#define KEY_UP_ARROW    0xDA
#define KEY_DOWN_ARROW  0xD9
#define KEY_LEFT_ARROW  0xD8
#define KEY_RIGHT_ARROW 0xD7
#define KEY_BACKSPACE   0xB2
#define KEY_TAB         0xB3
#define KEY_ENTER       0xB0
#define KEY_ESC         0xB1
#define KEY_CAPS_LOCK   0xC1
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Setting vars for input pins.
int playButton = 5;
int switch1 = 6; 
int switch2 = 7; 
int switch3 = 8; 
int switch4 = 9; 

//Array of Program Headers/Titles
String headers [16] = { "Screen 0", "Screen 1", "Screen 2", "Screen 3", "Screen 4", "Screen 5", "Screen 6", "Screen 7", "Screen 8", "Lock Screen", "Tech Fast", "Tech Slow", "Matrix.bat", "Screen 13", "Screen 14", "Screen 15"};

//Adafruit Logo Stuff
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] ={ 0b00000000, 0b11000000, 0b00000001, 0b11000000, 0b00000001, 0b11000000, 0b00000011, 0b11100000, 0b11110011, 0b11100000, 0b11111110, 0b11111000, 0b01111110, 0b11111111, 0b00110011, 0b10011111, 0b00011111, 0b11111100, 0b00001101, 0b01110000, 0b00011011, 0b10100000, 0b00111111, 0b11100000, 0b00111111, 0b11110000, 0b01111100, 0b11110000, 0b01110000, 0b01110000, 0b00000000, 0b00110000 };



void setup() {
  Keyboard.begin(); //Keyboard emulator
  pinMode(playButton, INPUT);
  pinMode(switch1, INPUT);  // - - - 0 binary 1s
  pinMode(switch2, INPUT);  // - - 0 - binary 2s
  pinMode(switch3, INPUT);  // - 0 - - binary 4s
  pinMode(switch4, INPUT);  // 0 - - - binary 8s

  //This is some troubleshooting thing from Adafruits example program. 
  //I never got rid of it because I'm lazy :P
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }


  // the library initializes this with an Adafruit splash screen.
  display.display();
  display.clearDisplay();
}

//Main Loop. Get the prog num from binary dip switches. Draw the title on screen.
//Check if the play button is pressed.
int prog = 0;
void loop(){
  prog = readSwitches();
  makeHeader(headers[prog]);
  checkPlay(prog);
  
}

void makeHeader(String title){
  display.clearDisplay();
  display.drawRect(0,0, display.width(),9, SSD1306_WHITE);
  display.setTextSize(1);      
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(1, 1);    
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.println(title);
  display.display();
}

//Read the switches, generate int from binary input. return int.
int readSwitches(){
  int total = 0;
  if(digitalRead(switch1) == HIGH){
        total += 1;
    }
  if(digitalRead(switch2) == HIGH){
        total += 2;
    }
  if(digitalRead(switch3) == HIGH){
        total += 4;
    }
  if(digitalRead(switch4) == HIGH){
        total += 8;
    }
  return total;
}

//If play button is pressed type the macro of specific prog.
void checkPlay(int prog){
  if(digitalRead(playButton) == HIGH){
    delay(100);
    typeMacro(prog);
  }
}

void drawProgress(int progress){

  makeHeader(headers[prog]);
  display.drawRect(0,20,display.width(),25, SSD1306_WHITE);
  display.fillRect(0,20, progress ,25, SSD1306_WHITE);
  display.display();
}

void typeMacro(int prog){
  switch(prog){
        case 0:
          break;
        case 1:
          break;
        case 2:
          break;
        case 3:
          break;
        case 4:
          break;
        case 5:
          break;
        case 6:
          break;
        case 7:
          break;
        case 8:
          break;
        
        case 9:
            Keyboard.press(KEY_LEFT_GUI);
            Keyboard.press('l');
            Keyboard.releaseAll();
            delay(200);
            break;

        case 10:
            Keyboard.print("Greetings");
            
            Keyboard.write(KEY_ENTER);
            
            Keyboard.print("Have you tried to turn it off and on again?");
            
            Keyboard.write(KEY_ENTER);
            
            Keyboard.print("Thank you");
            delay(200);
            break;

        case 11:
            Keyboard.print("Greetings");
            delay(100);
            Keyboard.write(KEY_ENTER);
            delay(100);
            Keyboard.print("Have you tried to turn it off and on again?");
            delay(100);
            Keyboard.write(KEY_ENTER);
            delay(100);
            Keyboard.print("Thank you");
            delay(200);
            
            break;
        case 12:
              Keyboard.press(KEY_LEFT_GUI);
              Keyboard.press('r');
              Keyboard.releaseAll();
              delay(200);
              Keyboard.print("notepad.exe");
              Keyboard.write(KEY_ENTER);
              delay(100);
              Keyboard.print("@echo off\nmode 1000\ncolor 0A\n:1\necho %random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%%random%\ngoto 1");
              Keyboard.press(KEY_LEFT_CTRL);
              Keyboard.press('s');
              Keyboard.releaseAll();
              delay(500);
              Keyboard.write(KEY_TAB);
              delay(100);
              Keyboard.write(KEY_DOWN_ARROW);
              
              Keyboard.write(KEY_DOWN_ARROW);
            
              Keyboard.write(KEY_ENTER);
              delay(100);
              Keyboard.press(KEY_LEFT_SHIFT);
              Keyboard.press(KEY_TAB);
              Keyboard.releaseAll();
              delay(100);
              Keyboard.print("matrix.bat");
              delay(100);
              Keyboard.write(KEY_ENTER);
              delay(500);
              Keyboard.write(KEY_LEFT_GUI);
             delay(200);
              Keyboard.print("matrix.bat");
             delay(200);
              Keyboard.write(KEY_ENTER);
              
              
            break;
        case 13:
          break;
        case 14:
          break;
        case 15:
          break;
        
        
        
    }


}
