/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2896431704, 148043644, 1591984238, 2490314954, 2406373558, 2794883190, 640218694, 458580180, 4275765166, 3605859673, 2892416056, 310451646, 1518153466, 2938388056, 3788115651, 2667408740
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1077925198, 4014249570, 2091207704, 1849721079, 3984074760, 2033200053, 1400264159, 86905743, 2036395449, 2315712115, 3416036845, 3784751960, 775809481, 2285112942, 3790764590, 3036346764
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    158231783, 3230712251, 346898370, 1611490284, 2545446760, 883441812, 4094355597, 2361689191, 2682238442, 1989593963, 4230417044, 1086940731, 67899697, 2526490632, 2889349064, 3559654068
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3974356902, 4162293214, 3683191942, 4340036033, 6390448318, 4828083244, 2040482854, 545485923, 6312160616, 5921571788, 6308452902, 4095203607, 2293962948, 5223500999, 7578880241, 5703755505
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
