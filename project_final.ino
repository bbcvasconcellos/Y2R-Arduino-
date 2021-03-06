/*
Author: Bruno Vasconcellos
Project: Y2R - Autonomous robot car
Description: This project uses the Ultrasonic sensor to detect any obstacles on the way of the
robot car. If an obstacle is far away from it, the robot should move with max speed.
If the robot is approaching an obstacle, it will reduce its speed.
If it is really close to an object, will try 3 times to turn to the right; case it fails it will keep 
turning left until it finally moves out of the collision route
Note: pins can be modified according to user's own decision. Make sure that r and l speed pins are attached to
a pwd pin(~) in the arduino board 
*/

//right motor pins
int motor_in1R = 8;
int motor_in2R = 7;
int r_speed = 6;

//left motor pins
int motor_in3L = 13;
int motor_in4L = 12;
int l_speed = 11;

//ultrasonic sensor pins
int trig = 4;
int echo = 2;

int duration, count = 0;
float distance;

void setup() {
  
  Serial.begin(9600);
  
  //set the right motor pins
  pinMode(motor_in1R, OUTPUT);
  pinMode(motor_in2R, OUTPUT);
  pinMode(r_speed, OUTPUT);
  
  //set the left motor pins
  pinMode(motor_in3L, OUTPUT);
  pinMode(motor_in4L, OUTPUT);
  pinMode(l_speed, OUTPUT);
  
  //US sensor pins
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

}

void loop() {
  
  //sets the ultrasonic sensor
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  delayMicroseconds(3);
  
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.017;
  delay(10);
  
  //move forward at high speed
  if(distance >= 40){
    
    digitalWrite(motor_in1R, HIGH);
    digitalWrite(motor_in2R, LOW);
    analogWrite(r_speed, 250);
  
    digitalWrite(motor_in3L, HIGH);
    digitalWrite(motor_in4L, LOW);
    analogWrite(l_speed, 250);
    
    count = 0;
  }
  
  //reduce speed as it might be nearing a possible obstacle
  if(distance < 40 && distance >= 19){
    digitalWrite(motor_in1R, HIGH);
    digitalWrite(motor_in2R, LOW);
    analogWrite(r_speed, 127);
  
    digitalWrite(motor_in3L, HIGH);
    digitalWrite(motor_in4L, LOW);
    analogWrite(l_speed, 127);
    
    count = 0;
  }
  
  //if an obstacle is found within 17cm of range
  if(distance < 19 && count < 3){
    
    //1st: stops the car
    digitalWrite(motor_in1R, LOW);
    digitalWrite(motor_in2R, LOW);
    digitalWrite(motor_in3L, LOW);
    digitalWrite(motor_in4L, LOW);
    delay(500);
    
    //2nd: reverses the car
    digitalWrite(motor_in1R, LOW);
    digitalWrite(motor_in2R, HIGH);
    //analogWrite(r_speed, 127);
    digitalWrite(motor_in3L, LOW);
    digitalWrite(motor_in4L, HIGH);
    //analogWrite(l_speed, 127);
    delay(2000);
    
    //3rd: stops the car 
    digitalWrite(motor_in1R, LOW);
    digitalWrite(motor_in2R, LOW);
    digitalWrite(motor_in3L, LOW);
    digitalWrite(motor_in4L, LOW);
    delay(500);
    
    //4th: turns the car right
    digitalWrite(motor_in1R, HIGH);
    digitalWrite(motor_in2R, LOW);
    //analogWrite(r_speed, 127);
    digitalWrite(motor_in3L, LOW);
    digitalWrite(motor_in4L, LOW);
    delay(2000);
    
    count++;
    
  }
  
  //if the count is over 3, the car will left
  if(distance < 19 && count >= 3){
    
    //1st: stops the car
    digitalWrite(motor_in1R, LOW);
    digitalWrite(motor_in2R, LOW);
    digitalWrite(motor_in3L, LOW);
    digitalWrite(motor_in4L, LOW);
    delay(500);
    
    //2nd: reverses the car
    digitalWrite(motor_in1R, LOW);
    digitalWrite(motor_in2R, HIGH);
    //analogWrite(r_speed, 127);
    digitalWrite(motor_in3L, LOW);
    digitalWrite(motor_in4L, HIGH);
    //analogWrite(l_speed, 127);
    delay(2000);
    
    //3rd: stops the car 
    digitalWrite(motor_in1R, LOW);
    digitalWrite(motor_in2R, LOW);
    digitalWrite(motor_in3L, LOW);
    digitalWrite(motor_in4L, LOW);
    delay(500);
    
    //4th: turns the car left
    digitalWrite(motor_in1R, LOW);
    digitalWrite(motor_in2R, LOW);
    digitalWrite(motor_in3L, HIGH);
    digitalWrite(motor_in4L, LOW);
    //analogWrite(l_speed, 127);
    delay(2000);
  }
  
  delay(100);
}
