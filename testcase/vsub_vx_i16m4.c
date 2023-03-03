/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    54377, 24444, 49959, 60990, 42751, 59273, 60223, 49794, 22142, 17352, 58871, 38005, 13541, 33611, 34166, 42371
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    46429, 25973, 11947, 2230, 22955, 43747, 33486, 53937, 15360, 7902, 19446, 41834, 7217, 30023, 18761, 47091
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4 (*in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4 (*in2, vl);
    vint16m4_t out_v = __riscv_vle16_v_i16m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u16m4 (data1_v, data2_v, vl);
        void vint16m4_t __riscv_vse16_v_i16 (int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    7948, -1529, 38012, 58760, 19796, 15526, 26737, -4143, 6782, 9450, 39425, -3829, 6324, 3588, 15405, -4720
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
