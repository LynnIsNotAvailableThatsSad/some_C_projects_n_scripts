#include "../s21_math.h"

long double s21_pow(double base, double exp) {
  long double result = 1;
  if (base != base || exp != exp) {
    result = s21_NAN;
  } else if (s21_fabs((int)exp - exp) > 0.000001) {
    result = s21_exp(exp * s21_log(base));
  } else {
    if (exp < 0.0) {
      exp = -exp;
      result = 1 / s21_pow(base, exp);
    } else {
      for (int i = 0; i < (int)exp; i++) {
        result *= base;
      }
    }
  }
  return result;
}
