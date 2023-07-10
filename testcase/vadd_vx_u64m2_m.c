/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    13531509344126332401, 15372846083577919931, 17686374700523818526, 17576461958834655314, 13159306199580408075, 1540145359352069175, 8711850362165652391, 16121087382564469535, 18401512798691893259, 9558089143723127871, 18140332974918948894, 14432437094492073348, 8717802321902394147, 12137141151777531487, 9508389569280724058, 9426807791587049381
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    10697282186371163415, 6276262595797397905, 161629849616297359, 12382297993207561137, 3190072235326645967, 12904110556073209626, 17397452554383307994, 14407969833994380990, 8976271809682588052, 15693750291654515503, 14387097771388073820, 15307925387147014063, 13823649133679830819, 6470726137964065027, 15183471077350359373, 1208928156615700554
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const uint out_data[] = {
    0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0
    };
    const uint64_t *out = &out_data[0];
    uint32_t masked[] = {
    1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0
    };
    const uint32_t *mask = &masked[0];
    vuint64m2_t data1_v = __riscv_vle64_v_u64m2 (in1, vl);
    vuint64m2_t data2_v = __riscv_vle64_v_u64m2 (in2, vl);
    vuint64m2_t out_v = __riscv_vle64_v_u64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m2 (uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    5782047456787944200, 1, 1, 1, 0, 0, 0, 12082313142849298909, 1, 0, 14080686672597471098, 11293618407929535795, 4094707381872673350, 1, 0, 0
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
