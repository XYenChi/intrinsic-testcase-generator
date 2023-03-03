/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    109827233, 1022528840, 1839910395, 1333498818, 434239923, 1633871245, 3030048496, 1248928996, 596868379, 1112396282, 587182917, 1498212736, 2137926080, 3437262274, 926624856, 456054857
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3824213251, 2257215372, 2583742933, 1999255057, 1781044139, 963923793, 2575943675, 1768418750, 2380364055, 2138724584, 3917413422, 2751702862, 237523309, 729525555, 405936289, 537686598
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    420002759759264483, 2308067815961328480, 4753855480434488535, 2666004255390022626, 773400469778961297, 1574927367754032285, 7805234258214462800, 2208629453945075000, 1420764034937716845, 2379109275463596688, 2300238240224911974, 4122636273536050432, 507807276918998720, 2507570668120412070, 376150655339799384, 245214584561706486
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
