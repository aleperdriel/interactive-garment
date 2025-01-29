#include <Servo.h>

const int trigPins[2] = {2, 4};  
const int echoPins[2] = {3, 5};  
const int servoPins[2] = {9, 10}; 

Servo servos[2];

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 2; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
    servos[i].attach(servoPins[i]);
    servos[i].write(37);  // Set servos to the middle of 0°-90°
  }

  Serial.println("System ready!");
}

void loop() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(trigPins[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);

    long duration = pulseIn(echoPins[i], HIGH, 20000); // Timeout 20ms

    int distance = duration * 0.034 / 2;  

    if (distance < 2 || distance > 400) continue;  

    int angle = map(constrain(distance, 5, 100), 5, 150, 90, 0);
    servos[i].write(angle);

    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(distance);
    Serial.print(" cm → Servo ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(angle);
    Serial.println("°");
  }
}
