/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1865669499, 1082126280, 818940267, 2199936452, 1797114492, 3737020101, 4276645489, 2807940435, 2657148289, 4089008183, 3322869021, 4118393176, 1930972617, 3991134880, 103716724, 92388029
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    409834800, 922984033, 1652214765, 102755897, 2586556105, 4270333980, 1028164987, 3334596986, 2842126589, 2563973084, 282844110, 1500165008, 1192861295, 735797288, 53736048, 4078338653
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    bool4_t masked[] = {
    1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i32m8 (data1_v, data2_v, size_t vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    409834800, 922984033, 818940267, 102755897, 2586556105, 4270333980, 1028164987, 2807940435, 2842126589, 4089008183, 282844110, 1500165008, 1192861295, 735797288, 53736048, 4078338653
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
