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

void setup()
{
  pinMode(PASS, OUTPUT);
  pinMode(FAIL, OUTPUT);
  
  // other stuff
}

void loop()
{
  // Don't actually need code in here as we only want to test once.
}
