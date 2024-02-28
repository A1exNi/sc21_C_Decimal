#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int answer = 0;
  int degree_src = s21_def_degree(src.bits[3]);
  if (!dst) {
    answer = 1;
  } else {
    if (src.bits[2] != 0 || src.bits[1] != 0) {
      if (degree_src == 0) {
        answer = 1;
      } else {
        s21_truncate(src, &src);
        if (src.bits[2] != 0 || src.bits[1] != 0) {
          answer = 1;
        } else {
          *dst = src.bits[0];
        }
      }
    } else {
      if (degree_src == 0) {
        *dst = src.bits[0];
      } else {
        s21_truncate(src, &src);
        *dst = src.bits[0];
      }
    }
    if (s21_def_sign(src) == -1) {
      *dst = -(*dst);
    }
  }
  return answer;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int normal = 0;
  if (dst == NULL) {
    normal = 1;
  } else {
    s21_decimal_nullify(dst);
    if (src != INFINITY && src != -INFINITY) {
      if (src < 0) {
        dst->bits[3] |= S21_BIT_MINUS;
        src = -src;
      }
      dst->bits[0] = src;
    } else {
      normal = 1;
    }
  }
  return normal;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int normal = 0;
  if (dst == NULL) {
    normal = 1;
  } else {
    s21_decimal_nullify(dst);
    if (src == src && src != INFINITY && src != -INFINITY) {
      if (src == 0.F) {
        normal = 0;
      } else {
        int sign = 0;
        if (src < 0.F) {
          sign = 1;
          src *= -1;
        }
        long double tmp = fabs(src);
        int exp = get_bin_exp(src);
        float fl_buf = 0.;
        int scale = 0;
        if (exp < 95) {
          while (scale < 28 && ((int)tmp / 2097152) == 0) {
            tmp *= 10;
            scale++;
          }
        }
        tmp = round(tmp);
        if (scale <= 28 && (exp >= -94 && exp < 96)) {
          tmp = (float)tmp;
          while (fmod(tmp, 10) == 0 && scale > 0) {
            tmp /= 10;
            scale--;
          }
        }
        fl_buf = tmp;
        exp = get_bin_exp(fl_buf);
        s21_set_bit(dst, exp);
        for (int i = 23; i >= 0; i--) {
          if (get_float_bit(fl_buf, i)) s21_set_bit(dst, exp);
          exp--;
        }
        if (exp < -94 || scale > 28) {
          normal = 1;
          s21_decimal_nullify(dst);
        } else {
          dst->bits[3] = s21_set_degree(scale);
          if (sign) dst->bits[3] |= S21_BIT_MINUS;
        }
      }
    } else {
      normal = 1;
    }
  }
  return normal;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int answer = 0;
  if (!dst) {
    answer = 1;
  } else {
    int sign = s21_def_sign(src);
    int exponent = get_exponent(src);
    long double tmp = 0;
    for (int i = 0; i < 96; i++) tmp += pow(2, i) * s21_bit_eq_one(src, i);
    while (exponent--) tmp /= 10.0;
    if (sign == -1) tmp *= -1.0;
    *dst = tmp;
  }
  return answer;
}

int s21_from_decimal_to_double(s21_decimal src, long double *dst) {
  long double temp = 0;
  temp = (double)*dst;
  for (int i = 0; i < 96; i++) {
    temp += s21_bit_eq_one(src, i) * pow(2, i);
  }
  temp = temp * pow(10, -s21_def_degree(src.bits[3]));
  if (s21_bit_eq_one(src, 127)) temp = -1 * temp;
  *dst = temp;
  return 0;
}
