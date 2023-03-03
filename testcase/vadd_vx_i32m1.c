/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    207550392, 1703502125, 1324367299, 2351494573, 164353403, 2209885673, 2873844281, 1815532283, 2363554541, 1944162911, 3733151302, 3194428890, 1205549096, 3989697228, 4149527439, 3063722429
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    828097936, 3318591508, 1894597505, 3445816011, 3863483652, 1175666660, 1926223572, 3518391186, 1981268785, 3377467731, 481854412, 3174688240, 1315482808, 22907467, 3201478072, 2567412598
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1035648328, 5022093633, 3218964804, 5797310584, 4027837055, 3385552333, 4800067853, 5333923469, 4344823326, 5321630642, 4215005714, 6369117130, 2521031904, 4012604695, 7351005511, 5631135027
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
