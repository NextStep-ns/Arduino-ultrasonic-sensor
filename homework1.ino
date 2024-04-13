// C++ code
//
int trigPin = 3;
int echoPin = 2;
int redPin = 11;
int greenPin = 9;
int bluePin = 10;
int buzzerPin= 8;

long read_echo;
long cm;

long readdistance(int triggerPin, int echoPin)
{
 DDRD|=(1<<4);
 //digitalWrite(trigPin, LOW); 
 PORTD &=~(1<<4);
 delayMicroseconds(2);
  
 //digitalWrite(trigPin, HIGH); 
 PORTD |=(1<<4);
 delayMicroseconds(10);
 //digitalWrite(trigPin, LOW);
 PORTD &=~(1<<4);
   
 DDRD &=~(1<<5); 
 return pulseIn(echoPin, HIGH);
}


void setup()
{
  Serial.begin(9600);
  
  DDRB|=(1<<2);
  DDRB|=(1<<4);
  DDRB|=(1<<3);
  DDRB|=(1<<5);
  
  //digitalWrite(redPin, LOW);
  PORTB &=~(1<<2);
  //digitalWrite(greenPin, LOW);
  PORTB &=~(1<<4);
  //digitalWrite(bluePin, LOW);
  PORTD &=~(1<<3);
  //digitalWrite(buzzerPin, LOW);
  PORTB &=~(1<<5);
  
  delay(2000);
}

void loop()
{
  cm = 0.01723*readdistance(trigPin, echoPin);
  Serial.print("Distance in cm :");
  Serial.println(cm);
  
  if (cm <= 15)
  {
    //digitalWrite(greenPin, LOW);
    PORTB &=~(1<<4);
    //digitalWrite(redPin, LOW);
    PORTB &=~(1<<2);
    //digitalWrite(bluePin, HIGH);
    PORTB |=(1<<3);
    //digitalWrite(buzzerPin, HIGH);
    PORTB |=(1<<5);
    delay(250);
    //digitalWrite(bluePin, LOW);
    PORTB &=~(1<<3);
    //digitalWrite(buzzerPin, LOW);
    PORTB &=~(1<<5);
  }
  
  if (15 < cm && cm <= 150)
  {
    //analogWrite(greenPin, 1.275*cm);
    OCR1A = 1.275*cm;
    //analogWrite(redPin, 190-1.275*cm);
    OCR2A = (190-1.275*cm);
    //analogWrite(bluePin, 0);
    OCR1B = 0;
    //digitalWrite(buzzerPin, LOW);
    PORTB &=~(1<<5);
  }
  
  if (150 < cm && cm <= 300)
  {
      //digitalWrite(greenPin, HIGH);
    	PORTB |=(1<<4);
      //digitalWrite(redPin, LOW);
    	PORTB &=~(1<<2);
      //digitalWrite(bluePin, LOW);
    	PORTB &=~(1<<3);
      //digitalWrite(buzzerPin, LOW);
    	PORTB &=~(1<<5);
  }
  
  if (cm > 300)
  {
    //digitalWrite(greenPin, LOW);
    PORTB &=~(1<<4);
    //digitalWrite(redPin, LOW);
    PORTB &=~(1<<2);
    //digitalWrite(bluePin, LOW);
    PORTB &=~(1<<3);
    //digitalWrite(buzzerPin, LOW);
    PORTB &=~(1<<5);
  }

  delay(70);
}