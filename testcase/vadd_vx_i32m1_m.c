/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    396963652, 1260424182, 1453185822, 1208889864, 2943318043, 317909808, 1401479330, 2500325937, 1698510045, 870668984, 1991408286, 256701235, 148649665, 1332427905, 3213161986, 4045872771
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2672318138, 2335363039, 3887305181, 1410895525, 1727932395, 4024070106, 2427946993, 927630008, 1409097768, 1900638089, 3937573736, 1678934853, 3351441349, 3964455637, 3307779703, 1091323609
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    3945664491, 218752238, 239781664, 4199674732, 1673515154, 3305941821, 2282070777, 2747091799, 3980820242, 1469257555, 615863509, 545875810, 607269634, 1136013344, 3780658753, 1650107759
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3069281790, 3595787221, 5340491003, 2619785389, 1673515154, 3305941821, 3829426323, 3427955945, 3980820242, 1469257555, 5928982022, 545875810, 607269634, 1136013344, 6520941689, 1650107759
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
