/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1081664189, 2188132995, 1406189587, 3716754278, 2281215536, 1965721913, 3133810072, 4041968981, 2698078933, 2732332216, 664552504, 4181887658, 999978150, 248032551, 107666689, 449593751
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    738974285, 4034813759, 102429907, 3745785029, 2112255088, 1144867852, 1434239624, 837358745, 1388447938, 1683704512, 4243406438, 3281532801, 696537034, 882652303, 2600631804, 2652852818
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    3908389681, 2378310368, 1711545606, 3090532731, 27822089, 1234287050, 2694410244, 1693206671, 4226623173, 104139891, 3796535385, 569021764, 3705472636, 302526348, 3335112536, 2047517971
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1820638475, 6222946755, 1508619495, 7462539308, 4393470624, 3110589766, 4568049697, 4879327727, 4086526871, 4416036728, 4907958942, 7463420459, 1696515185, 1130684855, 2708298494, 3102446569
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
