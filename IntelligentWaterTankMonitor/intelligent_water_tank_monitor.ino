// intelligent_water_tank_monitor.ino
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG_PIN 12
#define ECHO_PIN 11
#define RELAY_PIN 10
#define OLED_RESET -1

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Tank dimensions (adjust for your tank)
#define TANK_HEIGHT_CM 400  // Max water height in cm
#define TANK_DIAMETER_CM 20  // Diameter in cm

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Thresholds
#define WATER_LEVEL_LOW 30    // 30% - turn pump ON
#define WATER_LEVEL_HIGH 80   // 80% - turn pump OFF
#define WARNING_LEVEL 95      // 95% - overflow warning

void setup() {
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay OFF (active LOW)
  
  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while(1);
  }
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Water Tank Monitor");
  display.display();
  delay(2000);
}

void loop() {
  float distance = readDistance();
  float waterLevel = calculateWaterLevel(distance);
  
  // Update display
  updateDisplay(waterLevel);
  
  // Control pump based on water level
  controlPump(waterLevel);
  
  // Send data to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Water Level: ");
  Serial.print(waterLevel);
  Serial.println("%");
  
  delay(1000);
}

float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout for 400cm
  
  if(duration == 0) {
    return TANK_HEIGHT_CM; // Return max distance if no reading
  }
  
  float distance = duration * 0.034 / 2;
  distance = constrain(distance, 0, 400); // Limit to sensor range
  
  return distance;
}

float calculateWaterLevel(float distance) {
  // Distance from sensor to water surface
  // Water level = (Tank Height - Distance) / Tank Height * 100
  float waterLevel = ((TANK_HEIGHT_CM - distance) / TANK_HEIGHT_CM) * 100;
  
  // Constrain to 0-100%
  waterLevel = constrain(waterLevel, 0, 100);
  
  return waterLevel;
}

void updateDisplay(float waterLevel) {
  display.clearDisplay();
  
  display.setCursor(0, 0);
  display.println("WATER TANK STATUS");
  display.println("==================");
  
  display.setCursor(0, 20);
  display.print("Level: ");
  display.print(waterLevel, 1);
  display.println("%");
  
  // Visual bar
  display.drawRect(0, 35, 128, 20, WHITE);
  int barWidth = map(waterLevel, 0, 100, 0, 126);
  display.fillRect(1, 36, barWidth, 18, WHITE);
  
  display.setCursor(0, 58);
  if(waterLevel < WATER_LEVEL_LOW) {
    display.println("PUMP: ON");
  } else if(waterLevel > WATER_LEVEL_HIGH) {
    display.println("PUMP: OFF");
  } else {
    display.println("PUMP: STANDBY");
  }
  
  display.display();
}

void controlPump(float waterLevel) {
  static bool pumpState = false;
  
  if(waterLevel < WATER_LEVEL_LOW && !pumpState) {
    digitalWrite(RELAY_PIN, LOW);  // Turn pump ON
    pumpState = true;
    Serial.println("Pump turned ON");
  }
  else if(waterLevel > WATER_LEVEL_HIGH && pumpState) {
    digitalWrite(RELAY_PIN, HIGH); // Turn pump OFF
    pumpState = false;
    Serial.println("Pump turned OFF");
  }
  
  // Overflow warning
  if(waterLevel >= WARNING_LEVEL) {
    Serial.println("WARNING: Tank nearly full!");
    // Could add buzzer here
  }
}