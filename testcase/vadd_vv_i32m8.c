/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    937667713, -750106752, -601649603, 139895913, 19189934, 586733958, 2071268669, 1944418321, -1468168528, 2103924144, 479994038, -1374437075, -41174333, -609172593, 579231952, 979490770
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1248072289, 1571728548, -2119325570, 1260007940, -1193223263, 1016506720, -891069721, -1735482682, 386871694, -427655538, -208615988, 622518948, 1429936031, -686074801, -392309899, 1685151933
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m8 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    228612759, -1700722939, 342336329, -129738741, 917806010, 489493646, 3301529191, 2451164501, -2056975656, 1883142990, -468137200, -2045741724, 1265060873, 460246314, -914088759, -882245664
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
