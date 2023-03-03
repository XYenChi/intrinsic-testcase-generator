/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2355142071, 2842278816, 1686909511, 3003331064, 2381232110, 2888345427, 859050744, 1656717761, 3120719082, 422338395, 3036048839, 708014668, 4236801535, 508664740, 4130685715, 2115282008
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1893036438, 2343846440, 3681438173, 1025226948, 3574944449, 1348757445, 1197773686, 4179799732, 2979057951, 1413825644, 3198161963, 2522310286, 795800995, 549603618, 2169791190, 749442593
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    2499494502, 3386437716, 2889535231, 3512521459, 3580613477, 679417121, 446091856, 2107390165, 2035067619, 2208709615, 3594799839, 2800011065, 3086372368, 549314007, 1382059008, 2841909375
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    5886664657893393642, 9625200181890224257, 4874384463543482042, 10549264810781302376, 8526271784931146471, 1962391334465855668, 383215540789140864, 3491350715712220565, 6350874351773605758, 932822873820167926, 10913987877633336922, 1982448904582301420, 13076347186323984880, 279416666549013181, 5708851401632670720, 6011439769304025000
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
