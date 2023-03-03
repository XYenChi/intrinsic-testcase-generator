/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3324967401, 3970314757, 3765780691, 1536532205, 2208201438, 3465804165, 1751040457, 1249412215, 157445424, 655965285, 2596558491, 1804320723, 1711951850, 2614621179, 2830114512, 720697867
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1528459793, 640381922, 1890691472, 2528903689, 3846122445, 838097789, 2042800201, 1242798908, 3546097629, 1842304267, 433964501, 1863600629, 1490700952, 991277895, 1320589960, 3289320607
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
        out_v = __riscv_vsbc_vv_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1796507608, 3329932835, 1875089219, -992371484, -1637921007, 2627706376, -291759744, 6613307, -3388652205, -1186338982, 2162593990, -59279906, 221250898, 1623343284, 1509524552, -2568622740
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
