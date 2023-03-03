/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    40236, 64541, 34958, 26246, 8517, 59354, 18827, 6692, 44965, 13165, 51417, 5137, 27165, 21754, 43362, 34495
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    64773, 6003, 12538, 582, 65242, 18705, 20218, 8084, 51702, 40703, 10396, 32160, 61351, 29698, 50282, 46494
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    11382, 4527, 8825, 8577, 24957, 40797, 60865, 28866, 3465, 62480, 16039, 19033, 64159, 23043, 60414, 65188
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    457966152, 292177108, 308504350, 225111943, 212558770, 2421465139, 1145905355, 193171272, 155803725, 822549200, 824677263, 97772521, 1742879235, 501277422, 2619671868, 2248660061
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
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
