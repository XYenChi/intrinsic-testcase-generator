/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m2_t data1[] = {
    1508263678, 79157386, 2905408413, 852825251, 189181353, 3564710349, 1980331480, 1053573447
    };
    const vint32m2_t *in1 = &data1[0];
    vint32m2_t data2[] = {
    3930715075, 329810588, 4204073620, 511567378, 2090807082, 3334743858, 2272423069, 3283349655
    };
    const vint32m2_t *in2 = &data2[0];
    vint32m2_t out_data[] = {
    103725509, 2820021795, 1558712836, 3266986833, 3834990547, 4246443419, 3016332728, 3920423124
    };
    vint32m2_t *out = &out_data[0];
    int masked[] = {
    0, 0, 1, 1, 1, 1, 1, 1
    };
    const int *mask = &masked[0];
    for (int n = 8, Q_element = 32;n >= 0; n -= Q_element) {
        vint32m2_t out = __riscv_vadd_vx_i32m2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint32m2_t golden[] = {
    103725509, 2820021795, 7109482033, 1364392629, 2279988435, 6899454207, 4252754549, 4336923102
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
