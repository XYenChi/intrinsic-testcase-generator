/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3519783226, 136190409, 4112046669, 929779309, 2412419157, 2583859402, 2803635543, 1588281600, 1647044926, 880171475, 567437685, 1623825849, 2668674096, 2380508112, 778584984, 1364576285
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1837679715, 2668983557, 2431711666, 2887400546, 1339362112, 1971507710, 3762587364, 1860072388, 581901311, 3368348290, 57650421, 2975050164, 3441390551, 2706725814, 4155361441, 3063611789
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
        out_v = __riscv_vsbc_vx_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1682103511, -2532793148, 1680335003, -1957621237, 1073057045, 612351692, -958951821, -271790788, 1065143615, -2488176815, 509787264, -1351224315, -772716455, -326217702, -3376776457, -1699035504
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
