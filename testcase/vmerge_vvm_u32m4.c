/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1471504143, 3573036306, 3684108984, 2988838769, 3535717878, 566399564, 1702150480, 2126564292, 4265458271, 2554736307, 4131431655, 2760421445, 4148994657, 3758604801, 378445117, 2739244614
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1856464970, 4250445168, 3951207003, 2679254141, 1880425148, 4058604204, 560245852, 4062942010, 3979209413, 3590850083, 1062905516, 3151003872, 1114538515, 4111812087, 3968777797, 2480947344
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    bool8_t masked[] = {
    0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4 (in1, vl);
    vuint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m4 (uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1471504143, 4250445168, 3951207003, 2988838769, 1880425148, 566399564, 560245852, 2126564292, 3979209413, 3590850083, 4131431655, 3151003872, 4148994657, 4111812087, 3968777797, 2480947344
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
