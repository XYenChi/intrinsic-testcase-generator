/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m2_t data1[] = {
    47051593, 1327734860, 627962301, 2312489263, 4004252777, 3699671791, 3253770961, 2459746717
    };
    const vint32m2_t *in1 = &data1[0];
    vint32m2_t data2[] = {
    694899797, 3523345592, 3411637552, 1532480336, 3242415362, 1984923457, 3267147155, 2389260530
    };
    const vint32m2_t *in2 = &data2[0];
    vint32m2_t out_data[64];
    vint32m2_t *out = &out_data[0];
    for (int n = 8, Q_element = 32;n >= 0; n -= Q_element) {
        vint32m2_t out = __riscv_vadd_vv_i32m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32m2_t golden[] = {
    741951390, 4851080452, 4039599853, 3844969599, 7246668139, 5684595248, 6520918116, 4849007247
    };
    int fail = 0;
    for (int i = 0; i < 8; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
