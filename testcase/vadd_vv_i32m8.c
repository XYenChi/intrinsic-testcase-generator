/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2235080976, 2447127561, 3889345979, 1077434843, 231727336, 3239486895, 2971492972, 1744121504, 47680304, 3369555572, 304662592, 3124680121, 878143563, 1404003274, 202394416, 1064287349
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1386159463, 1262726348, 3466668103, 1243751264, 2186188692, 904630582, 1750156782, 3361399543, 3962507809, 3707382597, 482575614, 2938002635, 3205100101, 1907132166, 833219831, 2822714132
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3621240439, 3709853909, 7356014082, 2321186107, 2417916028, 4144117477, 4721649754, 5105521047, 4010188113, 7076938169, 787238206, 6062682756, 4083243664, 3311135440, 1035614247, 3887001481
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
