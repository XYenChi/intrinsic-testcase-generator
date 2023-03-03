/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3940925896, 1821647714, 2822863522, 3387796883, 585020136, 3700118644, 551127565, 3313525183, 1548432626, 1110825032, 3807043079, 1763948411, 3366725267, 579290066, 508539550, 3857913436
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3160042435, 4057629818, 675127508, 4175768187, 2547824374, 2340132047, 95729492, 3133827775, 1532441857, 3778451993, 2063765726, 1735797625, 3902031424, 1570070010, 691240085, 1606211576
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
        out_v = __riscv_vmin_vx_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3940925896, 4057629818, 2822863522, 4175768187, 2547824374, 3700118644, 551127565, 3313525183, 1548432626, 3778451993, 3807043079, 1763948411, 3902031424, 1570070010, 691240085, 3857913436
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
