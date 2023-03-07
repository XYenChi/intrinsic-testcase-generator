/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1876430649, 1365050162, 2024401942, 880141420, 850933708, -1809800412, -275448217, -1675032321, -971337293, -775643871, 1680258349, -123251118, 2133047355, -795484092, 665528954, -257930346
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    155637925, -1354713707, -1493638747, 106059064, 1271781347, 858027655, -1230006121, 355993329, -1091879753, 1255563681, 1585889103, 581088527, -609799517, 1995362639, 1751068576, -1393818611
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u32m2 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -2245861199, 2821933914, 3529184315, 2871737873, -128112648, -3075739791, -817804806, -840823817, -2856133015, -542509832, 809140756, -1889481036, 3586423330, -1234755369, 964267886, 1157659136
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
