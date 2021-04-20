#include <stdio.h>

#define x 0.1

float sum_first_method(int depth, float prev_f, float sum, int i) {
  i++;
  sum += prev_f;
  prev_f = prev_f * x * x * (2 * i - 3) / (2 * i - 1);

  if (depth + 1 != i) {
    sum = sum_first_method(depth, prev_f, sum, i);
  }
  return sum;
}

float sum_second_method(float prev_f, float* sum, int i) {
  if (i > 1) {
    prev_f = sum_second_method(prev_f, sum, i - 1);
    prev_f = prev_f * x * x * (2 * i - 3)/(2 * i - 1);
    *sum += prev_f;
  }
  else {
    *sum = prev_f;
  }
  return prev_f;
}

float sum_third_method(int depth, float prev_f, float sum, int i) {
  float temp_f = prev_f;
  if (depth > i) {
    i++;
    prev_f = prev_f * x * x * (2 * i - 3) / (2 * i - 1);
    sum = sum_third_method(depth, prev_f, sum, i);
  }
  return sum += temp_f;
}

int main() {
  float F = x;

  int n = 1; // Given natural number n
  printf("Input n: ");
  scanf("%d", &n);

  float first_sum = 0;
  float second_sum = 0;
  float third_sum = 0;

  first_sum = sum_first_method(n, F, first_sum, 1);
  sum_second_method(F, &second_sum, n);
  third_sum = sum_third_method(n, F, third_sum, 1);

  printf("Sum using first method: %0.10f\n", first_sum);
  printf("Sum using second method: %0.10f\n", second_sum);
  printf("Sum using third method: %0.10f\n", third_sum);
}