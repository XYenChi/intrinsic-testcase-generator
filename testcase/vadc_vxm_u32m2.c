/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    439352314, 1012610792, 2391455400, 2531425407, 1378544199, 2053981964, 1520851130, 2227044674, 4065584125, 4111396890, 191001431, 2874168410, 2038399511, 617467282, 1478440795, 2687825593
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2689387080, 3267080413, 1400546164, 1110817078, 3523558171, 1080533297, 466518284, 4192944695, 1437420090, 2583018130, 4207476431, 505247122, 2337706883, 2646738643, 2933412824, 1711461585
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    bool16_t masked[] = {
    0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2 (in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m2 (uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3128739394, 4279691205, 3792001565, 3642242485, 4902102370, 3134515262, 1987369414, 6419989369, 5503004215, 6694415020, 4398477863, 3379415532, 4376106394, 3264205926, 4411853619, 4399287178
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
