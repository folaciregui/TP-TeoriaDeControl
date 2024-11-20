// Pines del sensor ultrasónico
const int trigPin = 9;
const int echoPin = 10;

// Pin para controlar el motor usando PWM
const int motorPin = 6;

// Variables para medir la distancia
long duration;
int distance;

void setup() {
  // Configurar pines del sensor ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Configurar pin del motor
  pinMode(motorPin, OUTPUT);
  
  // Iniciar comunicación serial
  Serial.begin(9600);
}

void loop() {
  // Enviar pulso al trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Leer el tiempo que tarda el eco en regresar
  duration = pulseIn(echoPin, HIGH);
  
  // Calcular la distancia en centímetros
  distance = duration * 0.034 / 2;
  
  Serial.print("Distancia_maxima:");
  Serial.print(20);  // Valor fijo de 20
  Serial.print(",");
  
  Serial.print("Distancia_medida:");
  Serial.print(distance);  // Suponiendo que distance cambia en tiempo real
  Serial.print(",");
  
  Serial.print("Distancia_minima:");
  Serial.println(0);  // Valor fijo de 0

  
  // Controlar la velocidad del motor según la distancia
  if (distance > 20) {
    analogWrite(motorPin, 255); // Velocidad máxima si está lejos
  } else if (distance >= 10 && distance <= 20) {
    int speed = map(distance, 10, 20, 50, 255); // Mapea la distancia a una velocidad PWM
    // Entre 50 y el máximo porque sino la bombita no llega a cargar por la manguera, le falta fuerza
    analogWrite(motorPin, speed); 
  } else {
    analogWrite(motorPin, 0); // Apaga el motor si está cerca
  }
  
  delay(100);
}