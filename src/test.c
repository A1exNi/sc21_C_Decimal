#include <check.h>

#include "s21_decimal.h"

START_TEST(add_simple) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};
  value_1.bits[0] = (int)256879;
  value_2.bits[0] = (int)22568;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 279447;

  int status = s21_add(value_1, value_2, &ans);
  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(add_simple_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};
  value_1.bits[0] = (int)895698;
  value_1.bits[3] |= S21_BIT_MINUS;
  value_2.bits[0] = (int)256899;
  value_2.bits[3] |= S21_BIT_MINUS;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)1152597;

  true_ans.bits[3] |= S21_BIT_MINUS;

  int status = s21_add(value_1, value_2, &ans);

  int answer_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(add_with_dot) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)613478421;
  value_1.bits[3] = (int)196608;

  value_2.bits[0] = (int)2056771366;
  value_2.bits[1] = (int)613;
  value_2.bits[3] = (int)393216;

  s21_decimal true_ans = {0};

  true_ans.bits[0] = (int)1354869038;
  true_ans.bits[1] = (int)756;

  true_ans.bits[3] = (int)393216;

  int status = s21_add(value_1, value_2, &ans);
  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(add_with_dot_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)613478421;
  value_1.bits[3] = 196608;

  value_2.bits[0] = (int)0;
  value_2.bits[3] = 393216;

  s21_decimal true_ans = {0};
  true_ans.bits[1] = (int)142;
  true_ans.bits[0] = (int)3593064968;
  true_ans.bits[3] = 393216;

  int status = s21_add(value_1, value_2, &ans);
  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(add_zero) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};

  value_1.bits[0] = (int)723947;
  value_1.bits[1] = (int)839204;
  value_1.bits[2] = (int)8239;

  value_2.bits[3] = (int)1835008;

  s21_decimal ans = {0};

  int status = s21_add(value_1, value_2, &ans);

  s21_decimal true_ans = {0};

  true_ans.bits[0] = (int)3675223264;
  true_ans.bits[1] = (int)2316021392;
  true_ans.bits[2] = (int)823900019;
  true_ans.bits[3] = (int)327680;

  int answer_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}

START_TEST(add_big_values_with_dot_overflow) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)4294967295;
  value_1.bits[1] = (int)4294967295;
  value_1.bits[2] = (int)4294967295;
  value_1.bits[3] = (int)196608;

  value_2.bits[0] = (int)1;
  value_2.bits[3] = (int)196608;

  s21_decimal true_ans = {0};

  true_ans.bits[0] = (int)2576980378;
  true_ans.bits[1] = (int)2576980377;
  true_ans.bits[2] = (int)429496729;
  true_ans.bits[3] = (int)131072;

  int status = s21_add(value_1, value_2, &ans);
  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(add_big_values_overflow) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)4238529012;
  value_1.bits[1] = (int)4294967295;
  value_1.bits[2] = (int)0;

  value_2.bits[0] = (int)56438283;
  value_2.bits[1] = (int)4294967295;
  value_2.bits[2] = (int)4294967294;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)4294967295;
  true_ans.bits[1] = (int)4294967294;
  true_ans.bits[2] = (int)4294967295;

  int status = s21_add(value_1, value_2, &ans);

  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(add_big_values) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)4238529012;
  value_1.bits[1] = (int)4294967295;
  value_1.bits[2] = (int)4294967295;

  value_2.bits[0] = (int)56438283;
  value_2.bits[1] = (int)4294967295;
  value_2.bits[2] = (int)4294967294;

  int status = s21_add(value_1, value_2, &ans);

  int answer_status = 1;
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(add_to_sub) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)23784103;

  value_2.bits[0] = (int)721398;
  value_2.bits[3] |= S21_BIT_MINUS;

  s21_decimal true_ans = {0};

  true_ans.bits[0] = (int)23062705;

  int status = s21_add(value_1, value_2, &ans);
  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(add_to_sub_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};
  value_1.bits[0] = (int)74563556;
  value_1.bits[3] |= S21_BIT_MINUS;
  value_2.bits[0] = (int)24567653;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)49995903;
  true_ans.bits[3] |= S21_BIT_MINUS;
  int status = s21_add(value_1, value_2, &ans);
  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(add_big_values_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};
  value_1.bits[0] = (int)4294967294;
  value_1.bits[1] = (int)4294967295;
  value_1.bits[2] = (int)4294967295;

  value_2.bits[0] = (int)1;
  value_2.bits[1] = (int)0;
  value_2.bits[2] = (int)0;
  value_2.bits[3] = (int)1835008;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)4294967294;
  true_ans.bits[1] = (int)4294967295;
  true_ans.bits[2] = (int)4294967295;

  int status = s21_add(value_1, value_2, &ans);
  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(s21_add_1) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(
      result.bits[0] + result.bits[1] + result.bits[2] + result.bits[3], 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_2) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(
      result.bits[0] + result.bits[1] + result.bits[2] + result.bits[3], 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_add_3) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{1, 1, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_add_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int x = 10, y = 10, z = 20, result_int = 0;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_int_to_decimal(y, &value_2);
  int return_value = s21_add(value_1, value_2, &result);
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, z);
}
END_TEST

START_TEST(s21_add_5) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {{1, 1, 1, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
  for (int i = 0; i < 3; i++)
    ck_assert_int_eq(result.bits[i], (int)0xFFFFFFFF - 1);
}
END_TEST

START_TEST(s21_add_6) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int x = 2;
  float result_float = 0, y = 1.2345678, z = x + y;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_float_to_decimal(y, &value_2);
  int return_value = s21_add(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(fabs((result_float - z)) < 1e-6, 1);
}
END_TEST

START_TEST(s21_add_7) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{1, 1, 1, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 2);
}
END_TEST

START_TEST(add_8) {
  s21_decimal val1 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_9) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_10) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{1, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_12) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_13) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_14) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_15) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_16) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_17) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_18) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {0};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_19) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_20) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_21) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_22) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_23) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_24) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_25) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  val1.bits[3] = s21_set_degree(5);
  val2.bits[3] = s21_set_degree(5);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(add_26) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  val1.bits[3] = s21_set_degree(5);
  val2.bits[3] = s21_set_degree(3);
  s21_decimal res;
  ck_assert_int_eq(0, s21_add(val1, val2, &res));
}
END_TEST

START_TEST(sub_simple) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)987654;

  value_2.bits[0] = (int)123654;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)864000;

  int status = s21_sub(value_1, value_2, &ans);

  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(sub_simple_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)123654;
  value_2.bits[0] = (int)987654;

  s21_decimal true_ans = {0};

  true_ans.bits[0] = (int)864000;
  true_ans.bits[3] |= S21_BIT_MINUS;

  int status = s21_sub(value_1, value_2, &ans);
  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(sub_simple_3) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)987654;
  value_1.bits[3] |= S21_BIT_MINUS;

  value_2.bits[0] = (int)123654;
  value_2.bits[3] |= S21_BIT_MINUS;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)864000;
  true_ans.bits[3] |= S21_BIT_MINUS;

  int status = s21_sub(value_1, value_2, &ans);

  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(sub_simple_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)240001;
  value_1.bits[3] |= S21_BIT_MINUS;

  value_2.bits[0] = (int)740002;
  value_2.bits[3] |= S21_BIT_MINUS;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)500001;

  int status = s21_sub(value_1, value_2, &ans);

  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(sub_with_dot) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)532167;
  value_1.bits[3] = (int)196608;

  value_2.bits[0] = (int)1236;
  value_2.bits[3] = (int)983040;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)607087404;
  true_ans.bits[1] = (int)123904785;
  true_ans.bits[3] = (int)983040;
  int status = s21_sub(value_1, value_2, &ans);
  int answer_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(sub_with_dot_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)532167;
  value_1.bits[3] = (int)196608;

  value_2.bits[0] = (int)0;
  value_2.bits[3] = (int)0;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)532167;
  true_ans.bits[3] = (int)196608;

  int status = s21_sub(value_1, value_2, &ans);
  int answer_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(sub_to_add) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};
  value_1.bits[0] = (int)569999;
  value_1.bits[3] |= S21_BIT_MINUS;

  value_2.bits[0] = (int)30001;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)600000;
  true_ans.bits[3] |= S21_BIT_MINUS;

  int status = s21_sub(value_1, value_2, &ans);

  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(sub_to_add_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};
  value_1.bits[0] = (int)1152597;

  value_2.bits[0] = (int)2656565;
  value_2.bits[3] |= S21_BIT_MINUS;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)3809162;

  int status = s21_sub(value_1, value_2, &ans);

  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(sub_big_values) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)4294967295;
  value_1.bits[1] = (int)4294967295;
  value_1.bits[2] = (int)4294967295;

  value_2.bits[0] = (int)6;
  value_2.bits[1] = (int)0;
  value_2.bits[2] = (int)0;
  value_2.bits[3] = (int)65536;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)4294967294;
  true_ans.bits[1] = (int)4294967295;
  true_ans.bits[2] = (int)4294967295;
  int status = s21_sub(value_1, value_2, &ans);

  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(s21_sub_1) {
  s21_decimal value_1 = {{0, 0, 0, 0x80000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result), x = 0;
  s21_from_decimal_to_int(result, &x);
  ck_assert_int_eq(x, 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_2) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(
      result.bits[0] + result.bits[1] + result.bits[2] + result.bits[3], 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_sub_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {{1, 1, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(return_value, 0);
  for (int i = 0; i < 3; i++)
    ck_assert_int_eq(result.bits[i], (int)0xFFFFFFFF - 1);
}
END_TEST
//
START_TEST(s21_sub_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int x = 10, y = 2147483638, result_int = 0;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_int_to_decimal(y, &value_2);
  int return_value = s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, -2147483628);
}
END_TEST

START_TEST(s21_sub_5) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0] + result.bits[1] + result.bits[2], 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST
//
START_TEST(s21_sub_6) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  int x = 2;
  float result_float = 0, y = 1.2345678, z = x - 1.2345678;
  s21_from_int_to_decimal(x, &value_1);
  s21_from_float_to_decimal(y, &value_2);
  int return_value = s21_sub(value_1, value_2, &result);
  s21_from_decimal_to_float(result, &result_float);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(fabs((result_float - z)) < 1e-7, 1);
}
END_TEST

START_TEST(s21_sub_7) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal value_2 = {{1, 1, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_sub(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(sub_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_8) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_9) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_10) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {0};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_14) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(2, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_15) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_16) {
  s21_decimal val1 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_17) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_18) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal res;
  ck_assert_int_eq(1, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(sub_19) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_sub(val1, val2, &res));
}
END_TEST

START_TEST(mul_simple) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};
  value_1.bits[0] = (int)1526;
  value_2.bits[0] = (int)1000;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)1526000;

  int status = s21_mul(value_1, value_2, &ans);
  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(mul_simple_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};
  value_1.bits[0] = (int)125236476;
  value_1.bits[3] = (int)393216;

  value_2.bits[0] = (int)364287140;
  value_2.bits[3] = (int)2147483648 + (int)196608;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)1694409072;
  true_ans.bits[1] = (int)10622208;
  true_ans.bits[3] = (int)589824 + (int)2147483648;

  int status = s21_mul(value_1, value_2, &ans);
  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(mul_with_overflow) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[2] = (int)4294967295;

  value_2.bits[0] = 2;

  int status = s21_mul(value_1, value_2, &ans);
  int answer_status = 1;

  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(mul_fits) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)4294967295;
  value_1.bits[1] = (int)4294967295;
  value_1.bits[2] = (int)2147483647;

  value_2.bits[0] = 2;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)4294967294;
  true_ans.bits[1] = (int)4294967295;
  true_ans.bits[2] = (int)4294967295;

  int status = s21_mul(value_1, value_2, &ans);
  int answer_status = 0;

  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, answer_status);
}
END_TEST

START_TEST(mul_with_overflow_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)137900165;
  value_1.bits[1] = (int)69122625;
  value_1.bits[2] = (int)1;
  value_1.bits[3] = (int)1310720;

  value_2.bits[0] = (int)46246921;
  value_2.bits[1] = (int)0;
  value_2.bits[2] = (int)0;
  value_2.bits[3] = (int)983040;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)2090836748;
  true_ans.bits[1] = (int)3002702997;
  true_ans.bits[2] = (int)4;
  true_ans.bits[3] = (int)1835008;

  int status = s21_mul(value_1, value_2, &ans);
  int answer_status = 0;
  ck_assert_int_eq(status, answer_status);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(mul_with_overflow_3) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal ans = {0};

  value_1.bits[0] = (int)137900165;
  value_1.bits[1] = (int)69122625;
  value_1.bits[2] = (int)1;
  value_1.bits[3] = (int)1310720;

  value_2.bits[0] = (int)1;
  value_2.bits[1] = (int)0;
  value_2.bits[2] = (int)0;
  value_2.bits[3] = (int)1048576;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = (int)2752641148;
  true_ans.bits[1] = (int)43;
  true_ans.bits[2] = (int)0;
  true_ans.bits[3] = (int)1835008;

  int status = s21_mul(value_1, value_2, &ans);
  int answer_status = 0;
  ck_assert_int_eq(status, answer_status);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
}
END_TEST

START_TEST(mul_0) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_1) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_2) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_6) {
  s21_decimal val1 = {{8, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_7) {
  s21_decimal val1 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_8) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_9) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_10) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_11) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{0, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_12) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, ~(UINT_MAX / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  val1.bits[3] = s21_set_degree(1);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_13) {
  s21_decimal val1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal val2 = {{200, 0, 0, 0}};
  s21_decimal res = {0};
  val1.bits[3] = s21_set_degree(1);
  val2.bits[3] = s21_set_degree(2);
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(mul_14) {
  s21_decimal val1 = {{20, 0, 0, 0}};
  val1.bits[3] = s21_set_degree(1);
  s21_decimal val2 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  val2.bits[3] = s21_set_degree(2);
  s21_decimal res = {0};

  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(div_simple) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans = {0};
  dec1.bits[0] = 125688;
  dec2.bits[0] = 2;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 62844;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(basic_div) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans = {0};
  dec1.bits[0] = 125688;
  dec1.bits[3] |= S21_BIT_MINUS;
  dec2.bits[0] = 2;
  s21_decimal true_ans = {0};
  true_ans.bits[0] = 62844;
  // set_sign(true_ans);
  true_ans.bits[3] |= S21_BIT_MINUS;
  int status = s21_div(dec1, dec2, &ans);
  int true_status = 0;
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(status, true_status);
}
END_TEST

START_TEST(int_to_decimal_INT32MAX) {
  s21_decimal decimal = {0};
  int i = INT32_MAX, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_to_decimal_INT32MIN) {
  s21_decimal decimal = {0};
  int i = INT32_MIN, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_to_decimal_0) {
  s21_decimal decimal = {0};
  int i = 0, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_to_decimal_minus) {
  s21_decimal decimal = {0};
  int i = -12500, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_to_decimal_plus) {
  s21_decimal decimal = {0};
  int i = 12500, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_to_decimal_5) {
  s21_decimal decimal = {0};
  int i = -5, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(int_to_decimal_1) {
  s21_decimal decimal = {0};
  int i = 1, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(is_equal_simple) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  int val_1 = 10250;
  int status = s21_from_int_to_decimal(val_1, &value_1);
  int second_status = s21_from_int_to_decimal(val_1, &value_2);
  ck_assert_int_eq(1, s21_is_equal(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_equal_with_scale) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  float val_1 = 613478.421;
  float val_2 = 613.478421;
  int status = s21_from_float_to_decimal(val_1, &value_1);
  int second_status = s21_from_float_to_decimal(val_2, &value_2);
  ck_assert_int_eq(0, s21_is_equal(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_equal_big_with_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = (int)4294967295;
  value_1.bits[1] = (int)4294967295;
  value_1.bits[2] = (int)4294967295;
  value_1.bits[3] |= S21_BIT_MINUS;
  value_2.bits[0] = (int)4294967295;
  value_2.bits[1] = (int)4294967295;
  value_2.bits[2] = (int)4294967295;
  ck_assert_int_eq(0, s21_is_equal(value_1, value_2));
}
END_TEST

START_TEST(is_not_equal_simple) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  int val_1 = 10250;
  int status = s21_from_int_to_decimal(val_1, &value_1);
  int second_status = s21_from_int_to_decimal(val_1, &value_2);
  ck_assert_int_eq(0, s21_is_not_equal(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_not_equal_with_scale) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  float val_1 = 613478.421;
  float val_2 = 613.478421;
  int status = s21_from_float_to_decimal(val_1, &value_1);
  int second_status = s21_from_float_to_decimal(val_2, &value_2);
  ck_assert_int_eq(1, s21_is_not_equal(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_not_equal_big_with_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = (int)4294967295;
  value_1.bits[1] = (int)4294967295;
  value_1.bits[2] = (int)4294967295;
  value_1.bits[3] |= S21_BIT_MINUS;
  value_2.bits[0] = (int)4294967295;
  value_2.bits[1] = (int)4294967295;
  value_2.bits[2] = (int)4294967295;
  ck_assert_int_eq(1, s21_is_not_equal(value_1, value_2));
}
END_TEST

START_TEST(is_greater) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  int val_1 = 10250;
  int val_2 = 0;
  int status = s21_from_int_to_decimal(val_1, &value_1);
  int second_status = s21_from_int_to_decimal(val_2, &value_2);
  ck_assert_int_eq(1, s21_is_greater(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_greater_with_scale) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  float val_1 = 613478.421;
  float val_2 = 613.478421;
  int status = s21_from_float_to_decimal(val_1, &value_1);
  int second_status = s21_from_float_to_decimal(val_2, &value_2);
  ck_assert_int_eq(1, s21_is_greater(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_greater_with_scale_1) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  float val_1 = 61347842.1;
  float val_2 = 613478421.0;
  int status = s21_from_float_to_decimal(val_1, &value_1);
  int second_status = s21_from_float_to_decimal(val_2, &value_2);
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_greater_big_with_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = (int)4294967295;
  value_1.bits[1] = (int)4294967295;
  value_1.bits[2] = (int)4294967295;
  value_1.bits[3] |= S21_BIT_MINUS;
  value_2.bits[0] = (int)4294967295;
  value_2.bits[1] = (int)4294967295;
  value_2.bits[2] = (int)4294967295;
  ck_assert_int_eq(0, s21_is_greater(value_1, value_2));
}
END_TEST

START_TEST(is_greater_or_equal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  int val_1 = 10250;
  int status = s21_from_int_to_decimal(val_1, &value_1);
  int second_status = s21_from_int_to_decimal(val_1, &value_2);
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_greater_or_equal_with_scale) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  float val_1 = 613478.421;
  float val_2 = 613.478421;
  int status = s21_from_float_to_decimal(val_1, &value_1);
  int second_status = s21_from_float_to_decimal(val_2, &value_2);
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_greater_or_equal_with_scale_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  float val_1 = 61347842.1;
  float val_2 = 61347842.1;
  int status = s21_from_float_to_decimal(val_1, &value_1);
  int second_status = s21_from_float_to_decimal(val_2, &value_2);
  ck_assert_int_eq(1, s21_is_greater_or_equal(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_greater_or_equal_big_with_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = (int)4294967295;
  value_1.bits[1] = (int)4294967295;
  value_1.bits[2] = (int)4294967295;
  value_1.bits[3] |= S21_BIT_MINUS;
  value_2.bits[0] = (int)4294967295;
  value_2.bits[1] = (int)4294967295;
  value_2.bits[2] = (int)4294967295;
  ck_assert_int_eq(0, s21_is_greater_or_equal(value_1, value_2));
}
END_TEST

START_TEST(is_less_or_equal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  int val_1 = 10250;
  int status = s21_from_int_to_decimal(val_1, &value_1);
  int second_status = s21_from_int_to_decimal(val_1, &value_2);
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_less_or_equal_with_scale) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  float val_1 = 613478.421;
  float val_2 = 613.478421;
  int status = s21_from_float_to_decimal(val_1, &value_1);
  int second_status = s21_from_float_to_decimal(val_2, &value_2);
  ck_assert_int_eq(0, s21_is_less_or_equal(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_less_or_equal_with_scale_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  float val_1 = 61347842.1;
  float val_2 = 61347842.1;
  int status = s21_from_float_to_decimal(val_1, &value_1);
  int second_status = s21_from_float_to_decimal(val_2, &value_2);
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_less_or_equal_big_with_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = (int)4294967295;
  value_1.bits[1] = (int)4294967295;
  value_1.bits[2] = (int)4294967295;
  value_1.bits[3] |= S21_BIT_MINUS;
  value_2.bits[0] = (int)4294967295;
  value_2.bits[1] = (int)4294967295;
  value_2.bits[2] = (int)4294967295;
  ck_assert_int_eq(1, s21_is_less_or_equal(value_1, value_2));
}
END_TEST

START_TEST(is_less) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  int val_1 = 10250;
  int val_2 = 0;
  int status = s21_from_int_to_decimal(val_1, &value_1);
  int second_status = s21_from_int_to_decimal(val_2, &value_2);
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_less_with_scale) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  float val_1 = 613478.421;
  float val_2 = 613.478421;
  int status = s21_from_float_to_decimal(val_1, &value_1);
  int second_status = s21_from_float_to_decimal(val_2, &value_2);
  ck_assert_int_eq(0, s21_is_less(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_less_with_scale_1) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  float val_1 = 61347842.1;
  float val_2 = 613478421.0;
  int status = s21_from_float_to_decimal(val_1, &value_1);
  int second_status = s21_from_float_to_decimal(val_2, &value_2);
  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
  ck_assert_int_eq(status, second_status);
}
END_TEST

START_TEST(is_less_big_with_minus) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = (int)4294967295;
  value_1.bits[1] = (int)4294967295;
  value_1.bits[2] = (int)4294967295;
  value_1.bits[3] |= S21_BIT_MINUS;
  value_2.bits[0] = (int)4294967295;
  value_2.bits[1] = (int)4294967295;
  value_2.bits[2] = (int)4294967295;
  ck_assert_int_eq(1, s21_is_less(value_1, value_2));
}
END_TEST

void truncate_test_function(float n, float accuracy) {
  float value0 = 0.0;
  s21_decimal var1 = {0}, var2 = {0};

  int value1 = 0, value2 = 0;
  s21_from_float_to_decimal(n, &var1);
  s21_truncate(var1, &var2);
  s21_from_decimal_to_float(var2, &value0);
  value2 = (int)value0;
  value1 = truncf(n);
  ck_assert_float_eq_tol(value1, value2, accuracy);
  return;
}

START_TEST(truncate_0n) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_1n) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_2n) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_3n) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(5);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -0.0;
  ck_assert_float_eq(need, fres);
}

START_TEST(truncate_4n) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(1);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 12;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_6n) {
  s21_decimal value_1 = {{35, 0, 0, 0}};
  s21_decimal check = {{3, 0, 0, 0}};
  value_1.bits[3] = s21_set_degree(1);
  s21_truncate(value_1, &value_1);
  ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(truncate_7n) {
  s21_decimal value_1 = {{123456, 0, 0, 0}};
  value_1.bits[3] = s21_set_degree(3);
  value_1.bits[3] |= S21_BIT_MINUS;
  s21_decimal check = {{123, 0, 0, 0}};
  check.bits[3] |= S21_BIT_MINUS;
  s21_truncate(value_1, &value_1);
  ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(truncate_8n) {
  s21_decimal src1 = {0};
  src1.bits[3] = 0x000A0000;
  src1.bits[2] = 0x0;
  src1.bits[1] = 0xFFFFFFFF;
  src1.bits[0] = 0xFFFFFFFF;
  s21_decimal result = {0};
  result.bits[3] = 0x0;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x6DF37F67;
  s21_decimal res_od = {0};
  s21_truncate(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(truncate_9n) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b00000000000000000000000001101101;
  src1.bits[1] = 0b00000000000011000110010101011011;
  src1.bits[2] = 0b00000000000000000011000000111001;
  src1.bits[3] = 0b00000000000011100000000000000000;
  s21_decimal result = {0};
  result.bits[0] = 0b10000111101111000001011000011110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res_od = {0};
  s21_truncate(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_trun_1) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b00000000000000000000000011010011;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000010101;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1 = {0};
  s21_truncate(value_1, &res1);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_trun_2) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b00000000000000000000000010100101;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000010000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1 = {0};
  s21_truncate(value_1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_trun_4) {
  s21_decimal value_1 = {0};
  value_1.bits[0] = 0b10000000000000000000000010100101;
  value_1.bits[1] = 0b00000000000000000000000000000000;
  value_1.bits[2] = 0b00000000000000000000000000000000;
  value_1.bits[3] = 0b00000000000001110000000000000000;
  float num = 0.0;
  s21_from_decimal_to_float(value_1, &num);
  s21_decimal result = {0};
  result.bits[0] = 0b00000000000000000000000011010110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1 = {0};
  s21_truncate(value_1, &res1);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_1) {
  s21_decimal value_1 = {0};

  value_1.bits[3] = 0x000A0000;
  value_1.bits[2] = 0x0;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[0] = 0xFFFFFFFF;
  s21_decimal result = {0};
  result.bits[3] = 0x0;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x6DF37F67;
  s21_decimal res1 = {0};
  s21_truncate(value_1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal value_1 = {0};

  value_1.bits[3] = 0b10000000000011000000000000000000;
  value_1.bits[2] = 0x0;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[0] = 0xFFFFFFFF;
  s21_decimal result = {0};
  result.bits[3] = 0b10000000000000000000000000000000;
  result.bits[2] = 0x0;
  result.bits[1] = 0x0;
  result.bits[0] = 0x1197998;
  s21_decimal res1 = {0};
  s21_truncate(value_1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_3) {
  s21_decimal value_1 = {0};

  value_1.bits[3] = 0x80000000;
  value_1.bits[2] = 0x0;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[0] = 0xFFFFFFFF;
  s21_decimal result = {0};
  result.bits[3] = 0x80000000;
  result.bits[2] = 0x0;
  result.bits[1] = 0xFFFFFFFF;
  result.bits[0] = 0xFFFFFFFF;
  s21_decimal res1 = {0};
  s21_truncate(value_1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_4) {
  s21_decimal value_1 = {0};

  value_1.bits[0] = 0b00000000000000000000000001101101;
  value_1.bits[1] = 0b00000000000011000110010101011011;
  value_1.bits[2] = 0b00000000000000000011000000111001;
  value_1.bits[3] = 0b00000000000011100000000000000000;
  s21_decimal result = {0};
  result.bits[0] = 0b10000111101111000001011000011110;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1 = {0};
  s21_truncate(value_1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncate_6) {
  s21_decimal value_1 = {0};

  value_1.bits[3] = 0x80090000;
  value_1.bits[2] = 0;
  value_1.bits[1] = 0xFFFFEA34;
  value_1.bits[0] = 0xFF837E4F;
  s21_decimal result = {0};
  s21_truncate(value_1, &result);
  s21_decimal res1 = {0};

  res1.bits[3] = 0x80000000;
  res1.bits[2] = 0;
  res1.bits[1] = 0x4;
  res1.bits[0] = 0x4B829C70;
  ck_assert_int_eq(res1.bits[3], result.bits[3]);
  ck_assert_int_eq(res1.bits[2], result.bits[2]);
  ck_assert_int_eq(res1.bits[1], result.bits[1]);
  ck_assert_int_eq(res1.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncate_7) {
  s21_decimal value_1 = {0};

  value_1.bits[0] = 0b11010000101000110011000001101101;
  value_1.bits[1] = 0b00011111100110100110101101011000;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b00000000000010010000000000000000;
  s21_decimal result = {0};
  s21_truncate(value_1, &result);
  s21_decimal result_origin;
  result_origin.bits[3] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b10000111101111000001011000011110;
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncate_8) {
  s21_decimal value_1 = {0};

  value_1.bits[0] = 0b01111000101001111011110011000110;
  value_1.bits[1] = 0b10011111111111001111101010000100;
  value_1.bits[2] = 0b00011111111010011010111101101101;
  value_1.bits[3] = 0b00000000000111000000000000000000;
  s21_decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1 = {0};
  s21_truncate(value_1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_truncateTest1) {
  s21_decimal src1, origin;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest2) {
  s21_decimal src1, origin;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest3) {
  s21_decimal src1, origin;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest4) {
  s21_decimal src1, origin;

  src1.bits[0] = 0b00000000000000000000000000000000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest5) {
  s21_decimal src1, origin;

  src1.bits[0] = 0b01001100110100101000000111000101;
  src1.bits[1] = 0b00000000000000000000000000000010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b01001100110100101000000111000101;
  origin.bits[1] = 0b00000000000000000000000000000010;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest6) {
  s21_decimal src1, origin;

  src1.bits[0] = 0b10000010111000100101101011101101;
  src1.bits[1] = 0b11111001111010000010010110101101;
  src1.bits[2] = 0b10110000001111101111000010010100;
  src1.bits[3] = 0b10000000000011100000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b10000110011101001011101110010001;
  origin.bits[1] = 0b00000000000000011111000000010110;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest7) {
  s21_decimal src1, origin;

  src1.bits[0] = 0b00000111100110110001111110011000;
  src1.bits[1] = 0b01100110010010001001000110100011;
  src1.bits[2] = 0b00000000000001001000101100011101;
  src1.bits[3] = 0b10000000000110000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest8) {
  s21_decimal src1, origin;

  src1.bits[0] = 0b01001110111001000011100101110110;
  src1.bits[1] = 0b01001011001101011010000111011001;
  src1.bits[2] = 0b00011001101110010111010010111111;
  src1.bits[3] = 0b00000000000011110000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b10100100000111100100000000101101;
  origin.bits[1] = 0b00000000000000000000011100111101;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest9) {
  s21_decimal src1, origin;

  src1.bits[0] = 0b01111000100010101111010011001010;
  src1.bits[1] = 0b01100010000010101110010010000111;
  src1.bits[2] = 0b00100111111001000001101011010101;
  src1.bits[3] = 0b10000000000101010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000101111000110000101001101;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest10) {
  s21_decimal src1, origin;

  src1.bits[0] = 0b01100101111011101101100101011111;
  src1.bits[1] = 0b01011100001001010100001101000110;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_truncateTest11) {
  s21_decimal src1, origin;

  src1.bits[0] = 0b00000000000000000000000000000001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_truncate(src1, &result);

  origin.bits[0] = 0b00000000000000000000000000000001;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(truncate_0) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_1) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -2.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(truncate_3) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(5);
  // set_scale(&val, 5);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = -0.0;
  ck_assert_float_eq(need, fres);
}

START_TEST(truncate_4) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(1);
  // set_scale(&val, 1);
  ck_assert_int_eq(0, s21_truncate(val, &res));
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 12;
  ck_assert_float_eq(need, fres);
}

START_TEST(floor_0) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST

START_TEST(floor_1) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(5);
  val.bits[3] |= S21_BIT_MINUS;
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-1, fres);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(0, fres);
}
END_TEST

void floor_test_function(float n, float accuracy) {
  s21_decimal var1 = {0}, var2 = {0};
  float value1 = 0, value2 = 0;
  s21_from_float_to_decimal(n, &var1);
  s21_floor(var1, &var2);
  s21_from_decimal_to_float(var2, &value2);
  value1 = floorf(n);
  ck_assert_float_eq_tol(value1, value2, accuracy);
}

START_TEST(floor_0n) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST

START_TEST(floor_1n) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

START_TEST(floor_2n) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(5);
  val.bits[3] |= S21_BIT_MINUS;
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-1, fres);
}
END_TEST

START_TEST(floor_3n) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(0, fres);
}
END_TEST

START_TEST(floor_5n) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  value_1.bits[3] = s21_set_degree(5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(floor_6n) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  value_1.bits[3] = s21_set_degree(5);
  value_1.bits[3] |= S21_BIT_MINUS;
  s21_decimal check = {{75, 0, 0, 0}};
  check.bits[3] |= S21_BIT_MINUS;
  s21_decimal result = {0};
  int return_value = s21_floor(value_1, &result);

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(floor_7n) {
  s21_decimal src1;
  src1.bits[0] = 0b00001111111111111111111111111111;
  src1.bits[1] = 0b00111110001001010000001001100001;
  src1.bits[2] = 0b00100000010011111100111001011110;
  src1.bits[3] = 0b10000000000010100000000000000000;
  s21_decimal res_od = {0};
  s21_floor(src1, &res_od);
  s21_decimal result = {0};
  result.bits[0] = 0b10100111011001000000000000000000;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

void round_test_function(float n, float accuracy) {
  s21_decimal var1 = {0}, var2 = {0};
  float value1 = 0.0, value2 = 0.0;
  s21_from_float_to_decimal(n, &var1);
  s21_round(var1, &var2);
  s21_from_decimal_to_float(var2, &value2);
  value1 = roundf(n);
  ck_assert_float_eq_tol(value1, value2, accuracy);
  return;
}

START_TEST(round_0) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res;
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(round_1) {
  s21_decimal val = {{3, 3, 3, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_2) {
  s21_decimal val = {{3, 3, 3, 0}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_3) {
  s21_decimal val = {{7, 7, 7, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_4) {
  s21_decimal val = {{25, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_5) {
  s21_decimal val = {{26, 0, 0, 0}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_6) {
  s21_decimal val = {{115, 0, 0, 0}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_7) {
  s21_decimal val = {{118, 0, 0, 0}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_8) {
  s21_decimal val = {{125, 0, 0, 0}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_9) {
  s21_decimal val = {{128, 0, 0, 0}};
  s21_decimal res = {0};
  val.bits[3] = s21_set_degree(1);
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 13;
  ck_assert_float_eq(need, fres);
}
END_TEST

START_TEST(round_11) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  value_1.bits[3] = s21_set_degree(5);
  s21_decimal check = {{75, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_12) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  value_1.bits[3] = s21_set_degree(5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_13) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  value_1.bits[3] = s21_set_degree(5);
  value_1.bits[3] |= S21_BIT_MINUS;
  s21_decimal check = {{75, 0, 0, 0}};
  check.bits[3] |= S21_BIT_MINUS;
  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_14) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  value_1.bits[3] = s21_set_degree(5);
  value_1.bits[3] |= S21_BIT_MINUS;
  s21_decimal check = {{74, 0, 0, 0}};
  check.bits[3] |= S21_BIT_MINUS;
  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_15) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b01010101001110101110101110110001;
  src1.bits[1] = 0b00001101101101001101101001011111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000100100000000000000000;
  s21_decimal result = {0};
  result.bits[0] = 0b00000000000000000000000000000001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res_od = {0};
  s21_round(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(round_16) {
  s21_decimal src1 = {0};
  src1.bits[0] = 0b10010111011100111001111111111111;
  src1.bits[1] = 0b00111100000010000011000110001101;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b10000000000001110000000000000000;
  s21_decimal res_od = {0};
  s21_round(src1, &res_od);
  s21_decimal result = {0};
  result.bits[3] = 0b10000000000000000000000000000000;
  result.bits[2] = 0;
  result.bits[1] = 0b00000000000000000000001000010010;
  result.bits[0] = 0b00110110101101101000110001000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(negate_1) {
  s21_decimal a, b, c;
  s21_decimal_nullify(&a);
  a.bits[0] = (int)123;
  a.bits[3] |= S21_BIT_MINUS;
  s21_decimal_nullify(&b);
  b.bits[0] = (int)123;
  s21_negate(a, &c);
  ck_assert_int_eq(c.bits[0], b.bits[0]);
  ck_assert_int_eq(c.bits[1], b.bits[1]);
  ck_assert_int_eq(c.bits[2], b.bits[2]);
  ck_assert_int_eq(c.bits[3], b.bits[3]);
}

START_TEST(negate_2) {
  s21_decimal a, b, c;
  s21_decimal_nullify(&a);
  a.bits[0] = (int)123;
  s21_decimal_nullify(&b);
  b.bits[0] = (int)123;
  b.bits[3] |= S21_BIT_MINUS;
  s21_negate(a, &c);
  ck_assert_int_eq(c.bits[0], b.bits[0]);
  ck_assert_int_eq(c.bits[1], b.bits[1]);
  ck_assert_int_eq(c.bits[2], b.bits[2]);
  ck_assert_int_eq(c.bits[3], b.bits[3]);
}

START_TEST(negate_3) {
  s21_decimal a, b, c;
  s21_decimal_nullify(&a);
  a.bits[0] = (int)123;
  a.bits[3] = s21_set_degree(5);
  a.bits[3] |= S21_BIT_MINUS;
  s21_decimal_nullify(&b);
  b.bits[0] = (int)123;
  b.bits[3] = s21_set_degree(5);
  s21_negate(a, &c);
  ck_assert_int_eq(c.bits[0], b.bits[0]);
  ck_assert_int_eq(c.bits[1], b.bits[1]);
  ck_assert_int_eq(c.bits[2], b.bits[2]);
  ck_assert_int_eq(c.bits[3], b.bits[3]);
}

START_TEST(negate_4) {
  s21_decimal a, b, c;
  s21_decimal_nullify(&a);
  a.bits[0] = (int)123;
  a.bits[3] = s21_set_degree(5);
  s21_decimal_nullify(&b);
  b.bits[0] = (int)123;
  b.bits[3] = s21_set_degree(5);
  b.bits[3] |= S21_BIT_MINUS;
  s21_negate(a, &c);
  ck_assert_int_eq(c.bits[0], b.bits[0]);
  ck_assert_int_eq(c.bits[1], b.bits[1]);
  ck_assert_int_eq(c.bits[2], b.bits[2]);
  ck_assert_int_eq(c.bits[3], b.bits[3]);
}

Suite *test_suite(void) {
  Suite *s;
  TCase *tc1_1;
  s = suite_create("Test");
  tc1_1 = tcase_create("\033[31mTEST\033[0m");
  tcase_add_test(tc1_1, add_simple);
  tcase_add_test(tc1_1, add_simple_2);
  tcase_add_test(tc1_1, add_with_dot);
  tcase_add_test(tc1_1, add_with_dot_2);
  tcase_add_test(tc1_1, add_zero);
  tcase_add_test(tc1_1, add_big_values_with_dot_overflow);
  tcase_add_test(tc1_1, add_big_values_overflow);
  tcase_add_test(tc1_1, add_big_values);
  tcase_add_test(tc1_1, add_to_sub);
  tcase_add_test(tc1_1, add_to_sub_2);
  tcase_add_test(tc1_1, add_big_values_2);

  tcase_add_test(tc1_1, s21_add_1);
  tcase_add_test(tc1_1, s21_add_2);
  tcase_add_test(tc1_1, s21_add_3);
  tcase_add_test(tc1_1, s21_add_4);
  tcase_add_test(tc1_1, s21_add_5);
  tcase_add_test(tc1_1, s21_add_6);
  tcase_add_test(tc1_1, s21_add_7);

  tcase_add_test(tc1_1, add_8);
  tcase_add_test(tc1_1, add_9);
  tcase_add_test(tc1_1, add_10);
  tcase_add_test(tc1_1, add_11);
  tcase_add_test(tc1_1, add_12);
  tcase_add_test(tc1_1, add_13);
  tcase_add_test(tc1_1, add_14);
  tcase_add_test(tc1_1, add_15);
  tcase_add_test(tc1_1, add_16);
  tcase_add_test(tc1_1, add_17);
  tcase_add_test(tc1_1, add_18);
  tcase_add_test(tc1_1, add_19);
  tcase_add_test(tc1_1, add_20);
  tcase_add_test(tc1_1, add_21);
  tcase_add_test(tc1_1, add_22);
  tcase_add_test(tc1_1, add_23);
  tcase_add_test(tc1_1, add_24);
  tcase_add_test(tc1_1, add_25);
  tcase_add_test(tc1_1, add_26);

  tcase_add_test(tc1_1, sub_simple);
  tcase_add_test(tc1_1, sub_simple_2);
  tcase_add_test(tc1_1, sub_simple_3);
  tcase_add_test(tc1_1, sub_simple_4);
  tcase_add_test(tc1_1, sub_with_dot);
  tcase_add_test(tc1_1, sub_with_dot_2);
  tcase_add_test(tc1_1, sub_to_add);
  tcase_add_test(tc1_1, sub_to_add_2);
  tcase_add_test(tc1_1, sub_big_values);

  tcase_add_test(tc1_1, s21_sub_1);
  tcase_add_test(tc1_1, s21_sub_2);
  tcase_add_test(tc1_1, s21_sub_3);
  tcase_add_test(tc1_1, s21_sub_4);
  tcase_add_test(tc1_1, s21_sub_5);
  tcase_add_test(tc1_1, s21_sub_6);
  tcase_add_test(tc1_1, s21_sub_7);

  tcase_add_test(tc1_1, sub_0);
  tcase_add_test(tc1_1, sub_1);
  tcase_add_test(tc1_1, sub_2);
  tcase_add_test(tc1_1, sub_3);
  tcase_add_test(tc1_1, sub_4);
  tcase_add_test(tc1_1, sub_5);
  tcase_add_test(tc1_1, sub_6);
  tcase_add_test(tc1_1, sub_7);
  tcase_add_test(tc1_1, sub_8);
  tcase_add_test(tc1_1, sub_9);
  tcase_add_test(tc1_1, sub_10);
  tcase_add_test(tc1_1, sub_11);
  tcase_add_test(tc1_1, sub_12);
  tcase_add_test(tc1_1, sub_13);
  tcase_add_test(tc1_1, sub_14);
  tcase_add_test(tc1_1, sub_15);
  tcase_add_test(tc1_1, sub_16);
  tcase_add_test(tc1_1, sub_17);
  tcase_add_test(tc1_1, sub_18);
  tcase_add_test(tc1_1, sub_19);

  tcase_add_test(tc1_1, mul_simple);
  tcase_add_test(tc1_1, mul_simple_2);
  tcase_add_test(tc1_1, mul_with_overflow);
  tcase_add_test(tc1_1, mul_fits);
  tcase_add_test(tc1_1, mul_with_overflow_2);
  tcase_add_test(tc1_1, mul_with_overflow_3);

  tcase_add_test(tc1_1, mul_0);
  tcase_add_test(tc1_1, mul_1);
  tcase_add_test(tc1_1, mul_2);
  tcase_add_test(tc1_1, mul_3);
  tcase_add_test(tc1_1, mul_4);
  tcase_add_test(tc1_1, mul_5);
  tcase_add_test(tc1_1, mul_6);
  tcase_add_test(tc1_1, mul_7);
  tcase_add_test(tc1_1, mul_8);
  tcase_add_test(tc1_1, mul_9);
  tcase_add_test(tc1_1, mul_10);
  tcase_add_test(tc1_1, mul_11);
  tcase_add_test(tc1_1, mul_12);
  tcase_add_test(tc1_1, mul_13);
  tcase_add_test(tc1_1, mul_14);

  tcase_add_test(tc1_1, div_simple);
  tcase_add_test(tc1_1, basic_div);

  tcase_add_test(tc1_1, int_to_decimal_INT32MAX);
  tcase_add_test(tc1_1, int_to_decimal_INT32MIN);
  tcase_add_test(tc1_1, int_to_decimal_0);
  tcase_add_test(tc1_1, int_to_decimal_minus);
  tcase_add_test(tc1_1, int_to_decimal_plus);
  tcase_add_test(tc1_1, int_to_decimal_5);
  tcase_add_test(tc1_1, int_to_decimal_1);

  tcase_add_test(tc1_1, is_equal_simple);
  tcase_add_test(tc1_1, is_equal_with_scale);
  tcase_add_test(tc1_1, is_equal_big_with_minus);

  tcase_add_test(tc1_1, is_not_equal_simple);
  tcase_add_test(tc1_1, is_not_equal_with_scale);
  tcase_add_test(tc1_1, is_not_equal_big_with_minus);

  tcase_add_test(tc1_1, is_greater);
  tcase_add_test(tc1_1, is_greater_with_scale);
  tcase_add_test(tc1_1, is_greater_with_scale_1);
  tcase_add_test(tc1_1, is_greater_big_with_minus);

  tcase_add_test(tc1_1, is_greater_or_equal);
  tcase_add_test(tc1_1, is_greater_or_equal_with_scale);
  tcase_add_test(tc1_1, is_greater_or_equal_with_scale_2);
  tcase_add_test(tc1_1, is_greater_or_equal_big_with_minus);
  tcase_add_test(tc1_1, is_less_or_equal);
  tcase_add_test(tc1_1, is_less_or_equal_with_scale);
  tcase_add_test(tc1_1, is_less_or_equal_with_scale_2);
  tcase_add_test(tc1_1, is_less_or_equal_big_with_minus);
  tcase_add_test(tc1_1, is_less);
  tcase_add_test(tc1_1, is_less_with_scale);
  tcase_add_test(tc1_1, is_less_with_scale_1);
  tcase_add_test(tc1_1, is_less_big_with_minus);
  tcase_add_test(tc1_1, truncate_0);
  tcase_add_test(tc1_1, truncate_1);
  tcase_add_test(tc1_1, truncate_2);
  tcase_add_test(tc1_1, truncate_3);
  tcase_add_test(tc1_1, truncate_4);
  tcase_add_test(tc1_1, truncate_0n);
  tcase_add_test(tc1_1, truncate_1n);
  tcase_add_test(tc1_1, truncate_2n);
  tcase_add_test(tc1_1, truncate_3n);
  tcase_add_test(tc1_1, truncate_4n);
  tcase_add_test(tc1_1, truncate_6n);
  tcase_add_test(tc1_1, truncate_7n);
  tcase_add_test(tc1_1, truncate_8n);
  tcase_add_test(tc1_1, truncate_9n);
  tcase_add_test(tc1_1, s21_trun_1);
  tcase_add_test(tc1_1, s21_trun_2);
  tcase_add_test(tc1_1, s21_trun_4);
  tcase_add_test(tc1_1, s21_truncate_1);
  tcase_add_test(tc1_1, s21_truncate_2);
  tcase_add_test(tc1_1, s21_truncate_3);
  tcase_add_test(tc1_1, s21_truncate_4);
  tcase_add_test(tc1_1, s21_truncate_6);
  tcase_add_test(tc1_1, s21_truncate_7);
  tcase_add_test(tc1_1, s21_truncate_8);
  tcase_add_test(tc1_1, s21_truncateTest1);
  tcase_add_test(tc1_1, s21_truncateTest2);
  tcase_add_test(tc1_1, s21_truncateTest3);
  tcase_add_test(tc1_1, s21_truncateTest4);
  tcase_add_test(tc1_1, s21_truncateTest5);
  tcase_add_test(tc1_1, s21_truncateTest6);
  tcase_add_test(tc1_1, s21_truncateTest7);
  tcase_add_test(tc1_1, s21_truncateTest8);
  tcase_add_test(tc1_1, s21_truncateTest9);
  tcase_add_test(tc1_1, s21_truncateTest10);
  tcase_add_test(tc1_1, s21_truncateTest11);
  tcase_add_test(tc1_1, floor_0);
  tcase_add_test(tc1_1, floor_1);
  tcase_add_test(tc1_1, floor_2);
  tcase_add_test(tc1_1, floor_3);
  tcase_add_test(tc1_1, floor_0n);
  tcase_add_test(tc1_1, floor_1n);
  tcase_add_test(tc1_1, floor_2n);
  tcase_add_test(tc1_1, floor_3n);
  tcase_add_test(tc1_1, floor_5n);
  tcase_add_test(tc1_1, floor_6n);
  tcase_add_test(tc1_1, floor_7n);
  tcase_add_test(tc1_1, floor_0);
  tcase_add_test(tc1_1, floor_1);
  tcase_add_test(tc1_1, floor_2);
  tcase_add_test(tc1_1, floor_3);
  tcase_add_test(tc1_1, round_0);
  tcase_add_test(tc1_1, round_1);
  tcase_add_test(tc1_1, round_2);
  tcase_add_test(tc1_1, round_3);
  tcase_add_test(tc1_1, round_4);
  tcase_add_test(tc1_1, round_5);
  tcase_add_test(tc1_1, round_6);
  tcase_add_test(tc1_1, round_7);
  tcase_add_test(tc1_1, round_8);
  tcase_add_test(tc1_1, round_9);
  tcase_add_test(tc1_1, round_11);
  tcase_add_test(tc1_1, round_12);
  tcase_add_test(tc1_1, round_13);
  tcase_add_test(tc1_1, round_14);
  tcase_add_test(tc1_1, round_15);
  tcase_add_test(tc1_1, round_16);
  tcase_add_test(tc1_1, negate_1);
  tcase_add_test(tc1_1, negate_2);
  tcase_add_test(tc1_1, negate_3);
  tcase_add_test(tc1_1, negate_4);
  suite_add_tcase(s, tc1_1);
  return s;
}
