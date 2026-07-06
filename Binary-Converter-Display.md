# Binary Converter & Display

**Concept:** An Arduino/microcontroller project that converts decimal numbers to binary and displays them.  
(Relates to **CIT304** binary systems and data representation.)

## What to Build

- Read a decimal number from sensor/serial input
- Convert to binary
- Display on 8 LEDs (each LED = one bit)
- Show the binary equivalent on the Serial Monitor

## Project Setup (5 mins)

### Components Needed

- Arduino Uno/Nano
- 8 LEDs (any color)
- 8 × 220Ω resistors
- 1 × USB cable
- Breadboard and jumper wires

### Wiring

Connect 8 LEDs to Arduino digital pins **D2–D9** (one LED per pin).

#### Suggested Pin Mapping

- LED 1 (leftmost / MSB) → D9
- LED 2 → D8
- LED 3 → D7
- LED 4 → D6
- LED 5 → D5
- LED 6 → D4
- LED 7 → D3
- LED 8 (rightmost / LSB) → D2

For each LED:

1. Connect the Arduino pin to a **220Ω resistor**.
2. Connect the other end of the resistor to the LED **anode** (long leg).
3. Connect the LED **cathode** (short leg) to the breadboard **GND rail**.
4. Connect the breadboard GND rail to an Arduino **GND** pin.

> Each LED turns **ON** when its assigned Arduino pin is set **HIGH**.

## Complete Arduino Code

```cpp
// binary_display.ino
// Converts decimal numbers to binary and displays on 8 LEDs

const int LED_PINS[8] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  Serial.begin(9600);
  
  // Set all LED pins as OUTPUT
  for(int i = 0; i < 8; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  
  Serial.println("=== BINARY CONVERTER ===");
  Serial.println("Enter a number (0-255):");
}

void loop() {
  // Read input from Serial Monitor
  if(Serial.available()) {
    int decimal = Serial.parseInt();
    
    // Validate input (must be 0-255 for 8 bits)
    if(decimal >= 0 && decimal <= 255) {
      
      // Display on LEDs
      displayBinary(decimal);
      
      // Print to Serial Monitor
      Serial.print("Decimal: ");
      Serial.print(decimal);
      Serial.print(" → Binary: ");
      Serial.println(toBinaryString(decimal));
      
      // Show bit-by-bit breakdown
      Serial.println("LED Status (Left=MSB, Right=LSB):");
      Serial.print("Bit:   ");
      for(int i = 7; i >= 0; i--) Serial.print(i + " ");
      Serial.println();
      
      Serial.print("Value: ");
      for(int i = 7; i >= 0; i--) {
        int bit = (decimal >> i) & 1;
        Serial.print(bit + " ");
      }
      Serial.println("\n");
      
    } else {
      Serial.println("ERROR: Enter number between 0-255");
    }
  }
}

// Function: Display binary on LEDs
void displayBinary(int num) {
  for(int i = 0; i < 8; i++) {
    // Extract each bit from right to left
    int bit = (num >> i) & 1;
    
    // Pin 2 = Bit 7 (MSB), Pin 9 = Bit 0 (LSB)
    digitalWrite(LED_PINS[7 - i], bit);
    
    delay(100); // Small delay to see LEDs light up sequentially
  }
}

// Function: Convert to binary string for display
String toBinaryString(int num) {
  String binary = "";
  for(int i = 7; i >= 0; i--) {
    binary += ((num >> i) & 1) ? "1" : "0";
  }
  return binary;
}
```

## Testing Instructions (30 mins)

1. Upload the code to your Arduino.
2. Open **Serial Monitor** (`Ctrl+Shift+M`, `9600 baud`).
3. Test with the cases below.

### Test Cases

| Input | Expected Binary | Expected LED Pattern |
|------:|----------------:|----------------------|
| 0     | 00000000        | All OFF              |
| 1     | 00000001        | Rightmost LED ON     |
| 15    | 00001111        | Right 4 LEDs ON      |
| 128   | 10000000        | Leftmost LED ON      |
| 255   | 11111111        | All LEDs ON          |

### Example Output

```text
Decimal: 15
Binary : 00001111
```

## What You're Learning

- ✅ Von Neumann Architecture — Using registers (pins) to store bits
- ✅ Binary Representation — Converting decimal to binary (CIT332/CIT304)
- ✅ Bitwise Operations — Right shift (`>>`) and AND (`&`) operators
- ✅ Digital I/O — Controlling hardware with code
- ✅ Embedded Systems — Direct hardware manipulation
