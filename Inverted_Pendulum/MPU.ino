
#define MPU 0x68    //define MPU como sinonimo de 0x68

//valores brutos lidos pelo acelerometro
double accX, accY, accZ;
//angulo calculado atraves das aceleraçoes
double accAng;
//valores brutos lidos pelo giroscopio
double gyroX, gyroY, gyroZ;
//angulo calculado atraves dos giros
double gyroAng;
// ponto de repouso do giroscopio
double gyroBias;
double accBiasX, accBiasY, accBiasZ;
double ultimo_gyroAng;

long temp_anterior=0;

long dt;

//Bias eh o valor do ponto de repouso do giroscopio
//calcula o valor lido pelo giroscopio quando em repouso
//atraves da media de varias amostras
void Bias(){
  int i;
  for(i=0;i<100;i++){
    LerGyro();
    LerAccel();
    gyroBias += gyroY;
    accBiasX += accX; 
    accBiasY += accY; 
    accBiasZ += accZ; 
  }
  gyroBias = gyroBias/100;
  accBiasX = accBiasX/100;
  accBiasY = accBiasY/100;
  accBiasZ = accBiasZ/100;
  
}


void inicializar_MPU(){

  //inicializa a biblioteca Wire.h
  Wire.begin();
  //inicia transmissão para o MPU
  Wire.beginTransmission(MPU);
  //reseta o MPU
  Wire.write(0x6B);
  Wire.write(0);
  //finaliza trasmissão e libera o dispositivo
  Wire.endTransmission();
  
}

void LerAccel(){

  //inicia transmissão para o MPU
  Wire.beginTransmission(MPU);
  //indica o endereço onde sera realizada a leitura
  Wire.write(0x3B);
  //finaliza transmissão
  Wire.endTransmission();
  //requisita 6 dados do MPU e libera o dispositivo
  Wire.requestFrom(MPU,6,true);

  accX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  accY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  accZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  

}


void LerGyro(){
  //inicia transmissão para o MPU
  Wire.beginTransmission(MPU);
  //indica o endereço onde sera realizada a leitura
  Wire.write(0x43);
  //finaliza transmissão
  Wire.endTransmission();
  //requisita 6 dados do MPU e libera o dispositivo
  Wire.requestFrom(MPU,6,true);

  gyroX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  gyroY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  gyroZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  
}


double calcular_AccelAng(){

  LerAccel();

  //arco-tangente das aceleraçoes em cada eixo
  accAng = (atan(accX/(sqrt((accY*accY)+(accZ*accZ)))))*RAD_TO_DEG;
  //accAng = 0.98 * gyroAng + 0.02 * accAng;

  return accAng;

}

double calcular_GyroAng(){

  
  LerGyro();

  dt = millis() - temp_anterior;   // calcula o intervalo de tempo da leitura em milisegundos
  temp_anterior = millis();


  gyroAng = ((gyroY-gyroBias)/131.0) * dt/1000 + ultimo_gyroAng;

  /************************************************
   * gyro/131 - converte rad/seg para graus/seg
   * dt/1000 - tempo de leitura transformado em seg
   ***********************************************/

  ultimo_gyroAng = gyroAng; 
  
  temp_anterior = millis();

  return gyroAng;
  
}



