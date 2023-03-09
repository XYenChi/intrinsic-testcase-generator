/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -4127921, 1568610768, -1507537356, -160723826, 472503729, 86469041, -1654019151, 981212193, 742006873, -1938701684, 1906359045, -816631315, -1256208747, 40312240, -1769094217, 1827672475
    };
    const int32_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int out_data[] = {
    874901573, 935691906, 709644314, 1868265475, -832845836, -255181663, -1964383269, 184071896, 125526542, 1191555064, 216152748, 56959538, -308286870, 401101336, -1184864774, 42410172
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, in1, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_32m4 (mask, data1_v, vl);
        void __riscv_vse32_v_i32m4 (bool32_t mask, int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4127921, -1568610768, 1507537356, 160723826, -472503729, -86469041, 1654019151, -981212193, -742006873, 1938701684, -1906359045, 816631315, 1256208747, -40312240, 1769094217, -1827672475
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
