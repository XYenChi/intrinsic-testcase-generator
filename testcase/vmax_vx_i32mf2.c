/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2744713458, 180244493, 535981384, 2754572144, 3487279614, 2960441377, 16688700, 2727946565, 608803809, 214734245, 1204866822, 3146997572, 2536457063, 3400963241, 537899888, 2693469248
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    633223010, 2967699921, 1588127257, 1665880972, 509459432, 1990385730, 3751880821, 2472988705, 2429104217, 299114403, 1755054791, 1607596420, 4257579054, 2095669662, 906828331, 3490867547
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2744713458, 2967699921, 1588127257, 2754572144, 3487279614, 2960441377, 3751880821, 2727946565, 2429104217, 299114403, 1755054791, 3146997572, 4257579054, 3400963241, 906828331, 3490867547
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
