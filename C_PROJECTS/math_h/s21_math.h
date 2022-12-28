#ifndef SRC_S21_MATH_H_  // SRC_S21_MATH_H_
#define SRC_S21_MATH_H_  // SRC_S21_MATH_H_

#include <stdio.h>

#define s21_NAN 0.0 / 0.0
#define s21_INFINITY 1.0 / 0.0
#define EPS 1E-10
#define s21_PI 3.14159265358979323846
#define s21_LN2 0.69314718056


//! Прототипы из задания

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_exp2(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

//! Дополнительные прототипы

unsigned long long s21_factorial(int x);
long double s21_taylor(double x);

#endif  // SRC_S21_MATH_H_

