#include "s21_decimal.h"

// зануление
void s21_decimal_nullify(s21_decimal *value) {
  for (int i = 0; i < 4; i++) value->bits[i] = 0;
}

// определение знака
int s21_def_sign(s21_decimal a) {
  int result = 1;
  if (!s21_is_zero(a)) {
    if (a.bits[3] & S21_BIT_MINUS) result = -1;
  }
  return result;
}

// определение нулевого числа
int s21_is_zero(s21_decimal a) {
  int result = 0;
  if (a.bits[0] == 0 && a.bits[1] == 0 && a.bits[2] == 0) result = 1;
  return result;
}

// определяем степень
int s21_def_degree(int bits3) {
  // зануляем биты с 31 по 24
  bits3 = bits3 & 0xFFFFFF;
  // смещение битов с 16 на 0 позицию
  bits3 = bits3 >> 16;
  return bits3;
}

// устанавливаем степень
int s21_set_degree(int degree) {
  degree = degree << 16;
  return degree;
}

// абсолют числа
s21_decimal s21_abs(s21_decimal a) {
  if (a.bits[3] & (S21_BIT_MINUS)) a.bits[3] ^= (1 << 31);
  return a;
}

// используется в div_mod
void s21_set_bit(s21_decimal *a, int i) { a->bits[i / 32] |= 1 << (i % 32); }

// 1 - если итый бит равен 1. Используется в умножении.
int s21_bit_eq_one(s21_decimal a, int i) {
  return (a.bits[i / 32] >> (i % 32)) & 1;
}

// меняем местами мантисcы в add/sub если - и 2 больше 1
// мантиссы приходят уже изменные
void s21_swap_mantiss(s21_decimal *mantiss_1, s21_decimal *mantiss_2,
                      char operation) {
  if (s21_bit_greater(*mantiss_2, *mantiss_1) && operation == '-') {
    s21_decimal buf;
    buf = *mantiss_1;
    *mantiss_1 = *mantiss_2;
    *mantiss_2 = buf;
  }
}

// определение степени в add/sub
int s21_degree_for_add(s21_decimal value_1, s21_decimal value_2) {
  int answer = 0;
  int degree_1 = value_1.bits[3] & 0xFFFFFF;
  // смещение битов с 16 на 0 позицию
  degree_1 = degree_1 >> 16;
  int degree_2 = value_2.bits[3] & 0xFFFFFF;
  // смещение битов с 16 на 0 позицию
  degree_2 = degree_2 >> 16;
  answer = degree_1;
  if (degree_2 > degree_1) answer = degree_2;
  return answer;
}

// определение знака для add и установка оператора
int s21_sign_for_add(s21_decimal value_1, s21_decimal value_2,
                     char *operation) {
  int sign_result = 1;
  int sign_1 = s21_def_sign(value_1);
  int sign_2 = s21_def_sign(value_2);
  if (*operation == '+') {
    value_1 = s21_abs(value_1);
    value_2 = s21_abs(value_2);
    if ((sign_1 == -1 && s21_is_greater(value_1, value_2)) ||
        (sign_2 == -1 && s21_is_greater(value_2, value_1)) ||
        (sign_1 == -1 && sign_2 == -1))
      sign_result = -1;
  }
  if (*operation == '-') {
    if (s21_is_greater(value_2, value_1)) sign_result = -1;
  }
  if (sign_1 != sign_2) {
    if (*operation == '+') {
      *operation = '-';
    } else {
      *operation = '+';
    }
  }
  return sign_result;
}

// определяем переполнение и окрубление в add
int s21_overflow_for_add(int sign_result, int residual, int need_round,
                         s21_decimal *result) {
  int answer = 0;
  if (residual) {
    answer = 1;
    if (sign_result == -1) answer = 2;
  }
  if (need_round) {
    s21_decimal one;
    s21_from_int_to_decimal(1, &one);
    if (result->bits[0] & 1) s21_sub(*result, one, result);
  }
  return answer;
}

// расчет битов в add
unsigned calc_bit(int a, int b, int *residual, char operation) {
  unsigned result = 0;
  long unsigned abuf = (unsigned)a;
  long unsigned bbuf = (unsigned)b;
  long unsigned rbuf = 0;
  if (operation == '+') rbuf = abuf + bbuf + *residual;
  if (operation == '-') rbuf = abuf - bbuf + *residual;
  if (rbuf <= UINT_MAX) {
    result = rbuf;
    *residual = 0;
  } else {
    result |= rbuf;
    rbuf = rbuf >> 32;
    *residual = rbuf;
  }
  return result;
}

// 0 - ошибка 1 - успех
// возведение числа 10 в степень
int s21_decimal_pow_ten(s21_decimal *a, int degree) {
  int result = 1;
  s21_decimal_nullify(a);
  s21_decimal ten;
  s21_from_int_to_decimal(10, &ten);
  if (degree > 28) {
    result = 0;
  } else {
    a->bits[0] = 10;
    for (int i = 1; i < degree; i++) {
      s21_mul(*a, ten, a);
    }
    if (degree == 0) a->bits[0] = 1;
  }
  return result;
}

// уменьшить
// коррекстируем мантиссы если степень не равны нулю
int s21_cor_mantiss(s21_decimal *mantiss_1, s21_decimal *mantiss_2,
                    int degree_1, int degree_2, int *residual, int *count_mul,
                    char operation) {
  int degree_result = 0;
  s21_decimal ten;
  s21_from_int_to_decimal(10, &ten);
  mantiss_1->bits[3] = 0;
  s21_decimal buf = *mantiss_1;
  // умножаем на 10 для выравнивания, фиксируем количество умножений
  for (int i = 0; i < degree_2 - degree_1 && !(*residual); i++) {
    *residual = s21_mul(buf, ten, &buf);
    if (!(*residual)) {
      *mantiss_1 = buf;
      // определяем сколько раз можно умножить на 10
      (*count_mul)++;
    }
  }
  mantiss_2->bits[3] = s21_set_degree(degree_2 - degree_1);
  // если произошло переполнение нужно корректировать второе число
  if (*residual) {
    for (int i = 0; i < *count_mul; i++) s21_mul(*mantiss_2, ten, mantiss_2);
    if (*count_mul == 0) *count_mul = degree_1;
    s21_decimal one;
    s21_from_int_to_decimal(1, &one);
    if (!s21_is_zero(*mantiss_2)) {
      s21_truncate(*mantiss_2, mantiss_2);
      if (operation == '+') s21_add(*mantiss_2, one, mantiss_2);
      if (operation == '-') {
        if ((mantiss_2->bits[0] & 1 && mantiss_1->bits[0] & 1) ||
            (!(mantiss_2->bits[0] & 1) && !(mantiss_1->bits[0] & 1))) {
          s21_sub(*mantiss_2, one, mantiss_2);
        } else {
          s21_add(*mantiss_2, one, mantiss_2);
        }
      }
    }
    degree_result = -2;
    *residual = 0;
  } else {
    degree_result = degree_2;
  }
  return degree_result;
}

// 0 - успех; -1 - произошло переполнение; -2 - нужно округление
int s21_def_mantiss(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *mantiss_1, s21_decimal *mantiss_2,
                    char operation, int *count_mul) {
  int degree_result = 0;
  int residual = 0;
  // определяем степень
  int degree_1 = s21_def_degree(value_1.bits[3]);
  int degree_2 = s21_def_degree(value_2.bits[3]);
  *mantiss_1 = value_1;
  *mantiss_2 = value_2;
  if (degree_1 == degree_2) degree_result = degree_1;
  if (degree_2 > degree_1) {
    degree_result = s21_cor_mantiss(mantiss_1, mantiss_2, degree_1, degree_2,
                                    &residual, count_mul, operation);
  }
  if (degree_1 > degree_2) {
    degree_result = s21_cor_mantiss(mantiss_2, mantiss_1, degree_2, degree_1,
                                    &residual, count_mul, operation);
  }
  if (residual) degree_result = -1;
  return degree_result;
}

int s21_cor_result_add(s21_decimal value_1, s21_decimal value_2,
                       s21_decimal *result, int count_mul, char operation,
                       int *residual) {
  int degree_result = 0;
  s21_decimal mantiss_1, mantiss_2, res_1, res_2;
  s21_decimal_nullify(&mantiss_1);
  s21_decimal_nullify(&mantiss_2);
  s21_decimal_nullify(&res_1);
  s21_decimal_nullify(&res_2);
  *residual = 0;
  s21_truncate(value_1, &mantiss_1);
  s21_truncate(value_2, &mantiss_2);
  s21_sub(value_1, mantiss_1, &res_1);
  s21_sub(value_2, mantiss_2, &res_2);
  res_1 = s21_abs(res_1);
  res_2 = s21_abs(res_2);
  for (int i = 0; i < 3; i++)
    result->bits[i] =
        calc_bit(mantiss_1.bits[i], mantiss_2.bits[i], residual, operation);
  if (!(*residual)) {
    if (!s21_is_zero(res_2) || !s21_is_zero(res_1)) {
      s21_decimal res_1_2;
      s21_decimal_nullify(&res_1_2);
      if (operation == '+') s21_add(res_1, res_2, &res_1_2);
      if (operation == '-') s21_sub(res_1, res_2, &res_1_2);
      s21_decimal ten, trank_res_1_2, buf_result, buf;
      s21_decimal_nullify(&trank_res_1_2);
      buf_result = *result;
      s21_decimal_nullify(&buf);
      s21_from_int_to_decimal(10, &ten);
      int overflow_residual, overflow_result;
      for (int i = 0; i < count_mul && !(*residual); i++) {
        overflow_residual = s21_mul(res_1_2, ten, &res_1_2);
        overflow_result = s21_mul(buf_result, ten, &buf_result);
        if (overflow_result || overflow_residual) *residual = 1;
        s21_truncate(res_1_2, &trank_res_1_2);
        if (!(*residual)) *residual = s21_add(buf_result, trank_res_1_2, &buf);
        if (!(*residual)) {
          *result = buf;
          degree_result++;
        }
      }
      *residual = 0;
      s21_decimal one;
      s21_from_int_to_decimal(1, &one);
      if (operation == '+' && result->bits[0] & 1)
        *residual = s21_add(*result, one, result);
    }
  }
  return degree_result;
}

int calc_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
             char operation) {
  int answer = 0;
  int need_round = 0;
  // определяем степень
  int degree_result = s21_degree_for_add(value_1, value_2);
  // определяем знак
  int sign_result = s21_sign_for_add(value_1, value_2, &operation);
  // определяем мантиссу
  // сколько раз моно умножить на 10
  int count_mul = 0;
  s21_decimal mantiss_1, mantiss_2, res_1, res_2;
  s21_decimal_nullify(&mantiss_1);
  s21_decimal_nullify(&mantiss_2);
  s21_decimal_nullify(&res_1);
  s21_decimal_nullify(&res_2);
  degree_result = s21_def_mantiss(value_1, value_2, &mantiss_1, &mantiss_2,
                                  operation, &count_mul);
  // меняем местами если - и 2 больше 1
  s21_swap_mantiss(&mantiss_1, &mantiss_2, operation);
  // основная часть
  int residual = 0;
  if (degree_result == -1) residual = 1;
  if (degree_result == -2) {
    if (!s21_is_zero(value_2) && !s21_is_zero(value_1)) need_round = 1;
    degree_result = count_mul;
  }
  if (degree_result != -1) {
    for (int i = 0; i < 3; i++)
      result->bits[i] =
          calc_bit(mantiss_1.bits[i], mantiss_2.bits[i], &residual, operation);
  }
  if (residual) {
    if (count_mul == 0) {
      int degree_1 = s21_def_degree(value_1.bits[3]);
      count_mul = degree_1 - 1;
    }
    degree_result = s21_cor_result_add(value_1, value_2, result, count_mul,
                                       operation, &residual);
  }
  answer = s21_overflow_for_add(sign_result, residual, need_round, result);
  // устанавливаем степень
  result->bits[3] = s21_set_degree(degree_result);
  // устанавливаем знак минус если результат не 0
  if (sign_result == -1 && !s21_is_zero(*result))
    result->bits[3] |= S21_BIT_MINUS;
  return answer;
}

// поверить значение когда разница между степенью может быть отрицательной
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal_nullify(result);
  // если степень больше 28 считать что 0?
  return calc_add(value_1, value_2, result, '+');
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal_nullify(result);
  // если степень больше 28 считать что 0?
  return calc_add(value_1, value_2, result, '-');
}

// возвращает переполнение, если есть перенос в старших 32 битах
int s21_shifting_bits(s21_decimal *a, int i) {
  int residual1 = 0;
  int residual2 = 0;
  int residual3 = 0;
  if (i > 0) {
    if (i < 32) {
      // 1111111...111111 >> (32 - 1) = 000000000...0001
      // 1111111...111111 >> (32 - 2) = 000000000...0011
      residual1 = (unsigned)a->bits[0] >> (32 - i);
      residual2 = (unsigned)a->bits[1] >> (32 - i);
      residual3 = (unsigned)a->bits[2] >> (32 - i);
      // 1111111...111111 << 1        = 1111111...111110
      // 1111111...111111 << 2        = 1111111...111100
      a->bits[0] = a->bits[0] << i;
      a->bits[1] = a->bits[1] << i;
      a->bits[1] |= residual1;
      a->bits[2] = a->bits[2] << i;
      a->bits[2] |= residual2;
    } else {
      if (i < 64) {
        // 1111111...111111 << (32 - 32) = 1111111...111111
        // 1111111...111111 << (33 - 32) = 1111111...111110
        residual1 = (unsigned)a->bits[0] << (i - 32);
        residual2 = (unsigned)a->bits[1] << (i - 32);
        // 1111111...111111 >> (64 - 33) = 000000000...0001
        if (i != 32) residual2 |= (unsigned)a->bits[0] >> (64 - i);
        residual3 = (unsigned)a->bits[2] << (i - 32);
        if (i != 32) residual3 |= (unsigned)a->bits[1] >> (64 - i);
        a->bits[0] = 0;
        a->bits[1] = residual1;
        a->bits[2] = residual2;
      } else {
        if (i < 96) {
          residual2 = (unsigned)a->bits[0] << (i - 64);
          residual3 = (unsigned)a->bits[1] << (i - 64);
          if (i != 64) residual3 |= (unsigned)a->bits[0] >> (96 - i);
          a->bits[0] = 0;
          a->bits[1] = 0;
          a->bits[2] = residual2;
        }
      }
    }
  }
  return residual3;
}

int s21_calc_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *sum) {
  int residual = 0;
  s21_decimal_nullify(sum);
  s21_decimal buf = value_1;
  for (int i = 0; i < 96 && residual == 0; i++) {
    if (s21_bit_eq_one(value_2, i)) {
      value_1 = buf;
      int residual_shift = s21_shifting_bits(&value_1, i);
      int residual_add = s21_add(*sum, value_1, sum);
      // если есть переполнение при сдвиге или суммировании
      if (residual_shift || residual_add) residual = 1;
    }
  }
  return residual;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int answer = 0;
  int residual = 0;
  s21_decimal_nullify(result);
  // определяем знак числа
  int sign_1 = s21_def_sign(value_1);
  int sign_2 = s21_def_sign(value_2);
  // если степень больше 28 считать что 0?
  // определяем степень
  int degree_1 = s21_def_degree(value_1.bits[3]);
  int degree_2 = s21_def_degree(value_2.bits[3]);
  // считаме значение 180064005714237130894418068.94 * 12.22
  s21_decimal sum1, sum2, sum3, sum4;
  s21_decimal trank_m1, trank_m2, sub_r1, sub_r2;
  s21_truncate(value_1, &trank_m1);
  s21_truncate(value_2, &trank_m2);
  s21_sub(value_1, trank_m1, &sub_r1);
  s21_sub(value_2, trank_m2, &sub_r2);
  trank_m1.bits[3] = 0;
  trank_m2.bits[3] = 0;
  sub_r1.bits[3] = 0;
  sub_r2.bits[3] = 0;
  // 180064005714237130894418068 * 12
  residual = s21_calc_mul(trank_m1, trank_m2, &sum1);
  // 180064005714237130894418068 * 0.22
  if (!residual) residual = s21_calc_mul(trank_m1, sub_r2, &sum2);
  sum2.bits[3] = s21_set_degree(degree_2);
  // 0.94 * 12
  if (!residual) residual = s21_calc_mul(sub_r1, trank_m2, &sum3);
  sum3.bits[3] = s21_set_degree(degree_1);
  // 0.94 * 0.22
  if (!residual) residual = s21_calc_mul(sub_r1, sub_r2, &sum4);
  sum4.bits[3] = s21_set_degree(degree_1 + degree_2);
  if (!residual) residual = s21_add(sum1, sum4, result);
  if (!residual) residual = s21_add(*result, sum2, result);
  if (!residual) residual = s21_add(*result, sum3, result);
  int degree_result = s21_def_degree(result->bits[3]);
  if (degree_result > 28 && !residual) {
    s21_decimal pow_ten;
    s21_decimal_pow_ten(&pow_ten, (degree_result - 28));
    result->bits[3] = s21_set_degree(28);
    s21_div(*result, pow_ten, result);
  }
  // устанавливаем знак
  if (sign_1 != sign_2) result->bits[3] |= S21_BIT_MINUS;
  if (residual) {
    answer = 1;
    if (result->bits[3] & (1 << 31)) answer = 2;
  }
  return answer;
}

// 3 - деление на 0
int s21_div_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
                s21_decimal *residual) {
  int answer = 0;
  s21_decimal_nullify(result);
  s21_decimal_nullify(residual);
  // деление на 0
  if (!s21_is_zero(value_2)) {
    s21_decimal value_2_abs = value_2;
    value_2_abs.bits[3] = 0;
    for (int i = 95; i > -1; i--) {
      answer = s21_shifting_bits(residual, 1);
      if (s21_bit_eq_one(value_1, i)) residual->bits[0] |= 1;
      if (s21_is_greater_or_equal(*residual, value_2_abs)) {
        s21_sub(*residual, value_2_abs, residual);
        s21_set_bit(result, i);
      }
    }
  } else {
    answer = 3;
  }
  return answer;
}

// нецелочисленное деление
void s21_not_int_div(s21_decimal value, s21_decimal *result,
                     s21_decimal *residual, int *degree) {
  s21_decimal old_residual;
  s21_decimal_nullify(&old_residual);
  int answer_mul_result = 0;
  int answer_mul_residual = 0;
  int exit = 0;
  // если остаток не равен 0, например 10 / -8 = -1.25
  while (!exit && *degree < 28 && !s21_is_zero(*residual)) {
    s21_decimal ten, div_result, mul_result, residual_abs;
    s21_from_int_to_decimal(10, &ten);
    residual_abs = *residual;
    residual_abs.bits[3] = 0;
    // умножаем результат на 10
    answer_mul_result = s21_mul(*result, ten, &mul_result);
    // умножаем остаток на 10
    answer_mul_residual = s21_mul(residual_abs, ten, &residual_abs);
    if (!answer_mul_residual) {
      s21_div_mod(residual_abs, value, &div_result, residual);
    } else {
      residual_abs = *residual;
      residual_abs.bits[3] = 0;
      // уменьшаем value_2
      s21_div_mod(value, ten, &value, &old_residual);
      s21_div_mod(residual_abs, value, &div_result, residual);
      s21_add(mul_result, div_result, result);
    }
    // если при умножении произошло переполнение
    // нужно банковское округление
    // если 0ой бит равен 1 число нечетно и
    // мы должны округлить до четного(прибавить 1)
    // иначе просто откидываем дробную часть
    if (answer_mul_result != 0) {
      (*degree)--;
      if (result->bits[0] & 1) {
        s21_decimal one;
        s21_from_int_to_decimal(1, &one);
        s21_add(*result, one, result);
        answer_mul_result = 0;
      } else {
        answer_mul_result = 0;
      }
      exit = 1;
    } else {
      s21_add(mul_result, div_result, result);
    }
    (*degree)++;
  }
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal residual;
  s21_decimal_nullify(&residual);
  s21_decimal_nullify(result);
  // определяем знак числа
  int sign_1 = s21_def_sign(value_1);
  int sign_2 = s21_def_sign(value_2);
  int answer = s21_div_mod(value_1, value_2, result, &residual);
  // если степень больше 28 считать что 0?
  int degree_1 = s21_def_degree(value_1.bits[3]);
  int degree_2 = s21_def_degree(value_2.bits[3]);
  int degree = degree_1 - degree_2;
  // residual == 0 5/2=2.5
  // degree < 1 4294967296 / 0.3 = 14316557653.(3)
  // 1 / 0.3 = 3.(3)
  s21_not_int_div(value_2, result, &residual, &degree);
  // округление
  if (!s21_is_zero(residual)) {
    if (result->bits[0] & 1) {
      s21_decimal one;
      s21_from_int_to_decimal(1, &one);
      s21_add(*result, one, result);
    }
  }
  // возможно например при 8 / 0.2
  if (degree < 0) {
    s21_decimal degree_mantiss;
    s21_decimal_nullify(&degree_mantiss);
    int error = s21_decimal_pow_ten(&degree_mantiss, degree * (-1));
    // 8/2 = 4; 4*10=40
    if (error) answer = s21_mul(*result, degree_mantiss, result);
  } else {
    result->bits[3] = s21_set_degree(degree);
  }
  if (sign_1 != sign_2) result->bits[3] |= S21_BIT_MINUS;
  if (degree > 28 || answer == 1 || answer == 2) {
    answer = 1;
    if (sign_1 != sign_2) answer = 2;
  }
  return answer;
}

// 0 - FALSE 1 - TRUE
int s21_is_less(s21_decimal a, s21_decimal b) {
  int result = 1;
  if (s21_is_greater_or_equal(a, b)) result = 0;
  return result;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  int result = 0;
  if (s21_is_less(a, b)) result = 1;
  if (s21_is_equal(a, b)) result = 1;
  return result;
}

int s21_bit_greater(s21_decimal a, s21_decimal b) {
  int result = 0;
  if ((unsigned)a.bits[2] > (unsigned)b.bits[2]) result = 1;
  if (a.bits[2] == b.bits[2]) {
    if ((unsigned)a.bits[1] > (unsigned)b.bits[1]) result = 1;
    if (a.bits[1] == b.bits[1]) {
      if ((unsigned)a.bits[0] > (unsigned)b.bits[0]) result = 1;
    }
  }
  return result;
}

// 0 - FALSE 1 - TRUE
int s21_is_greater(s21_decimal a, s21_decimal b) {
  int result = 0;
  int sign_a = s21_def_sign(a);
  int sign_b = s21_def_sign(b);
  int degree_a = s21_def_degree(a.bits[3]);
  int degree_b = s21_def_degree(b.bits[3]);
  if (sign_a == 1 && sign_b == -1) result = 1;
  if (sign_a == sign_b) {
    if (s21_is_not_equal(a, b)) {
      if (degree_a == degree_b) {
        result = s21_bit_greater(a, b);
      } else {
        s21_decimal a_trunk, b_trunk;
        s21_decimal_nullify(&a_trunk);
        s21_decimal_nullify(&b_trunk);
        s21_truncate(a, &a_trunk);
        s21_truncate(b, &b_trunk);
        if (s21_is_equal(a_trunk, b_trunk)) {
          // если дошли сюда можно умножать начальные числа.
          // Здесь не может быть переполнения
          s21_decimal ten;
          s21_from_int_to_decimal(10, &ten);
          if (degree_a > degree_b)
            for (int i = 0; i < degree_a - degree_b; i++) s21_mul(b, ten, &b);
          if (degree_a < degree_b)
            for (int i = 0; i < degree_b - degree_a; i++) s21_mul(a, ten, &a);
          result = s21_bit_greater(a, b);
        } else {
          result = s21_bit_greater(a_trunk, b_trunk);
        }
      }
    }
    if (sign_a == -1) result = !result;
  }
  return result;
}

// 0 - FALSE 1 - TRUE
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  int result = 0;
  if (s21_is_greater(a, b)) result = 1;
  if (s21_is_equal(a, b)) result = 1;
  return result;
}

// 0 - FALSE 1 - TRUE
// 0 = -0
// 123 != -123
int s21_is_equal(s21_decimal a, s21_decimal b) {
  int answer = 0;
  if (a.bits[0] == b.bits[0] && a.bits[1] == b.bits[1] &&
      a.bits[2] == b.bits[2]) {
    if (a.bits[0] == 0 && a.bits[1] == 0 && a.bits[2] == 0) {
      answer = 1;
    } else {
      if (a.bits[3] == b.bits[3]) answer = 1;
    }
  }
  return answer;
}

// 0 - FALSE 1 - TRUE
int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_equal(a, b);
}
