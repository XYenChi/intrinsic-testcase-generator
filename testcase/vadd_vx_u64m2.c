/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    1176602007699442469, -8606596532534608379, -1142487705090590184, -5104054999178004562, 915440623657926226, -6178713042327955122, 8070544688873807905, -8077959789477072079, 8102999158858713919, -8721200613380054261, 9104592473099752476, 6715672261364765517, -8912459687555730614, 7969967498646209227, 3346110071762023343, 2941452293037971068
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -8044602884029208367, -7457631474384641405, 4866717889356364973, 5941610850390367582, -927491246885650926, -3596873792532334158, -8402320739230447083, 4737430177031391494, -6065832371497476886, 4929333195430498966, -8604073354594675336, 8600853021857988272, 6579767068407202299, -5034581629404707932, 2922557214026532885, -8970719218690356998
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (*in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (*in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u64m2 (data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    10357119837056181203, -6079917836332840459, 611059877246471238, -2394355255209087518, -4600468326515983919, -3034254081612979212, 7061332868462433863, -14988821764445472721, 13922580271781039266, -2483462678688182940, 7229202840684842033, 11184718542115778447, -27050124224830508, 1828277637301361447, 4348718662497189395, 10092770317725361199
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
