/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    710626885, 4141912203, 3640991796, 2543174075, 3222329890, 2025131036, 1010578976, 3234661830, 3383842875, 2396558029, 2538987854, 2669960782, 3290332601, 915873518, 2124391020, 1024370208
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3264210701, 505917359, 2979286349, 2523745089, 1180757821, 3257453549, 3515831949, 1905747680, 2509950571, 3876104900, 1179862348, 3463064858, 3345352018, 4042391741, 3893197592, 2677100499
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    1897382874, 172919084, 1493207966, 2595694112, 170017232, 760169921, 1880282370, 2245203207, 2768228237, 3769692825, 483554867, 4034966456, 3200865669, 171410849, 1325990495, 1627695095
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1897382874, 172919084, 3640991796, 2543174075, 3222329890, 3257453549, 1880282370, 2245203207, 3383842875, 3876104900, 2538987854, 4034966456, 3200865669, 4042391741, 3893197592, 2677100499
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
