#include "../s21_math.h"

unsigned long long s21_factorial(int n) {
  unsigned long long result;
  if (n < 1) {
    result = 1;
  } else {
    result = n * s21_factorial(n - 1);
  }
  return result;
}
