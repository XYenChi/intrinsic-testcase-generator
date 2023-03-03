/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    949336606, 3184144775, 2064116039, 1218768535, 3723181944, 894391689, 4173722990, 3784644127, 3511977875, 1697810373, 862261435, 3811211676, 2004784751, 1636986286, 3894586586, 3207267595
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3874980865, 2030875881, 1032903294, 2031901415, 3046355539, 365437760, 1326437768, 2323976594, 2027663191, 3742345682, 3459921085, 1157108410, 815929650, 664755865, 2197980626, 1964685441
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    1173815018, 3024792799, 722149542, 2708941509, 454420452, 1726502958, 3969617669, 491906161, 3062408354, 2359862425, 1326866565, 3653383576, 1092504756, 3693096088, 557944926, 4271864594
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1173815018, 1153268894, 722149542, -813132880, 676826405, 528953929, 2847285222, 491906161, 3062408354, 2359862425, -2597659650, 3653383576, 1188855101, 3693096088, 1696605960, 4271864594
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
