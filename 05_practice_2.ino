#define PIN_LED 7
#define turn_on 0

int count = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(PIN_LED, turn_on);
  digitalWrite(PIN_LED, turn_on);
  delay(1000);
  int n = 5;
  
  while(n--){
    digitalWrite(PIN_LED, !turn_on);
    delay(100);
    digitalWrite(PIN_LED, turn_on);
    delay(100);
  }
  digitalWrite(PIN_LED, !turn_on);
  while(1){}
}
