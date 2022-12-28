#include "../s21_math.h"

long double s21_floor(double x) {
    long double result = 0;
    if (x == s21_INFINITY) {
        result = s21_INFINITY;
    } else if (x == -s21_INFINITY) {
        result = -s21_INFINITY;
    } else if (x != x) {
        result = s21_NAN;
    } else {
        result = x > 0 ? (long int)x : (x == (long int)x) ? (long int)x : (long int)(--x);
    }
    return result;
}
