/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1068505786, -1912390079, 2023931200, -1337236809, 881248684, 790109298, -549265091, 1906111186, 77230865, -589453545, -57883488, 1058450411, 263420150, -1705939474, 799770015, 475901183
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    992229289, 2044752559, -374325973, -587816547, -1842530609, -963037129, -1733818120, -1096440504, 1254542741, -41840634, 784675588, 763526461, 1356177589, 1840772730, -1429408824, -865950024
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int out_data[] = {
    -700090830, -631434303, -1006633685, -1412047401, -1824961202, -1243159925, 1289072051, -1889628614, -1665995292, -168970515, -819644033, -577459489, 550191349, -718679952, -1079921762, -2028549630
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (bool32_t mask, int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -700090829, -631434302, -1006633685, -1412047400, -1824961202, -1243159924, 1289072051, -1889628613, -1665995292, -168970515, -819644032, -577459489, 550191350, -718679952, -1079921762, -2028549629
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
