#define BRAKE 0
#define CW    1
#define CCW   2

//motor 1
#define M1A 7
#define M1B 6
#define M1P 5
#define M1E 15

//motor 2
#define M2A 13
#define M2B 12
#define M2P 11
#define M2E 0

//motor 3
#define M3A 4
#define M3B 3
#define M3P 2
#define M3E 14

//motor 4
#define M4A 8
#define M4B 9
#define M4P 10
#define M4E 1

int xAxis, yAxis;
int x = 0;
int y = 0;

#define MOTOR_1  0

short motSpeed = 0;  //default motor speed
unsigned short motStatus = BRAKE;
 
void setup()                         
{
  pinMode(M4A, OUTPUT);
  pinMode(M4B, OUTPUT);
  pinMode(M4P, OUTPUT);
  pinMode(M4E, OUTPUT);
  
  Serial.begin(38400);              // Initiates the serial to do the monitoring 
  Serial.println("kontrol");
  

}

void loop() 
{
  xAxis = 510;
  yAxis = 510;

  while (Serial.available() >=2)
  {
  x = Serial.read();
  delay(10);
  y = Serial.read();
  }

  delay(10);

  if (x > 60 & x < 220) 
  {
    xAxis = map(x, 220, 60, 1023, 0); // Convert the smartphone X and Y values to 0 - 1023 range, 
  }

  if (y > 60 & y < 220) 
  {
    yAxis = map(y, 220, 60, 0, 1023);
  }

  if (yAxis > 550)
  {
    maju();
  }

  if (yAxis < 470)
  {
    mundur();
  }

  if (xAxis < 470)
  {
    kiri();
  }

  if (xAxis > 550)
  {
    kanan();
  }
}

//motor 1, motor 3 ccw maju
//motor 2, motor 4 cw maju

void Stop()
{
  Serial.println("Stop");
  motStatus = BRAKE;
  motor1(MOTOR_1, motStatus, 0);
  motor2(MOTOR_1, motStatus, 0);
  motor3(MOTOR_1, motStatus, 0);
  motor4(MOTOR_1, motStatus, 0);
}

void maju()
{
  Serial.println("mazuu maszeehh");
  motSpeed = map(yAxis, 550, 1023, 0, 255);
  motor1(MOTOR_1, motStatus = CCW, motSpeed);
  motor2 (MOTOR_1, motStatus = CW, motSpeed);
  motor3 (MOTOR_1, motStatus = CCW, motSpeed);
  motor4 (MOTOR_1, motStatus = CW, motSpeed);
}

void mundur()
{
  Serial.println("mundor maszehh");
  motSpeed = map(yAxis, 470, 0, 0, 255);
  motor1 (MOTOR_1, motStatus = CW, motSpeed);
  motor2 (MOTOR_1, motStatus = CCW, motSpeed);
  motor3 (MOTOR_1, motStatus = CW, motSpeed);
  motor4 (MOTOR_1, motStatus = CCW, motSpeed);
}

void kanan()
{
  Serial.println("nganan maszehhh");
  motSpeed = map(xAxis, 550, 1023, 0, 255);
  motor1 (MOTOR_1, motStatus = CCW, motSpeed);
  motor2 (MOTOR_1, motStatus = CCW, motSpeed);
  motor3 (MOTOR_1, motStatus = CW, motSpeed);
  motor4 (MOTOR_1, motStatus = CW, motSpeed);
}

void kiri()  
{
  Serial.println("ngiri maszehhh");
  motSpeed = map(xAxis, 470, 0, 0 , 1023);
  motor1 (MOTOR_1, motStatus = CW, motSpeed);
  motor2 (MOTOR_1, motStatus = CW, motSpeed);
  motor3 (MOTOR_1, motStatus = CCW, motSpeed);
  motor4 (MOTOR_1, motStatus = CCW, motSpeed); 
}

void majuKanan()
{
  Serial.println("maju tapi nganan");    
  motor1 (MOTOR_1, motStatus = CCW, motSpeed);
  motor2 (MOTOR_1, motStatus, 0);
  motor3 (MOTOR_1, motStatus, 0);
  motor4 (MOTOR_1, motStatus = CW, motSpeed);
}
void mundurKanan()
{
  Serial.println("mundur tapi nganan");
  motor1(MOTOR_1, motStatus, 0);
  motor2 (MOTOR_1, motStatus = CCW, motSpeed);
  motor3 (MOTOR_1, motStatus = CW, motSpeed);
  motor4 (MOTOR_1, motStatus, 0);
}

void majuKiri()
{
  Serial.println("maju tapi ngiri");
  motor1(MOTOR_1, motStatus, 0);
  motor2 (MOTOR_1, motStatus = CW, motSpeed);
  motor3 (MOTOR_1, motStatus = CCW, motSpeed);
  motor4 (MOTOR_1, motStatus, 0);
}

void mundurKiri()
{
  Serial.println("mundur tapi ngiri");
  motor1 (MOTOR_1, motStatus = CW, motSpeed);
  motor2 (MOTOR_1, motStatus, 0);
  motor3 (MOTOR_1, motStatus, 0);
  motor4 (MOTOR_1, motStatus = CCW, motSpeed);
}
void increaseSpeed()
{
  motSpeed = motSpeed + 20;
  if(motSpeed > 255)
  {
    motSpeed = 255;  
  }
  
  Serial.print("Speed +: ");
  Serial.println(motSpeed);

  motor1(MOTOR_1, motStatus, motSpeed);
}

void decreaseSpeed()
{
  motSpeed = motSpeed - 20;
  if(motSpeed < 0)
  {
    motSpeed = 0;  
  }
  
  Serial.print("Speed -: ");
  Serial.println(motSpeed);

  motor1(MOTOR_1, motStatus, motSpeed);
}

void motor1(uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if(motor == MOTOR_1)
  {
    if(direct == CW)
    {
      digitalWrite(M1A, LOW); 
      digitalWrite(M1B, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(M1A, HIGH);
      digitalWrite(M1B, LOW);      
    }
    else
    {
      digitalWrite(M1A, LOW);
      digitalWrite(M1B, LOW);            
    }
    
    analogWrite(M1P, pwm); 
  }
} 
  void motor2 (uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if(motor == MOTOR_1)
  {
    if(direct == CW)
    {
      digitalWrite(M2A, LOW); 
      digitalWrite(M2B, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(M2A, HIGH);
      digitalWrite(M2B, LOW);      
    }
    else
    {
      digitalWrite(M2A, LOW);
      digitalWrite(M2B, LOW);            
    }
    
    analogWrite(M2P, pwm); 
  }
}

void motor3 (uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if(motor == MOTOR_1)
  {
    if(direct == CW)
    {
      digitalWrite(M3A, LOW); 
      digitalWrite(M3B, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(M3A, HIGH);
      digitalWrite(M3B, LOW);      
    }
    else
    {
      digitalWrite(M3A, LOW);
      digitalWrite(M3B, LOW);            
    }
    analogWrite(M3P, pwm); 
  }
}

  void motor4 (uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if(motor == MOTOR_1)
  {
    if(direct == CW)
    {
      digitalWrite(M4A, LOW); 
      digitalWrite(M4B, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(M4A, HIGH);
      digitalWrite(M4B, LOW);      
    }
    else
    {
      digitalWrite(M4A, LOW);
      digitalWrite(M4B, LOW);            
    }
    
    analogWrite(M4P, pwm);
  }
}
