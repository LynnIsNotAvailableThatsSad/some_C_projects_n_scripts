#include "../s21_math.h"

long double s21_cos(double x) {
  int sign = 1;
  x = s21_fmod(x, 2 * s21_PI);
  if (x > s21_PI) {
    x -= s21_PI;
    sign = -1;
  }
  long double result = 0;
  for (int i = 0; i < 9; i++) {
    result += s21_pow(-1, i) * (s21_pow(x, 2 * i)/s21_factorial(2 * i));
  }
  return sign * result;
}
