/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    617842918, 2872313525, 4288312160, 2064666650, 3018850217, 2175834904, 460712943, 2798326293, 2153913349, 4108687286, 2064211741, 1689526182, 663549077, 3348979108, 1258214936, 392981714
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2173255789, 834196976, 2858866918, 3006883505, 3778824727, 4286610029, 2418051547, 2889289348, 904982575, 3804771947, 739992785, 1396604028, 1837889222, 1948083690, 1029096662, 1410779615
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
        out_v = __riscv_vmul_vv_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1342730698236152302, 2396075256678900400, 12259713768281122880, 6208212093208608250, 11407705847108915759, 9326955720934652216, 1114027644544072821, 8085174350593226964, 1949254048904893675, 15632618124768365842, 1527501795052288685, 2359599071192661096, 1219529696886348094, 6524091578445548520, 1294824790716143632, 554410591178960110
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
