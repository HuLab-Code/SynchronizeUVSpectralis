 /*
  Cycle LED Power

Turns on UV LED connected to pin 8 through a relay switch
when the user presses the foot pedal connected to pin 7

  Nripun Sredar
  nsredar@stanford.edu
*/

// Can change START *****************
int number_of_cycles = 3; 

int start_delay_time_in_ms = 10000;

int high_time_in_ms = 20000;
int low_time_in_ms = 30000;

String startString = "Start";
String stopString = "Stop";
// Can change STOP *****************




// **** DO NOT CHANGE AFTER HERE ***********

int inPin = 7;   // choose the input pin (for a pushbutton)
int val = 0;     // variable for reading the pin status

String inputString = "";         // a String to hold incoming data
bool cycleLED = false;  // whether the string is complete
int relay_pin = 8; // Do not change
int counter = 0;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relay_pin, OUTPUT);
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  val = digitalRead(inPin);  // read input value
  if(val == 0){
    cycleLED = true;
  }
  
  Serial.println(val);
  if (cycleLED && counter ==0) {
    digitalWrite(LED_BUILTIN, LOW);// turn the builtin LED on (HIGH is the voltage level)
    Serial.println("Low");
    digitalWrite(relay_pin, LOW);  // turn the LED on (HIGH is the voltage level)
    delay(start_delay_time_in_ms);         // wait for a few milliseconds
    counter = counter + 1;
  }
  
  if (cycleLED && counter < number_of_cycles) {
    digitalWrite(LED_BUILTIN, HIGH);// turn the builtin LED on (HIGH is the voltage level)
    Serial.println("High");
    digitalWrite(relay_pin, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(high_time_in_ms);         // wait for a few milliseconds

    digitalWrite(LED_BUILTIN, LOW);// turn the builtin LED on (LOW is the voltage level)
    Serial.println("Low");
    digitalWrite(relay_pin, LOW);  // turn the LED on (LOW is the voltage level)
    delay(low_time_in_ms);         // wait for a few milliseconds

    counter = counter + 1;
  }
  if(!cycleLED || counter == number_of_cycles)
  {
   digitalWrite(LED_BUILTIN, LOW);// turn the builtin LED on (LOW is the voltage level)
//   Serial.println("OFF");
   digitalWrite(relay_pin, LOW);  // turn the LED on (LOW is the voltage level)
   delay(1000);         // wait for a few milliseconds 
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n' && inputString == startString+"\n") {
      Serial.println("Low");
      inputString = "";
      delay(start_delay_time_in_ms);
      cycleLED = false;
      counter = 0;
    }
    else if(inChar == '\n' && inputString == stopString+"\n") {
      cycleLED = false;
      inputString = "";
    }
    if (inChar == '\n')
    {
      inputString = "";
    }

    
  }
}
