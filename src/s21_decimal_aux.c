#include "s21_decimal.h"

void set_bit_0(s21_decimal *n, int pos) {
  ZERO_BIT(n->bits[pos / 32], pos % 32);
}

void set_bit_1(s21_decimal *n, int pos) {
  ADD_BIT(n->bits[pos / 32], pos % 32);
}

int get_exponent(s21_decimal decimal) {
  int exponent = 0;
  for (int i = 16, j = 0; i <= 23; i++, j++) {
    if (IS_SET(decimal.bits[3], i)) ADD_BIT(exponent, j);
  }
  return exponent;
}

int get_bin_exp(float val) {
  unsigned int bit = *((unsigned int *)&val);
  return (((bit & 0x7f800000) >> 23) - 127);
}

int get_float_bit(float val, int i) {
  int mask = 1 << i;  // 10..0..0
  return !!(*((unsigned int *)&val) & mask);
}
