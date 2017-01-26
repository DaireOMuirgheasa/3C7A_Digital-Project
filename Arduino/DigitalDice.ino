//
//  Digital Dice Testbed
//  Created 25-1-17
//  Group 7
//    Mark Anderson
//    Eoin Gogarty
//    Rob Hanson
//    Daire Morrissy
//

/*
// I think this should do the job. I've not got the Arduino software installed so I can't test it for errors or if the ISR is syntactically correct but I'll check in college tomorrow

volatile bool inputs[4];
volatile bool outputs[4];
int counter = 0;
int errors = 0;

// Note only pins 2 & 3 can have interrupts attached with Uno model
// Pin 0-3 used for inputs
// Pin 4-7 used for outputs

ISR (PCINT2_vect){
    inputs[0] = digitalRead(0);
    inputs[1] = digitalRead(1);
    inputs[2] = digitalRead(2);
    inputs[3] = digitalRead(3);
    
    outputs[0] = digitalRead(4);
    outputs[1] = digitalRead(5);
    outputs[2] = digitalRead(6);
    outputs[3] = digitalRead(7);
    
    if (counter % 1000 == 0 && counter != 0){
        serial.println( counter," tests run, ", errors, " errors encountered");
    }
    
    if (inputs[0] == outputs[0] && inputs[1] == outputs[1] && inputs[2] == outputs[2] && inputs[3] == outputs[3])
        serial.println("Error:  Inputs and outputs do not match");
}

void setup() {
    // Pin setup
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    
    interrupts();  
}
*/

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

char logic_out[6]  = {13, 2, 8, 10, 12, 14};
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
      //break;
    }
  }
  
  PORTD = 0;
  reading = PIND & B10000000;
  if (reading != 128 || failed)
    digitalWrite(FAIL, HIGH);
  else
    digitalWrite(PASS, HIGH);  
}
void setup()
{
  pinMode(PASS, OUTPUT);
  pinMode(FAIL, OUTPUT);

  logicTest();
}

void loop()
{
  // Don't actually need code in here as we only want to test once.
}
