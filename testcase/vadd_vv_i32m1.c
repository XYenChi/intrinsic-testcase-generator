/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1293992831, 1550351334, 1868958376, -1366715931, 895232667, 983715001, -1068666571, -698413117, 1828909781, -1131174792, -408664268, -839368842, -770866852, 187876438, -133859181, 1640794164
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    387462392, 202422264, 1676752747, 2100353871, -449214129, -2016761252, 1436172591, 1780789445, 855236008, -2043572302, -764959465, -31567706, 968020018, -877325828, -2122019212, -1264362313
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m1 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    275802825, 3612305355, 545859945, -1936390019, 941667813, 295749517, -1119756879, 694980772, 1605043128, -2128881568, -1206488089, -1138556701, 731444940, 1875148952, 1552087337, 2249165302
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
