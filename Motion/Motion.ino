int pirPin = D7;
int ledPin0 = D3;
int val;
 
void setup() {
Serial.begin(9600);

pinMode(ledPin0, OUTPUT);
digitalWrite(ledPin0, HIGH);
}
 
void loop()
{
val = digitalRead(pirPin);
//low = no motion, high = motion
if (val == LOW)
{
  Serial.println("No motion");
}
else
{
  Serial.println("Motion detected");
  digitalWrite(ledPin0, LOW);
  delay(4000);
  digitalWrite(ledPin0, HIGH);
}
 
delay(1000);
}
