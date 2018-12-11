// ###################
// # Cut-Down Device #
// ###################

// A servo-operated cut-down device for high altitude ballooning

// The device operates in three modes:

// Cut_Down:
// The M0 is woken up from deep sleep by an interrupt from the 'Open' or 'Close' switch
// It waits to see if the switch pin stays low for the required amount of time (intDuration) then
// moves the servo to the open or closed position as appropriate.
// By default, intDuration will be zero - i.e. the servo will move immediately.
// The M0 goes back into deep sleep when the servo move is complete.
//
// In reality, the required intDuration is decreased by 0.1 seconds to allow exact whole second key presses
// to trigger the device. E.g. if intDuration is set to '1' a key press of 0.9s or longer will trigger the device.
// This keeps things simpler when triggering the device from an Iridium Beacon via Mobile Terminated messaging.

// Set_Servo:
// If the M0 comes out of reset with the 'Plus' switch held low:
// The servo is moved to its mid-range position (PWM = 1500)
// Depending on whether the 'Plus' or 'Minus' switches are held down, the servo is moved towards
// one limit (PWM = 900) or the other (PWM = 2100)
// If the 'Open' switch is pulled low, the servo position is written into flash memory as servoOpen
// If the 'Closed' switch is pulled low, the servo position is written into flash memory as servoClosed
// The M0 will stay in this mode until reset

// Set_Duration:
// If the M0 comes out of reset with the 'Minus' switch held low:
// The LED will be used to flash the current intDuration
// intDuration can have a value of 0, 1, 2, 3, 4 or 5 seconds
// The LED will flash intDuration times (0.2s on, 0.2s off, repeating intDuration times every four seconds)
// If the 'Plus' switch is pulsed low, intDuration is increased by 1
// If the 'Minus' switch is pulsed low, intDuration is decreased by 1
// If either 'Open' or 'Close' is pulled low, intDuration is written into flash memory
// The M0 will stay in this mode until reset

// This code is intended to be run on Paul's Cut_Down Device:
// https://github.com/PaulZC/Cut-Down_Device

// The Cut-Down_Device PCB is based extensively on the Adafruit Feather M0 (Adalogger)
// https://www.adafruit.com/products/2796
// Set the Arduino Board type to "Adafruit Feather M0"

// With grateful thanks to MartinL: http://forum.arduino.cc/index.php?topic=346731.msg2610904#msg2610904

// Uses Cristian Maglie's FlashStorage library to store the settings in flash memory
// https://github.com/cmaglie/FlashStorage

// With grateful thanks to CaveMoa for his SimpleSleepUSB example
// https://github.com/cavemoa/Feather-M0-Adalogger
// https://github.com/cavemoa/Feather-M0-Adalogger/tree/master/SimpleSleepUSB

// With thanks to Nick Gammon for his ISR code examples:
// http://gammon.com.au/interrupts

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
#define VBUS A7 // Point VBUS to A7

// Flash Storage
#include <FlashStorage.h>
typedef struct { // Define a struct to hold the flash variable(s)
  int PREFIX; // Flash storage prefix (0xB5); used to test if flash has been written to before 
  int intDuration; // Minimum Open or Close interrupt duration
  int servoOpen; // Servo PWM value for the open position
  int servoClosed; // Servo PWM value for the closed position
  int CSUM; // Flash storage checksum; the modulo-256 sum of PREFIX and INTERVAL; used to check flash data integrity
} FlashVarsStruct;
FlashStorage(flashVarsMem, FlashVarsStruct); // Reserve memory for the flash variables
FlashVarsStruct flashVars; // Define the global to hold the variables

// Servo Position:
// Min Position = 900
// Mid Position = 1500
// Max Position = 2100
int PWM = 1500;
int servoOpen = 1500;
int servoClosed = 1500;
const int minServo = 900;
const int maxServo = 2100;

int intDuration = 0; // Default required minimum open/close interrupt duration

// Loop Steps
#define Cut_Down      0
#define Set_Servo     1
#define Set_Duration  2
int loop_step = Cut_Down;

volatile bool openSwitch_ISR_flag = false; // Open switch interrupt flag
volatile bool closeSwitch_ISR_flag = false; // Close switch interrupt flag

float vbat = 9.0; // Battery voltage
#define low_bat 6.0 // Low battery voltage

// Read battery voltage, compensating for resistor divider
void get_vbat() {
  vbat = analogRead(VBUS) * (4.3 * 3.3 / 1023.0);
}

void setup()
{
  // initialize digital pins

  pinMode(openSwitch, INPUT_PULLUP);
  pinMode(closeSwitch, INPUT_PULLUP);
  pinMode(plusSwitch, INPUT_PULLUP);
  pinMode(minusSwitch, INPUT_PULLUP);
  pinMode(pwmPin, OUTPUT);
  pinMode(enable5V, OUTPUT);
  digitalWrite(enable5V, LOW); // Disable switched 5V power for servo
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Disable the LED
  pinMode(enable3V, OUTPUT);
  digitalWrite(enable3V, HIGH); // Disable switched 3V power

  int plusSwitchState = digitalRead(plusSwitch); // Read the plus switch state
  int minusSwitchState = digitalRead(minusSwitch); // Read the minus switch state

  if ((plusSwitchState == 1) and (minusSwitchState == 1)) {
    // if both switches are high (not pressed) go into Cut_Down mode
    loop_step = Cut_Down;
  }
  else if ((plusSwitchState == 0) and (minusSwitchState == 1)) {
    // if plusSwitch is low (pressed) go into Set_Servo mode
    loop_step = Set_Servo;
  }
  else if ((plusSwitchState == 1) and (minusSwitchState == 0)) {
    // if minusSwitch is low (pressed) go into Set_Duration mode
    loop_step = Set_Duration;
  }
  else {
    loop_step = Cut_Down; // Default to Cut_Down mode if both switches are pressed
  }
  
  // See if servo settings have already been stored in flash
  // If they have, read them. If not, initialise them.
  flashVars = flashVarsMem.read(); // Read the flash memory
  int csum = flashVars.PREFIX + flashVars.intDuration + flashVars.servoOpen + flashVars.servoClosed; // Sum the prefix and data
  csum = csum & 0xff; // Limit checksum to 8-bits
  if ((flashVars.PREFIX == 0xB5) and (csum == flashVars.CSUM)) { // Check prefix and checksum match
    // Flash data is valid so update BEACON_INTERVAL using the stored value
    intDuration = flashVars.intDuration;
    servoOpen = flashVars.servoOpen;
    servoClosed = flashVars.servoClosed;
  }
  else {
    // Flash data is corrupt or hasn't been initialised so do that now
    flashVars.PREFIX = 0xB5; // Initialise the prefix
    flashVars.intDuration = intDuration; // Initialise the required interrupt duration
    flashVars.servoOpen = servoOpen; // Initialise the servo open position
    flashVars.servoClosed = servoClosed; // Initialise the servo closed position
    csum = flashVars.PREFIX + flashVars.intDuration + flashVars.servoOpen + flashVars.servoClosed; // Initialise the checksum
    csum = csum & 0xff;
    flashVars.CSUM = csum;
    flashVarsMem.write(flashVars); // Write the flash variables
  }

  delay(1000); // Delay to prevent USB recognition problems
  
  // flash red LED intDuration times on reset
  if (intDuration > 0) {
    for (int i=0; i < intDuration; i++) {
      digitalWrite(ledPin, HIGH);
      delay(200);
      digitalWrite(ledPin, LOW);
      delay(200);
    }    
  }

  // Initialise PWM output for servo
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

}

void openSwitch_ISR() // Interrupt service routine for open switch
{
  detachInterrupt(digitalPinToInterrupt(openSwitch)); // Detach the open switch interrupt
  detachInterrupt(digitalPinToInterrupt(closeSwitch)); // Detach the close switch interrupt
  openSwitch_ISR_flag = true;
}

void closeSwitch_ISR() // Interrupt service routine for close switch
{
  detachInterrupt(digitalPinToInterrupt(openSwitch)); // Detach the open switch interrupt
  detachInterrupt(digitalPinToInterrupt(closeSwitch)); // Detach the close switch interrupt
  closeSwitch_ISR_flag = true;
}

void loop() // run over and over again
{
  switch(loop_step) {

    case Cut_Down: {
      noInterrupts(); // Disable interrupts
      
      SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; // Get ready to put M0 into deep sleep

      // Clear the flags
      openSwitch_ISR_flag = false;
      closeSwitch_ISR_flag = false;

      // Clear any pending interrupts
      REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT8;
      REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT9;

      // (Re)Attach the interrupts
      attachInterrupt(digitalPinToInterrupt(openSwitch), openSwitch_ISR, LOW); // Attach interrupt for open switch
      attachInterrupt(digitalPinToInterrupt(closeSwitch), closeSwitch_ISR, LOW); // Attach interrupt for close switch
      
      interrupts(); // Re-enable interrupts
      
      // Put M0 into Deep Sleep
      __WFI();

      // Wake-up

      unsigned long wake_millis = millis(); // Record the wake-up time

      // Turn on LED to indicate wake-up
      digitalWrite(ledPin, HIGH);

      int switchReleased = 0; // flag to indicate if switch has been released
      
      // calculate the maximum wait time in millis depending on value of intDuration
      // if intDuration is non-zero, max_wait_millis is decreased by 0.1 seconds so that it will respond correctly to intDurations of whole seconds
      unsigned long max_wait_millis;
      if (intDuration > 0) {
        max_wait_millis = (((unsigned long)intDuration) * 1000UL) - 100UL;
      }
      else {
        max_wait_millis = 0;
      }

      if (openSwitch_ISR_flag == true) {
        // If the open switch caused the interrupt
        // Check to see if the switch is held longer than max_wait_millis
        while ((switchReleased == 0) && ((millis() - wake_millis) < max_wait_millis)) {
          switchReleased = digitalRead(openSwitch);
          delay(1); // Avoid too many calls to millis() as it suspends interrupts
        }
      }
      else {
        // If the close switch caused the interrupt
        // Check to see if the switch is held longer than max_wait_millis
        while ((switchReleased == 0) && ((millis() - wake_millis) < max_wait_millis)) {
          switchReleased = digitalRead(closeSwitch);
          delay(1); // Avoid too many calls to millis() as it suspends interrupts
        }        
      }

      // Either the switch has been released or max_wait_millis has been reached
      if ((switchReleased == 0) && ((millis() - wake_millis) >= max_wait_millis)) {
        // If the switch is still pressed and max_wait_millis has been reached, move the servo
        
        // Change the servo PWM
        if (openSwitch_ISR_flag == true) {
          PWM = servoOpen;
        }
        else {
          PWM = servoClosed;
        }
        REG_TCC0_CCB1 = PWM; // TCC0 CCB1 - change the servo PWM on D5
        while(TCC0->SYNCBUSY.bit.CCB1);

        // Power up the servo
        digitalWrite(enable5V, HIGH);
        
        // Wait 2 seconds (blocking!!) - flash LED if battery is low
        for (int i=0; i < 10; i++) {
          get_vbat(); // Read battery voltage
          digitalWrite(ledPin, HIGH);
          delay(100);
          if (vbat < low_bat) {
            digitalWrite(ledPin, LOW);
          }
          delay(100);
        }
        
        // Power down the servo
        digitalWrite(enable5V, LOW);
      }

      // Turn off the LED
      digitalWrite(ledPin, LOW);

    }
    break;
    
    case Set_Servo: {

      // Power up the servo
      digitalWrite(enable5V, HIGH);      

      bool decOne = false; // Flag to indicate that the PWM should be decremented by one
      bool incOne = false; // Flag to indicate that the PWM should be incremented by one

      int plusSwitchState = digitalRead(plusSwitch); // Read the plus switch state
      int minusSwitchState = digitalRead(minusSwitch); // Read the minus switch state
    
      if ((plusSwitchState == 0) and (minusSwitchState == 1)) {
        // If only the plusSwitch is low (pressed) decrement the PWM value
        decOne = true;
      }
      else if ((plusSwitchState == 1) and (minusSwitchState == 0)) {
        // If only the minusSwitch is low (pressed) increment the PWM value
        incOne = true;
      }
      // If neither or both switches are pressed, do nothing
      
      if ((incOne == true) || (decOne == true)) {
        // If either switch was pressed
        if (incOne == true) {
          if (PWM < maxServo) {
            PWM = PWM + 1;
          }
        }
        else {
          if (PWM > minServo) {
            PWM = PWM - 1;
          }
        }
      }

      // Update the servo PWM
      REG_TCC0_CCB1 = PWM; // TCC0 CCB1 - change the servo PWM on D5
      while(TCC0->SYNCBUSY.bit.CCB1);

      // Wait (blocking!!)
      delay(10);
        
      bool updateFlash = false; // Flag to indicate that the flash storage should be updated

      int openSwitchState = digitalRead(openSwitch); // Read the open switch state
      int closeSwitchState = digitalRead(closeSwitch); // Read the close switch state
    
      if ((openSwitchState == 0) and (closeSwitchState == 1)) {
        // If only the openSwitch is low (pressed) update servoOpen
        updateFlash = true;
        servoOpen = PWM;
      }
      else if ((openSwitchState == 1) and (closeSwitchState == 0)) {
        // If only the closeSwitch is low (pressed) update servoClose
        updateFlash = true;
        servoClosed = PWM;
      }
      // If neither or both switches are pressed, do nothing
        
      if (updateFlash == true) {
        // If either switch was pressed, update flash memory
        flashVars.PREFIX = 0xB5; // Reset the prefix (hopefully redundant!)
        flashVars.intDuration = intDuration; // Store the required interrupt duration
        flashVars.servoOpen = servoOpen; // Store the servo open position
        flashVars.servoClosed = servoClosed; // Store the servo closed position
        int csum = flashVars.PREFIX + flashVars.intDuration + flashVars.servoOpen + flashVars.servoClosed; // Update the checksum
        csum = csum & 0xff;
        flashVars.CSUM = csum;
        flashVarsMem.write(flashVars); // Write the flash variables
        
        digitalWrite(ledPin, HIGH); // Turn on the LED
        delay(2000); // Wait (blocking!)
        digitalWrite(ledPin, LOW); // Turn off the LED
        delay(2000); // Wait (blocking!)
        
        // Wait until both open and close switches have been released
        while ((openSwitchState == 0) || (openSwitchState == 0)) {
          openSwitchState = digitalRead(openSwitch); // Read the open switch state
          closeSwitchState = digitalRead(closeSwitch); // Read the close switch state
        }
      }
      
    }
    break;
    
    case Set_Duration: {
      // Read millis
      unsigned long millis_now;
      millis_now = millis();

      int double_secs;
      double_secs = (int)(millis_now / 2000UL); // Divide millis by 2000 to get double-seconds
      int hecto_millis;
      hecto_millis = (int)(millis_now - ((unsigned long)(double_secs * 2000))); // Remove double-seconds to leave hecto_millis containing 0-1999 milliseconds
      hecto_millis = hecto_millis / 100; // Divide by 100 to leave hecto_millis in the range 0-19

      if ((double_secs % 2) == 0) { // If double_secs is even
        if ((hecto_millis % 4) < 2) { // If hecto_millis is 0,1,4,5,8,9 etc...
          if (intDuration > 0) { // If intDuration is non-zero
            if ((hecto_millis / 4) < intDuration) {
              // If hecto_millis divided by four is greater than or equal to intDuration, turn on the LED
              digitalWrite(ledPin, HIGH); // Turn on the LED
            }
            else {
              digitalWrite(ledPin, LOW); // Turn off the LED
            }
          }
          else {
            digitalWrite(ledPin, LOW); // Turn off the LED
          }
        }
        else {
          digitalWrite(ledPin, LOW); // Turn off the LED
        }
      }
      // If secs is even, turn the LED off
      else {
        digitalWrite(ledPin, LOW); // Turn off the LED
      }

      int plusSwitchState = digitalRead(plusSwitch); // Read the plus switch state
      int minusSwitchState = digitalRead(minusSwitch); // Read the minus switch state

      if ((plusSwitchState == 0) || (minusSwitchState == 0)) {
        // If either the plus switch or the minus switch is pressed
        if ((plusSwitchState == 0) and (minusSwitchState == 1)) {
          // If only the plusSwitch is low (pressed) increment intDuration
          if (intDuration < 5) {
            intDuration = intDuration + 1;
          }
        }
        else if ((plusSwitchState == 1) and (minusSwitchState == 0)) {
          // If only the minusSwitch is low (pressed) decrement intDuration
          if (intDuration > 0) {
            intDuration = intDuration - 1;
          }
        }
        // If neither or both switches are pressed, do nothing

        while ((plusSwitchState == 0) || (minusSwitchState == 0)) {
          // Wait for both switches to be released
          delay(10); // Switch debounce
          plusSwitchState = digitalRead(plusSwitch); // Read the plus switch state
          minusSwitchState = digitalRead(minusSwitch); // Read the minus switch state          
        }
      }

      int openSwitchState = digitalRead(openSwitch); // Read the open switch state
      int closeSwitchState = digitalRead(closeSwitch); // Read the close switch state
    
      if ((openSwitchState == 0) || (closeSwitchState == 0)) {
        // If either switch was pressed, update flash memory
        flashVars.PREFIX = 0xB5; // Reset the prefix (hopefully redundant!)
        flashVars.intDuration = intDuration; // Store the required interrupt duration
        flashVars.servoOpen = servoOpen; // Store the servo open position
        flashVars.servoClosed = servoClosed; // Store the servo closed position
        int csum = flashVars.PREFIX + flashVars.intDuration + flashVars.servoOpen + flashVars.servoClosed; // Update the checksum
        csum = csum & 0xff;
        flashVars.CSUM = csum;
        flashVarsMem.write(flashVars); // Write the flash variables
        
        digitalWrite(ledPin, HIGH); // Turn on the LED
        delay(2000); // Wait (blocking!)
        digitalWrite(ledPin, LOW); // Turn off the LED
        delay(2000); // Wait (blocking!)
        
        // Wait until both open and close switches have been released
        while ((openSwitchState == 0) || (openSwitchState == 0)) {
          openSwitchState = digitalRead(openSwitch); // Read the open switch state
          closeSwitchState = digitalRead(closeSwitch); // Read the close switch state
        }
      }

    }
    break;
      
  }
}

