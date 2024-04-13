// Déclaration des broches utilisées
const int trigPin = 11;
const int echoPin = 7;
const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

// Variables pour stocker la distance et la couleur de la LED
int distance;
int redValue;
int greenValue;
int blueValue;

void setup() {
  // Configuration des broches en entrée/sortie
  //pinMode(trigPin, OUTPUT);
  DDRB |=(1<<3);
  //pinMode(echoPin, INPUT);
  DDRD |=~(1<<echoPin);
  //pinMode(redPin, OUTPUT);
  DDRD |=(1<<redPin);
  //pinMode(greenPin, OUTPUT);
  DDRD |=(1<<greenPin);
  //pinMode(bluePin, OUTPUT);
  DDRD |= (1<<bluePin);

  // Initialisation de la LED à la couleur rouge
  redValue = 255;
  greenValue = 0;
  blueValue = 0;
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);

  // Démarrage de la communication série pour le débogage
  Serial.begin(9600);
}

void loop() {
  // Envoi d'une impulsion ultrasonique
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Mesure du temps de retour de l'écho
  int duration = pulseIn(echoPin, HIGH);

  // Calcul de la distance en centimètres
  distance = duration / 58;

  // Affichage de la distance pour le débogage
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Changement de couleur de la LED en fonction de la distance
  if (distance < 20 && distance > 0) {
    // Rouge vif
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
  }  else if (distance < 100 && distance > 20) {
    // Vert
    analogWrite(redPin, 255);
    analogWrite(greenPin, (distance - 20)*255/80);
    analogWrite(bluePin, (distance + 20)*255/80);
  }  else if (distance < 150 && distance > 100){
    // Bleu
      analogWrite(redPin, redValue);
      analogWrite(greenPin, greenValue);
      analogWrite(bluePin, blueValue);
    
  } else{
    // Bleu
    redValue = 255;
    greenValue = 0;
    blueValue = 255;
  }

  // Mise à jour de la couleur de la LED
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);

  // Attente avant la prochaine mesure
  delay(100);
}
