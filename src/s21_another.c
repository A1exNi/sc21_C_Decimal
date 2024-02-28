#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  s21_decimal_nullify(result);
  long double fl_to_round = 0;
  long double difference = 0;
  s21_from_decimal_to_double(value, &fl_to_round);
  fl_to_round = round(fl_to_round);
  result->bits[3] = s21_set_degree(0);
  if (fl_to_round < 0.0) {
    set_bit_1(result, 127);
    fl_to_round *= -1;
  }
  for (int i = 0; fl_to_round >= 1 && i < 96; i++) {
    fl_to_round = floor(fl_to_round) / 2;
    difference = fl_to_round - floor(fl_to_round);
    difference > 0.0 ? set_bit_1(result, i) : set_bit_0(result, i);
  }
  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_decimal_nullify(result);
  int degree_value = s21_def_degree(value.bits[3]);
  int sign_value = s21_def_sign(value);
  s21_decimal residual;
  s21_decimal_nullify(&residual);
  s21_decimal_pow_ten(&residual, degree_value);
  s21_div_mod(value, residual, result, &residual);
  if (sign_value == -1) result->bits[3] |= S21_BIT_MINUS;
  return 0;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal one;
  s21_from_int_to_decimal(1, &one);
  s21_decimal_nullify(result);
  if (!s21_truncate(value, result) && s21_def_sign(value) == -1 &&
      !s21_is_equal(*result, value))
    s21_sub(*result, one, result);
  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_decimal_nullify(result);
  int degree_value = s21_def_degree(value.bits[3]);
  result->bits[3] = s21_set_degree(degree_value);
  if (s21_def_sign(value) == 1) result->bits[3] |= S21_BIT_MINUS;
  for (int i = 0; i < 3; i++) result->bits[i] = value.bits[i];
  return 0;
}
