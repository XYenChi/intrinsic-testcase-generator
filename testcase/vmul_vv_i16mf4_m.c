/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    45064, 46530, 41829, 65117, 46317, 53300, 55389, 54466, 21586, 49689, 25922, 2310, 39224, 59051, 3363, 28639
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    52925, 9559, 3456, 45206, 58134, 24511, 53976, 47375, 51781, 6755, 14075, 12312, 53999, 33294, 30090, 39468
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    30743, 22262, 4697, 48875, 5874, 58439, 30719, 56570, 60506, 48895, 36599, 56619, 29611, 31570, 59487, 30778
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    2385012200, 444780270, 4697, 48875, 5874, 1306436300, 2989676664, 56570, 1117744666, 48895, 364852150, 28440720, 29611, 1966043994, 101192670, 1130324052
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
