#include "../s21_math.h"

long double s21_asin(double x) {
  long double result = 0;
  if (x != x || s21_fabs(x) > 1.0) {
    result = s21_NAN;
  } else if (x == 1.0) {
    result = s21_PI / 2;
  } else if (x == -1.0) {
    result = -s21_PI / 2;
  } else {
    for (int n = 0; n < 11; n++) {
      result += (s21_factorial(2 * n) * s21_pow(x, (2 * n) + 1)) /
                (s21_pow(4, n) * (2 * n + 1) * s21_pow(s21_factorial(n), 2));
    }
  }
  return result;
}
