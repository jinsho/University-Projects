#include <Wire.h>
#define runEvery(t) for (static long _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))

double Angulo;
double Saida_PID;
double KalAng;
double looptime;
double timer;

void setup(){

  #if ARDUINO >= 157
  Wire.setClock(400000UL); // Set I2C frequency to 400kHz
  #else
  TWBR = ((F_CPU / 400000UL) - 16) / 2; // Set I2C frequency to 400kHz
  #endif

  Serial.begin(9600);
  inicializar_MPU();
  inicializar_motores();
  setSetPoint(0.0);
  Bias();

  timer = millis();
  
}

void loop(){

  runEvery(75){
  
    LerGyro();
    LerAccel();
    looptime = (double)(millis() - timer) / 1000;
    timer = millis();
    
   Angulo = 0.98 * (Calcular_GyroAng()) + 0.02 * calcular_AccelAng();

   //Serial.print(calcular_GyroAng());
   Serial.print(Angulo);
   //Serial.print(" ");
   //Serial.print(Angulo);
   Serial.print(" ");

   Saida_PID = calcular_PID(Angulo);
   Serial.println(Saida_PID);
   Saida_motores(Saida_PID);

  }
   
  
}

