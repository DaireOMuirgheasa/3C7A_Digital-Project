//
//  Digital Dice Testbed
//  Created 25-1-17
//  Group 7
//    Mark Anderson
//    Eoin Gogarty
//    Rob Hanson
//    Daire Morrissy
//

#define PASS 13 // PASS/FAIL LEDs
#define FAIL 12

//  Truth Table
//     A B C D | Decimal
// 0 | 1 1 0 1 | 13 
// 1 | 0 0 1 0 | 2
// 2 | 1 0 0 0 | 8
// 3 | 1 0 1 0 | 10
// 4 | 1 1 0 0 | 12
// 5 | 1 1 1 0 | 14

char logic_out[]  = {13, 2, 8, 10, 12, 14};
char reading;
boolean failed;

void logicTest()
{
  // Logic Test
  DDRD = DDRD | B11110000; // Using Bit Manipulation here as we are dealing with a parallel bus
  DDRB = DDRB | B00001111; // Using a bitwise OR means we don't accidentally change something
  for (int i = 0; i < 6; i++){ // run through binary sequence on pins 
    PORTD = (i << 4); // output binary number on pins 4,5,6
    delay(10);
    reading = PINB & B00001111; // check inputs on B port (A - Pin 11, B - 10, C - 9, D - 8)
    if (reading != logic_out[i]){ 
      failed = true;
      break;
    }
  }
  
  PORTD = 0;
  reading = PIND & B10000000;
  if (reading != 128 || failed)
    digitalWrite(FAIL, HIGH);
  else
    digitalWrite(PASS, HIGH);  
}

void chipTest()
{
  DDRC = DDRC | B00011000; // clock, reset
  for (int i = 0; i < 6; i++){
    PORTC = 1<<5; // clock high
    delay(10); 
    PORTC = 0; // clock low
    delay(10); 
    reading = PINC & B00000111; // read A0, A1, A2;
    if(reading != i)
      failed = true;
  }
  if (failed)
    digitalWrite(FAIL, HIGH);
  else 
    digitalWrite(PASS, HIGH);
}

void flash()
{
  digitalWrite(PASS, LOW);
  digitalWrite(FAIL, LOW);
  delay(100);
  for (int i = 0; i < 3; i++){
    digitalWrite(PASS, HIGH);
    digitalWrite(FAIL, HIGH);
    delay(100);
    digitalWrite(PASS, LOW);
    digitalWrite(FAIL, LOW);
    delay(100);
  }
  delay(150);
}

void setup()
{
  pinMode(PASS, OUTPUT);
  pinMode(FAIL, OUTPUT);

  flash(); // start of test 1
  logicTest();
  delay(2000);
  
  flash(); // start of test 2
  chipTest();
  delay(2000);
}

void loop()
{
  // Don't actually need code in here as we only want to test once.
  // can always reset arduino
}
