//The sample code for driving one way motor encoder
const byte encoder0pinA = 2;//A pin -> the interrupt pin 0
const byte encoder0pinB = 3;//B pin -> the digital pin 4
byte encoder0PinALast;
unsigned long duration;//the number of the pulses
boolean Direction;//the rotation direction 

float voltage;

int pwm;
float rad1;
unsigned long time; 

unsigned long rpm;     // rpm reading
volatile byte pulses;  // number of pulses
unsigned long timeold; 
// The number of pulses per revolution
// depends on your index disc!!
unsigned int pulsesperturn = 1440;

int dir1PinA = 8;
int dir2PinA = 9;
int speedPinA = 10; // Needs to be a PWM pin to be able to control motor speed

void setup()
{  
  Serial.begin(57600);//Initialize the serial port
  motorSetup();
  EncoderInit();//Initialize the module
}
 
void loop()
{
  for (int pwm=100; pwm <= 255; pwm++)
  {
  analogWrite(speedPinA, 0);//Sets speed variable via PWM 
  //Serial.print("Time: ");
  voltage = volts(pwm);

  rpm = rpm1(duration);

  rad1 = rad(rpm);
  time = millis();
  //prints time since program started
  Serial.print(time);
  
   
  //rpm=duration*600;
  //rpm=rpm/1440;

  //Serial.print("\tPulse:");
  //Serial.print(duration);

  Serial.print("\t Volatge:");
  Serial.print(voltage);

  Serial.print("\tPWM:");
  Serial.print(pwm); 
 
  
  Serial.print("\t Rad/s:");
  Serial.print(rad1);
  
  //Write it out to serial port
  Serial.print("\t RPM");
  Serial.println(rpm,DEC);
 
  timeold = millis();
  //pulses = 0;
  duration = 0;
  
  delay(100);
  }
  
  for (int pwm=255; pwm >= 100; pwm--)
  {
  analogWrite(speedPinA, 0);//Sets speed variable via PWM 
  //Serial.print("Time: ");
  voltage = volts(pwm);

  rpm = rpm1(duration);

  rad1 = rad(rpm);
  time = millis();
  //prints time since program started
  Serial.print(time);
  
   
  //rpm=duration*600;
  //rpm=rpm/1440;

  //Serial.print("\tPulse:");
  //Serial.print(duration);

  Serial.print("\t Volatge:");
  Serial.print(voltage);

  Serial.print("\tPWM:");
  Serial.print(pwm); 
 
  
  Serial.print("\t Rad/s:");
  Serial.print(rad1);
  
  //Write it out to serial port
  Serial.print("\t RPM");
  Serial.println(rpm,DEC);
 
  timeold = millis();
  //pulses = 0;
  duration = 0;
  
  delay(100);
  }
}
 
void EncoderInit()
{
  Direction = true;//default -> Forward  
  pinMode(encoder0pinB,INPUT);  
  attachInterrupt(0, wheelSpeed, CHANGE);
}
 
void wheelSpeed()
{
  int Lstate = digitalRead(encoder0pinA);
  if((encoder0PinALast == LOW) && Lstate==HIGH)
  {
    int val = digitalRead(encoder0pinB);
    if(val == LOW && Direction)
    {
      Direction = false; //Reverse
    }
    else if(val == HIGH && !Direction)
    {
      Direction = true;  //Forward
    }
  }
  encoder0PinALast = Lstate;
 
  if(!Direction)  duration++;
  else  duration--;
}

void motorSetup()
{
  pinMode(dir1PinA,OUTPUT);
  pinMode(dir2PinA,OUTPUT);
  pinMode(speedPinA,OUTPUT);
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);
}

float volts(int num1) {

   /* local variable declaration */
   float result;
   float num2;

   num2=num1;

   result=(num2-100)*0.01806;
   result=result+7.6;
 
   return result; 
}

int pwm1(float v){

  int pwmr;

  pwmr=(v-7.6)*55;
  pwmr=pwmr+100;

  return pwmr;

}
  
long rpm1(unsigned long d){

  long result1;
  
  result1 = (duration/2)*600;
  result1 = result1/1440;

  return result1;
}

float rad(long a){

  float result2;

  result2 = a*0.1047;

  return result2;
}

