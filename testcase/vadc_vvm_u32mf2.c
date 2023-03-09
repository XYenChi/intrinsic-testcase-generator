/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    76667248, 2043375464, 3706813711, 3862300385, 2229233441, 1882238687, 4051298042, 914967860, 3791237112, 980094223, 1969308001, 4190383760, 410981037, 2795949280, 3562712162, 2304217775
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3092471850, 4193656760, 331316471, 405359039, 1887150364, 2863900683, 2948057942, 2751910057, 3777026138, 2812216850, 449292497, 4014962192, 2801205048, 3350240920, 357460133, 3353222268
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    bool64_t masked[] = {
    1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2 (in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32mf2 (uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3169139099, 6237032225, 4038130182, 4267659424, 4116383806, 4746139371, 6999355985, 3666877918, 7568263251, 3792311074, 2418600499, 8205345952, 3212186085, 6146190200, 3920172295, 5657440043
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
