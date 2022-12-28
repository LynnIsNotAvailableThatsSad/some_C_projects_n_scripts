#include "../s21_math.h"

long double s21_ceil(double x) {
  long double result = 0;
  if (x == s21_INFINITY) {
    result = s21_INFINITY;
  } else if (x == -s21_INFINITY) {
    result = -s21_INFINITY;
  } else if (x != x) {
    result = s21_NAN;
  } else {
    if (s21_fabs((int)x - x) < 0.00000001) {
      result = x;
    } else {
      result = s21_floor(x) + 1;
    }
  }
  return result;
}
