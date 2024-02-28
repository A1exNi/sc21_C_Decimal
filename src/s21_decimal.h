#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#define S21_BIT_MINUS 0b10000000000000000000000000000000
#define IS_SET(X, POS) ((X >> POS) & 1U)
#define ADD_BIT(X, POS) ((X) |= (1U << (POS)))
#define SET_BIT(X, BIT, POS) (X |= (BIT << POS))
#define ZERO_BIT(X, POS) (X &= ~(1UL << POS))

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int bits[4];
} s21_decimal;

void s21_swap_mantiss(s21_decimal *mantiss_1, s21_decimal *mantiss_2,
                      char operation);
int s21_degree_for_add(s21_decimal value_1, s21_decimal value_2);
int s21_sign_for_add(s21_decimal value_1, s21_decimal value_2, char *operation);
int s21_overflow_for_add(int sign_result, int residual, int need_round,
                         s21_decimal *result);
unsigned calc_bit(int a, int b, int *residual, char operation);
int s21_cor_result_add(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *result, int count_mul, char operation,
                       int *residual);
int calc_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
             char operation);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_decimal_pow_ten(s21_decimal *a, int degree);
int s21_cor_mantiss(s21_decimal *mantiss_1, s21_decimal *mantiss_2,
                    int degree_1, int degree_2, int *residual, int *count_mul,
                    char operation);
int s21_def_mantiss(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *mantiss_1, s21_decimal *mantiss_2,
                    char operation, int *count_mul);
int s21_shifting_bits(s21_decimal *a, int i);
int s21_calc_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *sum);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_div_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                s21_decimal *residual);
void s21_not_int_div(s21_decimal value, s21_decimal *result,
                     s21_decimal *residual, int *degree);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_bit_greater(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);

int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_double(s21_decimal src, long double *dst);

int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

void s21_decimal_nullify(s21_decimal *value);
int s21_def_sign(s21_decimal a);
int s21_is_zero(s21_decimal a);
int s21_def_degree(int bits3);
int s21_set_degree(int degree);
s21_decimal s21_abs(s21_decimal a);
void s21_set_bit(s21_decimal *a, int i);
int s21_bit_eq_one(s21_decimal a, int i);

void set_bit_0(s21_decimal *n, int pos);
void set_bit_1(s21_decimal *n, int pos);
int get_exponent(s21_decimal decimal);
int get_bin_exp(float val);
int get_float_bit(float val, int i);

#endif  // S21_DECIMAL_H
