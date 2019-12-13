int potPin = 2;
int ledPin = 13;
int val = 0;


void setup() {
Serial.begin(9600);
Serial.println("Hello World");

pinMode(ledPin,OUTPUT);



}

void loop() {
  int aux;
  if(val>500){
    aux=(val-500)/2;
    if(aux>255){
      aux=255;
      }
    analogWrite(5,aux);
    analogWrite(3,0);
    }
  if(val<500){
    aux=(500-val)/2;
    if(aux>255){
      aux=255;
      }
    analogWrite(3,aux);
    analogWrite(5,0);
    }

  val = analogRead(potPin);
  Serial.println(val);
  /*digitalWrite(ledPin,HIGH);

  delay(val);

  digitalWrite(ledPin,LOW);
  delay(val);*/
}
