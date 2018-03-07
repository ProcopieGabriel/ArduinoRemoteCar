#include <Servo.h>
#include <IRremote.h>
#define echoPin1 5//echopin
#define trigPin1 7//trigpin
int angle=90;//unghi servo
int motorpin1=3;//motoare spate pin
int motorpin2=4;//   -/-
int ledPin2=A1;//far
int RECV_PIN = 6;//telecomanda
int ledPin1=A0;//far
int motorpin3=8;//motor fata pin
int motorpin4=9;// -/-
long distance1,duration1,distance2,duration2,distance3,duration3,distance4;//date senzor
Servo myservo;//declarare obiect de tip  servo
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup() 
{   pinMode(trigPin1,OUTPUT);
    pinMode(echoPin1,INPUT);
    myservo.attach(2);//servo pin 2
    pinMode(RECV_PIN, INPUT);  
    irrecv.enableIRIn();
    pinMode(motorpin1,OUTPUT);
    pinMode(motorpin2,OUTPUT);
    pinMode(motorpin3,OUTPUT);
    pinMode(motorpin4,OUTPUT);
    pinMode(ledPin1,OUTPUT);
    pinMode(ledPin2,OUTPUT);
    Serial.begin(9600);
}
void loop() 
{
   digitalWrite(trigPin1,LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin1,HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin1,LOW);
   duration1=pulseIn(echoPin1,HIGH);
   distance1=duration1/58.2;
   int i=0;
   digitalWrite(trigPin1,LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin1,HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin1,LOW);
   long duration2=pulseIn(echoPin1,HIGH);
   long distance2=duration2/58.2;
   digitalWrite(trigPin1,LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin1,HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin1,LOW);
   long duration3=pulseIn(echoPin1,HIGH);
   long distance3=duration3/58.2;
   long distance4=(distance1+distance2+distance3)/3;
   Serial.println(distance4);
   if(distance4<=20)
   {
        digitalWrite(motorpin1,LOW);
        digitalWrite(motorpin2,HIGH);
        delay(2000);
        digitalWrite(motorpin1,LOW);
        digitalWrite(motorpin2,LOW);   
   }
   else 
   if (irrecv.decode(&results))
        {
            translateIR();
            irrecv.resume(); // Receive the next value
        }
} 
void translateIR() // takes action based on IR code received describing Car MP3 IR codes 
{
   switch(results.value)
    {
        case 0xFFA25D://stingi faruri  
             digitalWrite(ledPin1,HIGH);
             digitalWrite(ledPin2,HIGH);
             Serial.println(" CH-"); 
        break;
       
        case 0xFFE21D://aprinzi faruri 
             digitalWrite(ledPin1, LOW);
             digitalWrite(ledPin2, LOW);
             Serial.println("CH+"); 
        break;
      
        case 0xFF30CF://MISTI SENZOR  STANGA ?
             for(angle=180;angle>=90;angle=angle-2)
             {
             myservo.write(angle);
             if(angle==180)
             {
                
                digitalWrite(trigPin1,LOW);
                delayMicroseconds(2);
                digitalWrite(trigPin1,HIGH);
                delayMicroseconds(10);
                digitalWrite(trigPin1,LOW);
                duration1=pulseIn(echoPin1,HIGH);
                distance1=duration1/58.2;
                Serial.println(distance1);
                digitalWrite(trigPin1,LOW);
                delayMicroseconds(2);
                digitalWrite(trigPin1,HIGH);
                delayMicroseconds(10);
                digitalWrite(trigPin1,LOW);
                long duration2=pulseIn(echoPin1,HIGH);
                long distance2=duration2/58.2;
                digitalWrite(trigPin1,LOW);
                delayMicroseconds(2);
                digitalWrite(trigPin1,HIGH);
                delayMicroseconds(10);
                digitalWrite(trigPin1,LOW);
                long duration3=pulseIn(echoPin1,HIGH);
                long distance3=duration3/58.2;
                long distance4=(distance1+distance2+distance3)/3;
   
                if(distance4<10)
                {
                  digitalWrite(motorpin1,LOW);
                  digitalWrite(motorpin2,HIGH);
                  digitalWrite(motorpin3,LOW);
                  digitalWrite(motorpin4,HIGH);
                  digitalWrite(motorpin3,HIGH);
                  digitalWrite(motorpin4,LOW);
                  digitalWrite(motorpin3,LOW);
                  digitalWrite(motorpin4,HIGH);
                  delay(2000);
                  digitalWrite(motorpin1,LOW);
                  digitalWrite(motorpin2,LOW);
                  digitalWrite(motorpin3,LOW);
                  digitalWrite(motorpin4,LOW);
                 }
             delay(20); 
             }
              for(angle=90;angle<=180;angle=angle+2)
             {
             myservo.write(angle);
             delay(20); 
             }
             Serial.println("1");
        break;
       
        case 0xFF18E7://mergi in fata
             Serial.println("2");
             digitalWrite(motorpin1,HIGH);
             digitalWrite(motorpin2,LOW); 
        break;
 
        case 0xFFC23D:  
             myservo.write(90);   
             Serial.println(" PLAY/PAUSE     "); 
        break;
        case 0xFF7A85: //MISTI SENZOR DREAPTA ?  
             for(angle=0;angle<=90;angle=angle+2)
             {
             myservo.write(angle);
             if(angle==0)
             {

                digitalWrite(trigPin1,LOW);
                delayMicroseconds(2);
                digitalWrite(trigPin1,HIGH);
                delayMicroseconds(10);
                digitalWrite(trigPin1,LOW);
                duration1=pulseIn(echoPin1,HIGH);
                distance1=duration1/58.2;
                Serial.println(distance1);
                digitalWrite(trigPin1,LOW);
                delayMicroseconds(2);
                digitalWrite(trigPin1,HIGH);
                delayMicroseconds(10);
                digitalWrite(trigPin1,LOW);
                long duration2=pulseIn(echoPin1,HIGH);
                long distance2=duration2/58.2;
                digitalWrite(trigPin1,LOW);
                delayMicroseconds(2);
                digitalWrite(trigPin1,HIGH);
                delayMicroseconds(10);
                digitalWrite(trigPin1,LOW);
                long duration3=pulseIn(echoPin1,HIGH);
                long distance3=duration3/58.2;
                long distance4=(distance1+distance2+distance3)/3;
   
                if(distance4<10)
                {
                 digitalWrite(motorpin1,LOW);
                 digitalWrite(motorpin2,HIGH);
                 digitalWrite(motorpin3,HIGH);
                 digitalWrite(motorpin4,LOW);
                 digitalWrite(motorpin3,LOW);
                 digitalWrite(motorpin4,HIGH);
                 digitalWrite(motorpin3,HIGH);
                 digitalWrite(motorpin4,LOW);
                 delay(2000);
                 digitalWrite(motorpin1,LOW);
                 digitalWrite(motorpin2,LOW);
                 digitalWrite(motorpin3,LOW);
                 digitalWrite(motorpin4,LOW);
                 
                }
             }
             delay(20);  
             }
             for(angle=90;angle>=0;angle=angle-2)
             {
              myservo.write(angle);
              delay(20);  
             }
             Serial.println("3"); 
        break;
        
        case 0xFF10EF: //faci stanga 
             Serial.println("4"); 
             digitalWrite(motorpin3,HIGH);
             digitalWrite(motorpin4,LOW);
             digitalWrite(motorpin3,LOW);
             digitalWrite(motorpin4,HIGH);
             digitalWrite(motorpin3,HIGH);
             digitalWrite(motorpin4,LOW);
        break;
        
        case 0xFF38C7: //stationezi
             Serial.println("5");
             digitalWrite(motorpin1,LOW);
             digitalWrite(motorpin2,LOW); 
             digitalWrite(motorpin3,LOW);
             digitalWrite(motorpin4,LOW); 
        break;
        
        case 0xFF5AA5: //mergi dreapta
             Serial.println("6"); 
             digitalWrite(motorpin3,LOW);
             digitalWrite(motorpin4,HIGH);
             digitalWrite(motorpin3,HIGH);
             digitalWrite(motorpin4,LOW);
             digitalWrite(motorpin3,LOW);
             digitalWrite(motorpin4,HIGH);
        break;
        
        case 0xFF4AB5: //mergi inapoi
             Serial.println("8");
             digitalWrite(motorpin1,LOW);
             digitalWrite(motorpin2,HIGH);
        break;
   }
  delay(20);
    }
}
        

