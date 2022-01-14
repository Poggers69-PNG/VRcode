#include <Mouse.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vx, vy;
int inputPin = 5;
bool enableMouse;

void setup() {
  Serial.begin(9600);
  Wire.being();
  mpu.initialize();
  enableMouse = true;
  pinmode(inputPin, INPUT);
  if (!mpu.testConnection()) {
    while (1);
  }
  Serial.println("Running...");
}

void loop() {
  int val = digitalRead(inputPin);
  if (val == HIGH) { // check if the input is HIGH
    //Place logic here to execute when button is pressed
    //Disables mouse movement while button is pressed, this allows you to set your view angle easily
    enableMouse = false;
  }
  else
  {
    enableMouse = true;
  }
  if (enableMouse)
  {
    mpu.getmotion6(&ax, &ay, &az, &gx, &gy, &gz);
    vx = -(gy)/150;
    Mouse.move(vx, vy);
    delay(20);
  }
  }
