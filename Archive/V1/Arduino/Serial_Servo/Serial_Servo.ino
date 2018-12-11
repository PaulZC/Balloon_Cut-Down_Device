// Cut-Down Device Servo Tester

// This code is written to run on PaulZC's Balloon Cut-Down Device, which is based on the Adafruit Feather M0 / M0 Adalogger.
// The code should work OK if run on an Arduino Zero too.

// Servo PWM (Yellow) is connected to D5
// Servo 5V (Red) is connected to USB / VBUS (5V)
// Servo 0V (Black) is connected to GND

// With grateful thanks to MartinL: http://forum.arduino.cc/index.php?topic=346731.msg2610904#msg2610904

// Servo Position:
// Min Position = 900
// Mid Position = 1500
// Max Position = 2100

// Pin Allocations:
// D15 / A1 / EXTINT8 (Port B Pin 8) = 'Open' switch input (pulled low by the switch)
// D16 / A2 / EXTINT9 (Port B Pin 9) = 'Close' switch input (pulled low by the switch)
// D14 / A0 (Port A Pin 2) = 'Plus' switch input (pulled low by the switch)
// D19 / A5 (Port B Pin 2) = 'Minus' switch input (pulled low by the switch)
// D5 (Port A Pin 15) = PWM signal to the servo
// D8 (Port A Pin 6) = MPM3610 5V Regulator ENable (pull high to enable the regulator and provide power to the servo)
// D9 / A7 (Port A Pin 7) = BUS voltage * 1/4.3 (Used to sense the USB or battery voltage)
// D13 (Port A Pin 17) = Red LED
// D1 (Port A Pin 10) = Serial1 TX : Can be used to connect to an external GPS receiver (RX)
// D0 (Port A Pin 11) = Serial1 RX : Can be used to connect to an external GPS receiver (TX)
// D20 (Port A Pin 22) = SDA : Can be used to connect to an external I2C device e.g. an altitude sensor
// D21 (Port A Pin 23) = SCL : Can be used to connect to an external I2C device e.g. an altitude sensor
// D11 (Port A Pin 16) = 3V3SW Enable : Pull low to provide switched 3V3 power to the 3V3SW pins (for Serial1 and I2C devices)
static const int openSwitch = 15;
static const int closeSwitch = 16;
static const int plusSwitch = 14;
static const int minusSwitch = 19;
const uint8_t pwmPin = 5;
static const int enable5V = 8;
static const int ledPin = 13;
static const int enable3V = 11;

String inString = ""; // string to hold serial input
int PWM = 1500; // Default PWM value

void setup()
{
  // Initialize digital pins
  pinMode(openSwitch, INPUT_PULLUP);
  pinMode(closeSwitch, INPUT_PULLUP);
  pinMode(plusSwitch, INPUT_PULLUP);
  pinMode(minusSwitch, INPUT_PULLUP);
  pinMode(pwmPin, OUTPUT);
  pinMode(enable5V, OUTPUT);
  digitalWrite(enable5V, HIGH); // Enable switched 5V power for servo
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Disable the LED
  pinMode(enable3V, OUTPUT);
  digitalWrite(enable3V, HIGH); // Disable switched 3V power

  // Flash red LED for 10 seconds
  for (int i=0; i < 25; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }    
  
  Serial.begin(115200);
  Serial.println("Cut-Down Device Servo Tester");
  Serial.println("Connect Black to GND");
  Serial.println("Connect Red to VBUS/USB (5V)");
  Serial.println("Connect Yellow to D5");
  Serial.println("Servo requires 5V so this will only work when connected to USB");
  Serial.println("Set Serial Monitor to 115200 Baud and Newline line ending");
  Serial.println();

  // Initialise PWM output for servo
  Serial.println("Initializing Servo PWM...");
  // Output 50Hz PWM on timer TCC0 (14-bit resolution)
  REG_GCLK_GENDIV = GCLK_GENDIV_DIV(3) |          // Divide the 48MHz clock source by divisor 3: 48MHz/3=16MHz
                    GCLK_GENDIV_ID(4);            // Select Generic Clock (GCLK) 4
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |           // Set the duty cycle to 50/50 HIGH/LOW
                     GCLK_GENCTRL_GENEN |         // Enable GCLK4
                     GCLK_GENCTRL_SRC_DFLL48M |   // Set the 48MHz clock source
                     GCLK_GENCTRL_ID(4);          // Select GCLK4
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  // Enable the port multiplexer for the PWM channel: timer TCC0 outputs
  PORT->Group[g_APinDescription[pwmPin].ulPort].PINCFG[g_APinDescription[pwmPin].ulPin].bit.PMUXEN = 1;
  // Connect the TCC0 timer to the port outputs - port pins are paired odd PMUO and even PMUXE
  // F & E specify the timers: TCC0, TCC1 and TCC2
  PORT->Group[g_APinDescription[2].ulPort].PMUX[g_APinDescription[2].ulPin >> 1].reg = PORT_PMUX_PMUXO_F | PORT_PMUX_PMUXE_F;
  PORT->Group[g_APinDescription[6].ulPort].PMUX[g_APinDescription[6].ulPin >> 1].reg = PORT_PMUX_PMUXO_F | PORT_PMUX_PMUXE_F;

  // Feed GCLK4 to TCC0 and TCC1
  REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |         // Enable GCLK4 to TCC0 and TCC1
                     GCLK_CLKCTRL_GEN_GCLK4 |     // Select GCLK4
                     GCLK_CLKCTRL_ID_TCC0_TCC1;   // Feed GCLK4 to TCC0 and TCC1
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  // Dual slope PWM operation: timers countinuously count up to PER register value then down 0
  REG_TCC0_WAVE |= TCC_WAVE_POL(0xF) |         // Reverse the output polarity on all TCC0 outputs
                    TCC_WAVE_WAVEGEN_DSBOTTOM;    // Setup dual slope PWM on TCC0
  while (TCC0->SYNCBUSY.bit.WAVE);               // Wait for synchronization

  // Each timer counts up to a maximum or TOP value set by the PER register,
  // this determines the frequency of the PWM operation:
  // 20000 = 50Hz, 10000 = 100Hz, 2500  = 400Hz
  REG_TCC0_PER = 20000;      // Set the frequency of the PWM on TCC0 to 50Hz
  while(TCC0->SYNCBUSY.bit.PER);

  // The CCBx register value corresponds to the pulsewidth in microseconds (us)
  REG_TCC0_CCB1 = PWM;       // TCC0 CCB1 - center the servo on D5
  while(TCC0->SYNCBUSY.bit.CCB1);

  // Divide the 16MHz signal by 8 giving 2MHz (0.5us) TCC0 timer tick and enable the outputs
  REG_TCC0_CTRLA |= TCC_CTRLA_PRESCALER_DIV8 |    // Divide GCLK4 by 8
                    TCC_CTRLA_ENABLE;             // Enable the TCC0 output
  while (TCC0->SYNCBUSY.bit.ENABLE);              // Wait for synchronization

  Serial.println("Servo PWM initialized!");
  Serial.println();
  Serial.println("Enter the servo PWM value (900:2100): ");
}
     
void loop() // run over and over again
{
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, move the servo:
    if (inChar == '\n') {
      PWM = inString.toInt(); // Convert stored serial string to int

      if ((PWM >= 900) and (PWM <= 2100)) {
        Serial.print("Setting PWM to: ");
        Serial.println(PWM);
        
        // Move the servo
        REG_TCC0_CCB1 = PWM; // TCC0 CCB1 - move the servo on D5
        while(TCC0->SYNCBUSY.bit.CCB1);
      }
      else {
        Serial.println("Invalid value!");
      }
      
      // clear the string for new input:
      inString = "";

      Serial.println("Enter the servo PWM value (900:2100): ");
    }
  }
}

