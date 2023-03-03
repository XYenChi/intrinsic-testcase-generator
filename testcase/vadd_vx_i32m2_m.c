/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4271427696, 1611439300, 2820558598, 2326262599, 587626477, 2899940614, 1077630780, 4113241286, 1484934273, 3190519799, 2437794647, 4127606926, 555767270, 111093070, 2619171266, 3920247653
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3950715774, 3476911718, 553703541, 373844818, 1047010289, 396008693, 3231549681, 1681803689, 264635507, 2381739040, 3434363241, 3519726666, 2948685292, 933427665, 3740597786, 2482465944
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    780218596, 3710378301, 1225169120, 403705759, 3752574266, 2252617892, 3440015628, 2735414076, 430947619, 3058883147, 1231754404, 4213939865, 218010204, 751538353, 1075681339, 3937500845
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    8222143470, 3710378301, 3374262139, 403705759, 3752574266, 3295949307, 4309180461, 2735414076, 430947619, 5572258839, 5872157888, 7647333592, 3504452562, 1044520735, 6359769052, 3937500845
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
