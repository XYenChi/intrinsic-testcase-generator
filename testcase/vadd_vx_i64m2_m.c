/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m2_t data1[] = {
    15584657346874924333, 17208348412601863297, 5818057415077755826, 429752804310788303
    };
    const vint64m2_t *in1 = &data1[0];
    vint64m2_t data2[] = {
    1814361529302726938, 3641734322933081455, 9204586197739640688, 644745957222388314
    };
    const vint64m2_t *in2 = &data2[0];
    vint64m2_t out_data[] = {
    13329897303064425223, 1524243649833895442, 14909980124257924149, 737247540750733206
    };
    vint64m2_t *out = &out_data[0];
    int masked[] = {
    1, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (int n = 4, Q_element = 64;n >= 0; n -= Q_element) {
        vint64m2_t out = __riscv_vadd_vx_i64m2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint64m2_t golden[] = {
    17399018876177651271, 20850082735534944752, 14909980124257924149, 737247540750733206
    };
    int fail = 0;
    for (int i = 0; i < 4; i++){
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
