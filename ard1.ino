int LED1 = 8;
int LED2 = 7;
int LED3 = 6;

String command;
String flashlightStatus;

int state = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  flashlightStatus = "locked";

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()) {
    command = Serial.readStringUntil('\n');
  
    // Unlocking flashlight
    Serial.println(command);

    if(command == "unlock" && flashlightStatus == "locked") {
      digitalWrite(LED2, HIGH);
      flashlightStatus = "unlocked";
      delay(3000);
      digitalWrite(LED2, LOW);
      state = 0;
    } 
    // Locking flashlight
    if(command == "lock" && flashlightStatus == "unlocked") {
      digitalWrite(LED2, HIGH);
      delay(100);
      digitalWrite(LED2, LOW);
      delay(200);
      digitalWrite(LED2, HIGH);
      delay(100);
      digitalWrite(LED2, LOW);
      delay(200);
      digitalWrite(LED2, HIGH);
      delay(100);
      digitalWrite(LED2, LOW);
      delay(200);
      flashlightStatus = "locked";
      digitalWrite(LED1, LOW);
      digitalWrite(LED3, LOW);
    }

    if(command == "button") {
      state += 1;
      Serial.println(state);
    }
    
    if(state == 4) {
      state = 0;
    }
  }

  // check which state currently active
  if(state == 0) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);
  }
  
  if(state == 1 && flashlightStatus == "unlocked") {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED3, HIGH);
  }

  if(state == 2 && flashlightStatus == "unlocked") {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED3, HIGH);
    delay(200);
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);
    delay(300);
  }

  if(state == 3 && flashlightStatus == "unlocked") {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED3, LOW);
    delay(200);
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, HIGH);
    delay(200);
  }
  
  command = "";
}
