/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1742120307, 170448080, 4072028728, 3335669345, 4220443644, 493279834, 3990079030, 2436515931, 1544204234, 675120466, 1904684810, 1384906145, 263619321, 3396481600, 3540952453, 2161548992
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1017103652, 3037494194, 601592911, 595960936, 2942199911, 2044252195, 621951712, 3052083240, 1399391721, 1566405799, 953213662, 2410603326, 3102184104, 3670893194, 1414810821, 1613875140
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    1260919462, 2170004678, 277786889, 3189050524, 3196812210, 3442210278, 3256205962, 1427200808, 1433362719, 1542106616, 1231018842, 3196421840, 869439933, 2609632008, 2294738562, 117345218
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1771916926473061164, 2170004678, 277786889, 3189050524, 3196812210, 1008388383403735630, 3256205962, 1427200808, 1433362719, 1057512612965982334, 1231018842, 3338459359334838270, 869439933, 2609632008, 5009777847150893913, 3488470182080858880
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
