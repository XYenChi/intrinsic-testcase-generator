/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <riscv_vector.h>
int main(){
    int data1[] = {
  
  };
  const int *in1 = &data1[0];
    int data2[] = {
  
  const int *in2 = &data2[0];
  int out_data[64];
  int *out = &out_data[0];
  for (int n = 64, Q_element = 4;n >= 0; n -= Q_element) {
    vint['8m1', '8m2', '8m4', '8m8', '8mf2', '8mf4', '8mf8', '16m1', '16m2', '16m4', '16m8', '16mf2', '16mf4', '32m1', '32m2', '32m4', '32m8', '32mf2', '64m1', '64m2', '64m4', '64m8']_t out = __riscv_vadd_v['v', 'x']_i['8m1', '8m2', '8m4', '8m8', '8mf2', '8mf4', '8mf8', '16m1', '16m2', '16m4', '16m8', '16mf2', '16mf4', '32m1', '32m2', '32m4', '32m8', '32mf2', '64m1', '64m2', '64m4', '64m8'] (data1, data2);
    in1 += Q_element;
    out += Q_element;
  }
  int golden[] = {
  
  };
  int fail = 0;
  for (int i = 0; i < 64; ++i)
     if (golden0[i] != out0_data[i]) {
       printf ("idx=%d golden=%d out=%d\n", i, golden0[i], out0[i]);
       fail++;
     }
  if (fail) {
    printf("FAIL\n");
    return 1;
  } else {
    printf("PASS\n");
    return 0;
  }
}
