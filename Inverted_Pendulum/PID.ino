double Kp = 500.0;       //constante de ganho proporcional
double Ki = 0.1;       //constante de ganho integral
double Kd = 0.0;       //constante de ganho derivativo

double P;        //termo proporcional
double I = 0;    //termo integral
double D;        //termo derivativo

double PID;      //saída
double erro;  
double setPoint; //Angulo ideal

double ultima_entrada = 0; 

int outMin = -100;     //saida PWM mínima
int outMax = 100;      //saida PWM máxima

double calcular_PID(double entrada){

  //calculo do erro
  erro = setPoint - entrada;

  //calculo do termo Proporcional
  P = Kp * erro;
  //calculo do termo Integral
  I = I + (Ki * erro);
  //calculo do termo Derivativo
  D = Kd * (entrada - ultima_entrada)/looptime;
  
  //mantém o valor do termo integral entre -200 e 200;
  if(I >= outMax) I = outMax;
  if(I <= outMin) I = outMin;

  //calculo da saída
  PID = P + I + D;

  //mantém o valor da saída entre -200 e 200;
  if (PID >= outMax) PID = outMax;
  if (PID <= outMin) PID = outMin;

  return PID;
  
}


void setSetPoint(double val){
  setPoint = val;
}


double getSetPoint(){
  return setPoint;
}

