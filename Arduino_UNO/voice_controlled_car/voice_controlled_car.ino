#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11); 


const uint8_t IN1 = 2;
const uint8_t IN2 = 3;
const uint8_t IN3 = 4;
const uint8_t IN4 = 7;
const uint8_t ENA = 5;
const uint8_t ENB = 6;

const bool RIGHT_INVERT = true;
const bool LEFT_INVERT  = false;


const uint8_t TRIG_PIN = 8;
const uint8_t ECHO_PIN = 9;

const uint8_t TRIG_PIN2 = A0;
const uint8_t ECHO_PIN2 = A1;


const uint8_t TRIG_BACK = A2;
const uint8_t ECHO_BACK = A3;

const unsigned int OBSTACLE_CM = 20;

int motorSpeed = 200;
String readBuf = "";


const uint8_t BUZZER_PIN = 12;
const bool BUZZER_PASSIVE = true;
bool buzzerOn = false;


bool frontBlocked = false;
bool backBlocked  = false;

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT); pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN2, OUTPUT); pinMode(ECHO_PIN2, INPUT);

  pinMode(TRIG_BACK, OUTPUT); pinMode(ECHO_BACK, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  stopCar();
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void loop() {
  readBluetooth();

  
  int frontDist = measureFront();
  int backDist  = measureOne(TRIG_BACK, ECHO_BACK);

  
  if (frontDist > 0 && frontDist <= OBSTACLE_CM) {
    if (!frontBlocked) {
      frontBlocked = true;
      stopCar();
      startBuzzer();
      BT.println("front_obstacle");
    }
  } else {
    if (frontBlocked) {
      frontBlocked = false;
      stopBuzzer();
      BT.println("front_clear");
    }
  }


  if (backDist > 0 && backDist <= OBSTACLE_CM) {
    if (!backBlocked) {
      backBlocked = true;
      stopCar();
      startBuzzer();
      BT.println("back_obstacle");
    }
  } else {
    if (backBlocked) {
      backBlocked = false;
      stopBuzzer();
      BT.println("back_clear");
    }
  }

  
  if (readBuf.length() > 0) {
    String cmd = readBuf;
    readBuf = "";
    cmd.trim(); cmd.toLowerCase();

    Serial.print("Cmd: "); Serial.println(cmd);

    if (cmd == "forward") {
      if (!frontBlocked) moveForward();
      else BT.println("blocked_front");

    } else if (cmd == "back" || cmd == "backward") {
      if (!backBlocked) moveBack();
      else BT.println("blocked_back");

    } else if (cmd == "left") {
      turnLeft();

    } else if (cmd == "right") {
      turnRight();

    } else if (cmd == "stop" || cmd == "off") {
      stopCar();

    } else if (cmd.startsWith("speed")) {
      int s = parseSpeed(cmd);
      if (s >= 0) {
        motorSpeed = constrain(s, 0, 255);
        analogWrite(ENA, motorSpeed);
        analogWrite(ENB, motorSpeed);
      }
    }
  }

  delay(20);
}



void setRight(boolean forward) {
  bool a = forward; bool b = !forward;
  if (RIGHT_INVERT) { a = !a; b = !b; }
  digitalWrite(IN1, a ? HIGH : LOW);
  digitalWrite(IN2, b ? HIGH : LOW);
}
void setLeft(boolean forward) {
  bool a = forward; bool b = !forward;
  if (LEFT_INVERT) { a = !a; b = !b; }
  digitalWrite(IN3, a ? HIGH : LOW);
  digitalWrite(IN4, b ? HIGH : LOW);
}

void moveForward() {
  setRight(true); setLeft(true);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  BT.println("forward");
}
void moveBack() {
  setRight(false); setLeft(false);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  BT.println("back");
}
void turnLeft() {
  setRight(true); setLeft(false);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, 0);
  BT.println("left");
}
void turnRight() {
  setRight(false); setLeft(true);
  analogWrite(ENA, 0);
  analogWrite(ENB, motorSpeed);
  BT.println("right");
}
void stopCar() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
  BT.println("stopped");
}



void readBluetooth() {
  while (BT.available()) {
    char c = BT.read();
    if (c != '\n' && c != '\r') readBuf += c;
  }
}



int measureOne(uint8_t trigPin, uint8_t echoPin) {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long dur = pulseIn(echoPin, HIGH, 30000UL);
  if (dur == 0) return 0;

  return (dur * 0.0343 / 2.0);
}


int measureFront() {
  int d1 = measureOne(TRIG_PIN, ECHO_PIN);
  int d2 = measureOne(TRIG_PIN2, ECHO_PIN2);

  if (d1 == 0 && d2 == 0) return 0;
  if (d1 == 0) return d2;
  if (d2 == 0) return d1;
  return min(d1, d2);
}



int parseSpeed(const String &cmd) {
  int i = cmd.indexOf(' ');
  if (i < 0) return -1;
  String n = cmd.substring(i + 1);
  n.trim();
  for (unsigned int j = 0; j < n.length(); j++)
    if (!isDigit(n[j])) return -1;
  return n.toInt();
}



void startBuzzer() {
  if (buzzerOn) return;
  buzzerOn = true;
  if (BUZZER_PASSIVE) tone(BUZZER_PIN, 2000);
  else digitalWrite(BUZZER_PIN, HIGH);
}
void stopBuzzer() {
  if (!buzzerOn) return;
  buzzerOn = false;
  if (BUZZER_PASSIVE) noTone(BUZZER_PIN);
  else digitalWrite(BUZZER_PIN, LOW);
}