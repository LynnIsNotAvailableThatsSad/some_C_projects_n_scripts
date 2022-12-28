#include "../s21_math.h"

long double s21_log(double x) {
    long double res = 0.0;
    if (x != x) {
        res = s21_NAN;
    } else if (x < 0) {
        res = -s21_NAN;
    } else if (x == 0.0) {
        res = -s21_INFINITY;
    } else if (x == s21_INFINITY) {
        res = s21_INFINITY;
    } else if (x == -s21_INFINITY) {
        res = s21_NAN;
    } else if (x == 2) {
      res = s21_LN2;
    } else if (x > 2) {
        int n = 0;
        while (x > 1) {
            x /= 10;
            n++;
        }
        res = n * 2.30258509299 + s21_taylor(x - 1);
    } else {
        x = x - 1;
        res = s21_taylor(x);
    }
    return res;
}

long double s21_taylor(double x) {
    long double powx = 1, summ = 0, add;
    int sig = 1, n = 1;
    add = powx = x;
    while (s21_fabs(add) > 0) {
        summ = summ + add;
        sig = -sig;
        powx = powx * x;
        n++;
        add = sig * powx / n;
    }
    return summ;
}
