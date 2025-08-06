
const int flameSensor1 = 12;
//const int buzzer = 13;

const int motor1Forward= 2;
const int motor1Backward = 3;
const int motor2Forward = 4;
const int motor2Backward = 5;


int room1 = A0;
int room2 = A1;

bool fireDetected = false;
bool fireExtinguished = false;
bool fireFound = false;
int detectedRoom = 0;

void setup() {
  Serial.begin(9600);
  pinMode(motor1Forward, OUTPUT);
  pinMode(motor1Backward, OUTPUT);
  pinMode(motor2Forward, OUTPUT);
  pinMode(motor2Backward, OUTPUT);
  pinMode(flameSensor1, INPUT);
  //pinMode(flameSensor3, INPUT);

  
}

void loop() {
  if (!fireDetected) {
    int fire1 = analogRead(room1);
    int fire2 = analogRead(room2);
    Serial.println("Checking for fire...");

    
    if (fire1 > 650) {
      Serial.println("Fire detected in Room 1!");
      detectedRoom = 1;
      fireDetected = true;
     // digitalWrite(buzzer, HIGH);
      gotoRoom1();
    } else if (fire2 > 650) {
      Serial.println("Fire detected in Room 2!");
      detectedRoom = 2;
      fireDetected = true;
    //  digitalWrite(buzzer, HIGH);
      gotoRoom2();
    }
    delay(500); 
  }
}



void gotoRoom1(){
  forward();
  forward();
  forward();
  rotate360();
}

void gotoRoom2(){
  rotateleft(450);
  forward();
  forward();
  rotateright(450);
  forward();
  forward();
  forward();
  rotate360();
}

  void forward (){
  digitalWrite(motor2Forward, HIGH);
  digitalWrite(motor2Backward, LOW);
  delay(60);
  digitalWrite(motor1Forward, HIGH);
  digitalWrite(motor1Backward, LOW);
 
  
  delay(700);
  stopmotors();
  delay(400);
  }

 void stopmotors(){
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, LOW);
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Backward, LOW);
 }

void rotate360(){
  //int a=1;
  while(fireFound == false){
    rotateright(150);
    checkForFire();
    delay(300);}
  if(fireFound){
      stopmotors();
      Serial.println("fire found");
    }
}
 
 void rotateright(int k){
  digitalWrite(motor1Forward, HIGH);
  digitalWrite(motor1Backward, LOW);
  //Serial.println("motor1");
  digitalWrite(motor2Forward, LOW);
  digitalWrite(motor2Backward, HIGH);
  //Serial.println("motor2");
  delay(k); 
  stopmotors();
  delay(500);
  }
void rotateleft(int k){
  digitalWrite(motor1Forward, LOW);
  digitalWrite(motor1Backward, HIGH);
  digitalWrite(motor2Forward, HIGH);
  digitalWrite(motor2Backward, LOW);
  delay(k); 
  stopmotors();
  delay(500);
}



// void throwWater() {
//   do {
//     moveServo();
//     digitalWrite(relayPin, HIGH);
//     if (digitalRead(flameSensor4) == HIGH) {
//       fireExtinguished = true;
//       Serial.println("Fire extinguished!");
//     }
//   }
//   digitalWrite(relayPin, LOW); // Turn off relay after extinguishing fire
//   fireFound = false;          // Reset fireFound for next operation
// } while (!fireExtinguished);

// void moveServo() {
//   for(int k=0; k<1001; k++){
//     for (int pos = 15; pos <= 165; pos += 5) {  
//       fireServo.write(pos);
//       delay(30);  
//     }
//     for (int pos = 165; pos >= 15; pos -= 5) { 
//       fireServo.write(pos);
//       delay(30); 
//     }
//   if(digitalRead(flameSensor4)==HIGH){
//     break;
//   }
//   //delay(5000);
// }
// }

void checkForFire() {
  if (digitalRead(flameSensor1) == LOW) {
    fireFound = true;
  }
}