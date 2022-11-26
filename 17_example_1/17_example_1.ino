#include <Servo.h>

// Arduino pin assignment

#define PIN_POTENTIOMETER 3 // Potentiometer at Pin A3
// Add IR Sensor Definition Here !!!
#define PIN_SERVO 10
#define PIN_LED 3

#define _DIST_MIN 1000
#define _DIST_MAX 2500

#define _DUTY_MIN 553  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 2399 // servo full counter-clockwise position (180 degree)

#define LOOP_INTERVAL 50   // Loop Interval (unit: msec)

#define _EMA_ALPHA 0.3

Servo myservo;
unsigned long last_loop_time;   // unit: msec
float dist, duty, dist_ema = 0;

void setup()
{
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(57600);
  dist = (6762.0/(analogRead(PIN_POTENTIOMETER)-9)-4.0)*10.0 - 60.0;
}

void loop()
{
  unsigned long time_curr = millis();
  int a_value, duty;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Remove Next line !!!
  // Read IR Sensor value !!!
  a_value = analogRead(PIN_POTENTIOMETER);
  
  // Convert IR sensor value into distance !!!
  float prev_dist = dist;
  dist = (6762.0/(a_value-9)-4.0)*10.0 - 60.0;
  
  // we need distance range filter here !!!
  if (dist < _DIST_MIN) {
    dist = prev_dist;
    digitalWrite(PIN_LED, 1);
  } else if (dist > _DIST_MAX) {
    dist = prev_dist;
    digitalWrite(PIN_LED, 1);
  } else {
    prev_dist = dist;
    digitalWrite(PIN_LED, 0);
  }
  // we need EMA filter here !!!
  dist_ema = _EMA_ALPHA * dist + (1-_EMA_ALPHA)*dist_ema;
  // map distance into duty
  duty = (1846 / 15) * dist_ema - (3692 / 3);
  myservo.writeMicroseconds(duty);

  // print IR sensor value, distnace, duty !!!
  Serial.print("MIN: "); Serial.print(_DIST_MIN);
  Serial.print(", IR: "); Serial.print(a_value);
  Serial.print(", dist: "); Serial.print(dist);
  Serial.print(", ema: "); Serial.print(dist_ema);
  Serial.print(", servo: "); Serial.print(duty);
  Serial.print(", MAX: "); Serial.print(_DIST_MAX);
  Serial.println();
  //Serial.print("ADC Read: "); Serial.print(a_value);
  //Serial.print(" = ");
  //Serial.print((a_value / 1024.0) * 5.0);
  //Serial.print(" Volt => Duty : ");
  //Serial.print(duty);
  //Serial.println("usec");
}
