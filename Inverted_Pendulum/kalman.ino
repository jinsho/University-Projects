
double Q_angulo = 0.002;
double Gyro_Q_angulo = 0.003;
double R_angulo = 0.003;

double x_angulo = 0;
double erro_x = 0;
double P00 = 0, P01 = 0, P10 = 0, P11 = 0;
double y, S;
double K, Kpos;

double Kalman(double angulo, double taxa, double tempo){
  double dt = tempo / 1000;
  x_angulo += dt * (taxa - erro_x);
  P00 -= dt * (P10 + P01) + Q_angulo * dt;
  P01 -= dt * P11;
  P10 -= dt * P11;
  P11 += Gyro_Q_angulo * dt;

  y = x_angulo - erro_x;
  S = P00 + R_angulo;
  K = P00 / S;
  Kpos = P10 / S;

  x_angulo += K * y;
  taxa += Kpos * y;
  P00 *= -K;
  P01 *= -K;
  P10 *= -Kpos;
  P11 *= -Kpos;

  return x_angulo;
}

double Q_angulo2 = 0.002;
double Gyro_Q_angulo2 = 0.003;
double R_angulo2 = 0.003;

double x_angulo2 = 0;
double erro_x2 = 0;
double P000 = 0, P001 = 0, P010 = 0, P011 = 0;
double y2, S2;
double K2, Kpos2;

double Kalman2(double angulo2, double taxa2, double tempo2){
  double dt = tempo2 / 1000;
  x_angulo2 += dt * (taxa2 - erro_x2);
  P000 -= dt * (P010 + P001) + Q_angulo2 * dt;
  P001 -= dt * P011;
  P010 -= dt * P011;
  P011 += Gyro_Q_angulo2 * dt;

  y2 = x_angulo2 - erro_x2;
  S2 = P000 + R_angulo2;
  K2 = P000 / S2;
  Kpos2 = P010 / S2;

  x_angulo2 += K2 * y2;
  taxa2 += Kpos2 * y2;
  P000 *= -K2;
  P001 *= -K2;
  P010 *= -Kpos2;
  P011 *= -Kpos2;

  return x_angulo2;
}

double AtualizaKalman(){

  
  double kalman_result = Kalman(calcular_AccelAng(), gyroY/131.0, dt);
  double kalman_result2 = Kalman2(kalman_result, gyroY/131.0, dt);
  return kalman_result2;
}

