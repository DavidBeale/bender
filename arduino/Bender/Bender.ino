// Nokia 5110 LCD-Display (84x48 Bildpunkte)

#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "Splash.c"

// D9 - VCC
// D8 - GND
// D7 - LCD chip select (CE oder CS)
// D6 - LCD reset (RST)
// D5 - Data/Command select (DC oder D/C)
// D4 - Serial data out (DIN)
// D3 - Serial clock out (CLK oder SCLK)
// D2 - LED

Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 7, 6);

char character;
String message = "";

int col = 0;
int row = 0;
  

void setup()   {

  // Setup Power
  pinMode(2, INPUT);
  
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW); 
  
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);  
  
  
  // Display
  display.begin();
  display.setContrast(40);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  
  Serial.begin(115200);    // opens serial port, sets data rate to 9600 bps
  
  display.clearDisplay();   // clears the screen and buffer
  
  display.drawBitmap(4, 0, splash, 80, 48, BLACK);
  display.display();
}


void loop() {
  
    // send data only when you receive data:
  if (Serial.available() > 0) {
  
    // read the incoming byte:
    character = Serial.read();
    
    if (character == '\n')
    {
      handleMessage(message);
      message = "";
    }
    else
    {
      message.concat(character);
    }
  }
}


void handleMessage(String message)
{
  int index;
  
  if (row == 0)
  {
    display.clearDisplay();
  }
  
  for (index=0; index < message.length(); index++)
  {
    display.write((char)message[index]);
    
    col++;
    
    if (col > 13)
    {
      col = 0;
      row++;
      
      if (row > 6)
      {
        row = 0;
        
        if (index < message.length()-1) 
        {
          display.clearDisplay();
        }
      }
      
      display.setCursor(col*6, row*8);
    }  
  }
  
  display.display();
  
  
  // End of message
  col = 0; 
  if (++row > 5)
  {
    row = 0;
  }
  display.setCursor(col*6, row*8);
}


//  
//  display.setTextSize(1);
//  set_text(11,0,"Hallo Welt!",BLACK);
//  delay(500);
//  
//  display.drawLine(7,11,77,11,BLACK);
//  display.display();
//  delay(500);
//  
//  display.drawCircle(8,23,5,BLACK);
//  display.display();
//  delay(500);
//  
//  display.fillCircle(11,26,5,BLACK);
//  display.display();
//  delay(500);
//  
//  display.drawRect(25,18,10,10,BLACK);
//  display.display();
//  delay(500);
//
//  display.fillRect(28,21,10,10,BLACK);
//  display.display();
//  delay(500);
//
//  display.drawRoundRect(47,18,10,10,2,BLACK);
//  display.display();
//  delay(500);
//  
//  display.fillRoundRect(50,21,10,10,2,BLACK);
//  display.display();
//  delay(500);
//  
//  display.drawTriangle(68,18,68,28,78,23,BLACK);
//  display.display();
//  delay(500);
//
//  display.fillTriangle(71,21,71,31,81,26,BLACK);
//  display.display();
//  delay(500);
//  
//  // Ein kleines bisschen Scroll-Text-Magie
//  int x=0;
//  for(int i=0;i<(5.6*8);i++){
//    set_text(x,40,"blog.simtronyx.de",BLACK);
//    delay(i==0?1000:100);
//    if(i<(5.6*8)-1)set_text(x,40,"blog.simtronyx.de",WHITE);
//    if((i)<(2.74*8))x-=1;else x+=1;
//  }
//  delay(250);
//  
//  display.clearDisplay();      // Display wieder lÃ¶schen




void set_text(int x,int y,String text,int color){
  
  display.setTextColor(color); // Textfarbe setzen, also Schwarz oder Weiss
  display.setCursor(x,y);      // Startpunkt-Position des Textes
  display.println(text);       // Textzeile ausgeben
  display.display();           // Display aktualisieren
}

