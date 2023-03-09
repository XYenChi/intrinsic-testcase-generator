/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3623214660, 1550251086, 930696505, 2146794138, 1353564476, 3287603315, 360925195, 772423910, 3904805662, 3395919352, 4165400779, 2296526150, 2590055808, 1554409247, 3503913937, 3816195690
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    984659497, 535231803, 1223671991, 1325036107, 3548907776, 3648489269, 504848770, 1943972816, 1122327418, 3201758611, 1797491724, 737961908, 1435485810, 1131672577, 460962080, 2020524416
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    bool16_t masked[] = {
    1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0
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
    4607874158, 2085482890, 2154368496, 3471830246, 4902472253, 6936092584, 865773966, 2716396726, 5027133081, 6597677963, 5962892503, 3034488059, 4025541618, 2686081824, 3964876018, 5836720106
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
