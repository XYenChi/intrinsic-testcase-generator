/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m1_t data1[] = {
    12085420334322121719, 4187701307787305887
    };
    const vint64m1_t *in1 = &data1[0];
    vint64m1_t data2[] = {
    14601742740486280742, 1369662723634324888
    };
    const vint64m1_t *in2 = &data2[0];
    vint64m1_t out_data[] = {
    13176605769097065460, 17557299589295670366
    };
    vint64m1_t *out = &out_data[0];
    int masked[] = {
    0, 1
    };
    const int *mask = &masked[0];
    for (int n = 2, Q_element = 64;n >= 0; n -= Q_element) {
        vint64m1_t out = __riscv_vadd_vv_i64m1_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint64m1_t golden[] = {
    13176605769097065460, 5557364031421630775
    };
    int fail = 0;
    for (int i = 0; i < 2; i++){
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
