/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m2_t data1[] = {
    3667607731400676359, 2423963511803505202, 2701706292181064579, 5679025824865595622
    };
    const vint64m2_t *in1 = &data1[0];
    vint64m2_t data2[] = {
    10200698479959524875, 7237141670317838744, 8466581505591823166, 17219123397210301913
    };
    const vint64m2_t *in2 = &data2[0];
    vint64m2_t out_data[] = {
    616013451453672822, 17065262880592571703, 11356078079789110847, 5403140020295585781
    };
    vint64m2_t *out = &out_data[0];
    int masked[] = {
    0, 0, 1, 0
    };
    const int *mask = &masked[0];
    for (int n = 4, Q_element = 64;n >= 0; n -= Q_element) {
        vint64m2_t out = __riscv_vadd_vv_i64m2_m (, mask, data1, data264);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
        mask += Q_element;
      }
    vint64m2_t golden[] = {
    616013451453672822, 17065262880592571703, 11168287797772887745, 5403140020295585781
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
