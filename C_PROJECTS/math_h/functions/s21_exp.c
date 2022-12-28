#include "../s21_math.h"

long double s21_exp(double x) {
  long double expy = 1;
  long double x_stage = x;
  for (int n = 1; x_stage > 0.000001; n++) {
    if (n >= 2) {
      x_stage = x_stage * x;
    }
    x_stage = (x_stage) / s21_factorial(n);
    expy += x_stage;
  }
  return expy;
}
