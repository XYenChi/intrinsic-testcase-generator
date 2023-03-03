/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    24274, 22143, 21074, 28643, 55866, 11220, 37072, 40595, 47347, 12936, 54432, 56518, 57831, 34921, 1739, 62899
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    45863, 31941, 37545, 44697, 10332, 60389, 1832, 30886, 54829, 39189, 31104, 36671, 64683, 56692, 46009, 13127
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    16963, 45188, 41915, 16957, 23876, 17231, 4516, 38341, 56756, 51358, 11999, 36472, 3558, 63271, 11324, 18822
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -21589, -9799, -16472, -16054, 45533, -49169, 35239, 9708, -7482, -26254, 23328, 19846, -6853, -21772, -44271, 49772
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
