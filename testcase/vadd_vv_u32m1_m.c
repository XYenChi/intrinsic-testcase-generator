/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    493542272, 204871327, -531589875, -1245128624, -258621497, 2131727119, 1759918428, -716136570, 1110280867, -145055507, 495939576, 1200812532, -1346868730, -672273161, 386798847, -1806302374
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1039207493, -2087066980, 945337841, 391564434, -1326077021, -1859467439, -280438542, -2143525737, 1434996870, -1405820331, -242562965, 2119295859, 1520260566, -1934209265, -1536540083, -2056252575
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int out_data[] = {
    -1355299865, 964275609, 484821941, 1563222881, 2067105461, 783397172, -662282913, 860098894, -32689140, 1158202019, -563839389, -495853192, -1242127178, 2008018835, -1856896059, 1827861644
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u32m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (bool32_t mask, int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -1355299864, 964275609, 484821942, 1563222882, 2067105462, 783397173, -662282912, 860098894, -32689140, 1158202020, -563839388, -495853191, -1242127178, 2008018836, -1856896059, 1827861644
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
