/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1068918178, 501430521, 2797668481, 2338646394, 1877977878, 787110657, 3097218570, 2217878683, 3691055413, 3967509641, 3450702702, 1887649175, 4187249188, 351847088, 3906002270, 3045702536
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3801340306, 2493158581, 210358442, 261218623, 2778265829, 587122452, 3465718046, 1758340259, 1426188889, 423605133, 130691517, 2808717681, 1371435737, 2631252496, 2590846242, 468192188
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
        out_v = __riscv_vadc_vx_i32m8 (data1_v, data2_v, mask, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4870258484, 2994589102, 3008026923, 2599865017, 4656243707, 1374233109, 6562936616, 3976218942, 5117244302, 4391114774, 3581394219, 4696366856, 5558684925, 2983099584, 6496848512, 3513894724
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
