/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    809254642, 917892601, 693980846, 3251582891, 416154076, 932354516, 3210538954, 2934621358, 1299717019, 95798873, 3115758843, 3905842611, 3400385772, 911857604, 1518659113, 380131401
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2647036981, 680591500, 1883262396, 1362412559, 4267545008, 1584794812, 3784276945, 790467764, 1007848011, 2500303471, 1606531536, 2428938486, 3409055773, 1094905980, 297184091, 1907238237
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    2555227388, 2717691953, 2735567096, 3667231516, 974022647, 3665558973, 2048591970, 658696352, 240858715, 1913238566, 3356532192, 2920745229, 1406729409, 3240815543, 226397337, 1890104340
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3456291623, 1598484101, 2577243242, 4613995450, 4683699084, 2517149328, 6994815899, 3725089122, 2307565030, 1913238566, 3356532192, 2920745229, 6809441545, 3240815543, 1815843204, 1890104340
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
