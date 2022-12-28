#include "../s21_math.h"

long double s21_atan(double x) {
  long double result = 0;
  int sign = 1;
  if (x < 0.0) {
    sign = -1;
    x = -x;
  }
  if (x > 1.0) {
    result = s21_PI / 2 - s21_atan(1.0 / x);
  } else if (s21_fabs(x - 1.0) < 0.000001) {
    result = s21_PI / 4;
  } else {
    for (int n = 0; n < 20; n++) {
      result += (s21_pow(-1, n) * s21_pow(x, (2 * n) + 1)) / (2 * n + 1);
    }
  }
  return sign * result;
}
