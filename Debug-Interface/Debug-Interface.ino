

//Debug over UART settings
#define DebugOnOffPin 5


// bridge or switch between this digital pin and GND. If the bridge is detected the serial (UART) will be initialized

#define DebugActive 0 // If the digitalRead returns a 0 the bridge is connected
#define DebugInactive 1

int StoredDebugSwitchState = DebugInactive;

#define Serial_Speed 9600
//9600, 38400, 115200

//#define ON 1
//#define OFF 0

// Read serial Interface but do nothing special
void serialEvent() {
 int incomingByte;
 incomingByte = Serial.read();  // Statement(s)
 Serial.println("no keyboard commands implemented");
}

void debug_interface(void){
  int ActualDebugSwitchState = digitalRead(DebugOnOffPin);
  if(StoredDebugSwitchState == ActualDebugSwitchState){ return; }

  switch(ActualDebugSwitchState) {
    case DebugInactive: {
      debug("Debug will be disabled");
      Serial.end();      
      break;
      }
    case DebugActive: {
      Serial.begin(Serial_Speed);
      debug("Debug enabled");
      break;
    }
    default: {
      debug("default state unknown");
      break;
    }
  } 
  StoredDebugSwitchState = ActualDebugSwitchState;
}

void debug(String debub_string_to_uart){
 //if (StoredDebugSwitchState == DebugActive){
 Serial.println(String(Serial.availableForWrite()));
 Serial.println(debub_string_to_uart);
 //}
}
void setup() {
  
  Serial.end(); //set serial in a defined status
  StoredDebugSwitchState = DebugInactive;
  pinMode(DebugOnOffPin, INPUT_PULLUP); //initial PIN for debug switch with internal pullup resistant
  debug_interface(); // Check if debug is actice or not
  //pinMode(5, OUTPUT);
  //digitalWrite(5, HIGH);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
}
//----------------------------------------------------------------------------------------------------
// start loop
void loop() {
  debug_interface();  
}
