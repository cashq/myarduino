/*
  Serial Event example
 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and 
 clears it.
 
 A good test for this is to try it with a GPS receiver 
 that sends out NMEA 0183 sentences. 
 
 Created 9 May 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/SerialEvent
 
 */

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int state = 2;

void setup() {
  // initialize serial:
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  // reserve 200 bytes for the inputString:
  inputString.reserve(5);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    if (inputString == "on") {
      Serial.println("turn on");
      state = 1;
    } else if (inputString == "off") {
      Serial.println("turn off");
      state = 2;
    } else if (inputString == "blink") {
      Serial.println("blink");
      state = 3;
    } else {
      Serial.print("Receiving: ");
      Serial.println(inputString); 
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
  switch(state) {
    case 1:
      digitalWrite(13, HIGH);
      break;
    case 2:
      digitalWrite(13, LOW);
      break;
    case 3:
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      break;
    default:
      break;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      // add it to the inputString:
      inputString += inChar;
    }
  }
}


