/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2395631594, 3324316072, 1129468113, 3415101370, 403969937, 910506031, 4138279632, 1714171224, 1552025943, 2659388079, 1069843630, 2939477295, 223530054, 4164098896, 1097385206, 952712173
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1074013961, 2557452960, 2857620299, 3776455853, 1212732199, 1941836168, 2429647044, 1066810549, 1170333107, 531400548, 2969614288, 2528049749, 3040414275, 1559394290, 2753005526, 3005587795
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    3286524203, 3218261727, 2933192735, 45858183, 4234087924, 1937308530, 60628715, 2699523348, 1574587230, 3984696675, 1048773219, 2267538085, 1514316254, 1377751501, 2124234289, 3035859966
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3286524203, 3218261727, 3227591006782025787, 12896979557324818610, 489907350027901463, 1937308530, 10054558875134207808, 1828695944555441976, 1574587230, 3984696675, 1048773219, 2267538085, 679623967073120850, 6493472041417703840, 2124234289, 2863460079316728535
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
