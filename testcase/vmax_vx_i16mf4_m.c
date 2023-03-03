/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    29510, 5309, 21909, 11134, 55119, 47946, 52273, 1005, 5661, 18868, 48620, 34791, 16557, 47951, 19074, 23070
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    28702, 14956, 34233, 53216, 28950, 52770, 27343, 62341, 17739, 52958, 51887, 57912, 52467, 13528, 47445, 54039
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    17395, 18604, 31944, 40041, 58449, 57689, 19378, 2499, 11529, 30093, 60522, 8413, 42125, 63247, 24143, 63458
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    17395, 18604, 31944, 53216, 55119, 57689, 19378, 2499, 17739, 52958, 60522, 8413, 52467, 47951, 47445, 63458
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
