int ledPin0 = D2;
int ledPin1 = D3;
int ledPin2 = D4;
int ledPin3 = D5;
int ledPin4 = D6;
int ledPin5 = D7;
int ledPin6 = D8;
int ledPin7 = D9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting...");

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Loop...");


  digitalWrite(ledPin0, LOW);
  delay(1000);
  digitalWrite(ledPin1, LOW);
  delay(1000);
  digitalWrite(ledPin2, LOW);
  delay(1000);
  digitalWrite(ledPin3, LOW);
  delay(1000);
  digitalWrite(ledPin4, LOW);
  delay(1000);
  digitalWrite(ledPin5, LOW);
  delay(1000);
  digitalWrite(ledPin6, LOW);
  delay(1000);
  digitalWrite(ledPin7, LOW);
  
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
} 
