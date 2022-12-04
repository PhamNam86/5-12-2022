String textMessage;
int command;

int led = 5;  //D5
 
const int TRIG_PIN_1 = 16; //A2
const int ECHO_PIN_1 = 17; //A3

const int TRIG_PIN_2 = 9;  //D9    ULTRASOUND SENSOR RIGHT
const int ECHO_PIN_2 = 10; //D10

const int TRIG_PIN_3 = 11; //D11   ULTRASOUND SENSOR LEFT
const int ECHO_PIN_3 = 12; //D12

float duration_1, distance_front;
float duration_2, distance_right;
float duration_3, distance_left;

void setup()
{
 
 Serial.begin(115200); 

 pinMode(led, OUTPUT);
 digitalWrite(led, LOW);

 
  pinMode(TRIG_PIN_1, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO_PIN_1, INPUT);  // set arduino pin to input mode
 
  pinMode(TRIG_PIN_2, OUTPUT); 
  pinMode(ECHO_PIN_2, INPUT); 

  pinMode(TRIG_PIN_3, OUTPUT); 
  pinMode(ECHO_PIN_3, INPUT); 
}

void control_speed()
{
   if(Serial.available()>0){
    textMessage = Serial.readString();
    Serial.println(textMessage); 
    delay(10);
  } 
  if(textMessage.indexOf("TURN ON")>=0)
  {
    analogWrite(led, 255);
    }
  if(textMessage.indexOf("MEDIUM")>=0)
    {
      analogWrite(led, 200);
      }
      if(textMessage.indexOf("LOWEST")>=0)
    {
      analogWrite(led, 150);
      }
      if(textMessage.indexOf("TURN OFF")>=0)
    {
      analogWrite(led, 0);
      }
}

void highest()
{
  analogWrite(led, 255);
  }
void medium()
{
  analogWrite(led, 200);
  }
void lowest()
{
  analogWrite(led, 150);
  }
  void stop_mos()
{
  analogWrite(led,0);
  }
void loop()
{

 while(Serial.available()){ 
  command = Serial.read();
  
      if (command == 'O') highest();
      else if (command == 'M') medium();
      else if (command == 'C') lowest();
      else if (command == 'P') stop_mos();
  }
  
  digitalWrite(TRIG_PIN_1, LOW);
  delayMicroseconds(2);
   // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN_1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_1, LOW);
  // measure duration of pulse from ECHO pin
  duration_1 = pulseIn(ECHO_PIN_1, HIGH);
  // calculate the distance
  distance_front = 0.017 * duration_1;
  // print the value to Serial Monitor
  
  //Serial.print(distance_cm);
  //Serial.println(" cm");
  
  
  //int sdata1 = digitalRead(19);        //IR SENSOR
  //Serial.println(sdata1); 
  int sdata1 = round(distance_front);    //ULTRASOUND SENSOR
  Serial.print("distance_1: ");
  Serial.println(sdata1); 

  /*if(sdata1 < 20)//(sdata1 == 1) ||
  {
      Serial.println("ON");
    }
  else
  {
      Serial.println("OFF");
    }
  */
  digitalWrite(TRIG_PIN_2, LOW);
  delayMicroseconds(2);
   // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_2, LOW);
  // measure duration of pulse from ECHO pin
  duration_2 = pulseIn(ECHO_PIN_2, HIGH);
  // calculate the distance
  distance_right = 0.017 * duration_2;
  // print the value to Serial Monitor
  
  //Serial.print(distance_cm);
  //Serial.println(" cm");
  
  
  //int sdata1 = digitalRead(19);        //IR SENSOR
  //Serial.println(sdata1); 
  int sdata2 = round(distance_right);    //ULTRASOUND SENSOR
  Serial.print("distance_2: ");
  Serial.println(sdata2);


  digitalWrite(TRIG_PIN_3, LOW);
  delayMicroseconds(2);
   // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_3, LOW);
  // measure duration of pulse from ECHO pin
  duration_3 = pulseIn(ECHO_PIN_3, HIGH);
  // calculate the distance
  distance_left = 0.017 * duration_3;
  // print the value to Serial Monitor
  
  //Serial.print(distance_cm);
  //Serial.println(" cm");
  
  
  //int sdata1 = digitalRead(19);        //IR SENSOR
  //Serial.println(sdata1); 
  int sdata3 = round(distance_left);    //ULTRASOUND SENSOR
  Serial.print("distance_3: ");
  Serial.println(sdata3);

    if((sdata3 <= 20 && sdata1 > 20 && sdata2 <= 20) || (sdata3 > 20 && sdata1 > 20 && sdata2 >20))
  {
      Serial.println("goBack");
    }
  if((sdata3 <=20 && sdata1 <=20 && sdata2 > 20) || (sdata3 <= 20 && sdata1 > 20 && sdata2 >20) )
  {
    Serial.println("goRight");
    }
  if((sdata3 > 20 && sdata1 <= 20 && sdata2 <= 20) || (sdata3 > 20 && sdata1 > 20 && sdata2 <= 20) || (sdata3 > 20 && sdata1 <= 20 && sdata2 > 20))
  {
    Serial.println("goLeft");
  }
  delay(1000);
}

