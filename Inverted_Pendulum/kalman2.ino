/*
float Q_angulo = 0.001;
float Q_bias = 0.003;
float R_medicao = 0.03;

float* pQ_angulo = &Q_angulo;
float* pQ_bias = &Q_bias;
float* pR_medicao = &R_medicao;



float angulo = 0.0;
float bias = 0.0;
float taxa = 0.0;

float* pangulo = &angulo;
float* pbias = &bias;
float* ptaxa = &taxa;


float P00 = 0.0;
float P01 = 0.0;
float P10 = 0.0;
float P11 = 0.0;



float getAngulo(float novoAngulo, float novaTaxa, float dt){

  taxa = novaTaxa - bias;
  angulo += dt * taxa;


  P00 += dt * (dt*P11 - P01 - P10 + Q_angulo);
  P01 -= dt * P11;
  P10 -= dt * P11;
  P11 += Q_bias * dt;

  float S = P00 + R_medicao;

  float K[2];
  K[0] = P00 / S;
  K[1] = P10 / S;

  float y = novoAngulo - angulo;

  angulo += K[0] * y;
  bias += K[1] * y;

  float P00_temp = P00;
  float P01_temp = P01;

  P00 -= K[0] * P00_temp;
  P01 -= K[0] * P01_temp;
  P10 -= K[1] * P00_temp;
  P11 -= K[1] * P01_temp;

  return angulo;
}

void ajustarAngulo(float val){
  *pangulo = val;
}

float getTaxa(){
  return *ptaxa;
}

void ajustarQangulo(float val){
  *pQ_angulo = val;
}

void ajustarQbias(float val){
  *pQ_bias = val;
}

void ajustarRmedicao(float val){
  *pR_medicao = val;
}

float getQangulo(){
  return *pQ_angulo;
}

float getQbias(){
  return *pQ_bias;
}

float getQmedicao(){
  return *pR_medicao;
}

*/

