/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -368847348, 1355564087, -122437436, -660886390, 1297337806, -833512251, -949099249, 409747838, 1895408934, -513465379, 1006573517, 1442066169, -604076908, -697346127, 1145247680, -28196662
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1199950880, 312693192, -1056956772, 1090385586, -1878137981, -688747718, -216646534, 744512825, -847570701, -165953842, -324255425, -1787526803, -514995966, 1910786961, -1072273986, -1457485401
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m4 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -896206992, 44391680, 941145494, 1149108311, 943100484, -2188321557, -1641542328, -592431091, 1288122051, -569221169, -39235718, -169453955, -423990624, -918394318, 2833906262, -1483539668
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
