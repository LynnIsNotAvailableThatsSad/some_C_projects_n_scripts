#include "../s21_math.h"

long double s21_fmod(double x, double y) {
    long double result = 0;
    if (y == s21_INFINITY || y == -s21_INFINITY) {
        result = x;
    } else if (y == 0 || y != y || x != x || x == s21_INFINITY || x == -s21_INFINITY) {
        result = s21_NAN;
    } else {
        result = x - (int)(x/y) * y;
    }
    return result;
}
