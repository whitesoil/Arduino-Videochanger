
int s0=6,s1=5,s2=4,s3=3;
int out = 2;
int flag = 0;
int echoPin = 12;
int trigPin = 13;
byte counter = 0;
byte countR = 0,countG=0,countB = 0;

//for synchronization
int mutex = 0;
int semop = 0;

void setup(){
  Serial.begin(115200);
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
}

void TCS(){

  flag=0;
  digitalWrite(s1,HIGH);
  digitalWrite(s0,HIGH);  
  digitalWrite(s2,LOW);  
  digitalWrite(s3,LOW);  
  attachInterrupt(0, ISR_INTO, CHANGE);  
  timer0_init();
}

void ISR_INTO(){
  counter++;
}

void timer0_init(void){
  TCCR2A = 0x00;
  TCCR2B = 0x07;
  TCNT2 = 100;
  TIMSK2 = 0x01;
}

int i =0;

ISR(TIMER2_OVF_vect){
  TCNT2=111;
  flag++;
  if(flag==1){
    
    countR=counter;
    digitalWrite(s2,HIGH);
    digitalWrite(s3,HIGH);
    }

  else if(flag==2){
    
    countG=counter;
    digitalWrite(s2,LOW);
    digitalWrite(s3,HIGH);
    }

  else if(flag==3){
    
    countB=counter;    
    digitalWrite(s2,LOW);
    digitalWrite(s3,LOW);
  } 

   /*
    * RGB 값의 범위를 아래 주석을 지운 후 측정을 통해 범위를 정해주어야 합니다
    */
  else if(flag==4){
//    Serial.println(countR,DEC);
//    Serial.println(countG,DEC);
//    Serial.println(countB,DEC);
//    Serial.println("-------------");
    if(100 < countR && countR < 200 && 100 < countG && countG < 200 && 100 < countB && countB < 200 && mutex == 0 && semop == 0){
      //Red
      
      Serial.write(101);
      mutex = 1;
    }else if(100 < countR && countR < 200 && 100 < countG && countG < 200 && 100 < countB && countB < 200 && mutex == 1){
      //Green
      
      Serial.write(121);
      mutex = 2;
    }else if(100 < countR && countR < 200 && 100 < countG && countG < 200 && 100 < countB && countB < 200 && mutex == 2){
      //blue
      
      Serial.write(151);
      mutex = 0;
    }else{
     
    }
    flag=0;
   }
    
  counter=0;
}

void loop()
{
  float duration, distance;
  TCS();
  // 초음파 거리 측정센서
  while(1){
    digitalWrite(trigPin,HIGH);
    delay(10);
    digitalWrite(trigPin,LOW);

    duration = pulseIn(echoPin,HIGH);
    distance = ((float)(340 * duration)/10000)/2;
    if(distance < 30 && mutex == 0){
      Serial.write(241);
      semop = 0;
    }else if( 500 < distance && mutex == 0){
      Serial.write(251);
      semop = 1;
    }
    delay(100);
    };
}
