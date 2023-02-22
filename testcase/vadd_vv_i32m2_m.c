/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m2_t data1[] = {
    3804275833, 1878386024, 2860449140, 2311957041, 4001890565, 2270941005, 1334625028, 976555134
    };
    const vint32m2_t *in1 = &data1[0];
    vint32m2_t data2[] = {
    574619899, 3982522681, 383588370, 789766741, 2201329788, 2286221317, 4210057740, 2605202079
    };
    const vint32m2_t *in2 = &data2[0];
    vint32m2_t out_data[] = {
    42805524, 3595642817, 3913182196, 457505596, 3537476270, 4165799495, 1728131404, 2347145618
    };
    vint32m2_t *out = &out_data[0];
    int masked[] = {
    1, 0, 1, 0, 0, 1, 1, 0
    };
    const int *mask = &masked[0];
    for (int n = 8, Q_element = 32;n >= 0; n -= Q_element) {
        vint32m2_t out = __riscv_vadd_vv_i32m2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint32m2_t golden[] = {
    4378895732, 3595642817, 3244037510, 457505596, 3537476270, 4557162322, 5544682768, 2347145618
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
