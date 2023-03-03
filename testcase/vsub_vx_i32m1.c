/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2824961154, 3399834851, 2593601771, 1987977775, 1774959788, 166435979, 240332530, 564937114, 155156676, 434547611, 650503712, 4141133081, 501416694, 3819524858, 2561441144, 796718852
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    515734391, 2991758460, 1022678975, 2298852658, 2310548842, 1483525152, 3117944322, 1111839, 2369962835, 3791217838, 294866489, 3930736232, 2023211442, 91287053, 2671675373, 2119565504
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2309226763, 408076391, 1570922796, -310874883, -535589054, -1317089173, -2877611792, 563825275, -2214806159, -3356670227, 355637223, 210396849, -1521794748, 3728237805, -110234229, -1322846652
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
