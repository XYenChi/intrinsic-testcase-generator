/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -771665896, -1013628903, -1029721489, 1411047574, 730534595, 633256619, -92347523, -999191958, 1744081306, -1497367175, -1789903798, 267213515, -1957865591, 334936227, -538921235, 1911565217
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -510752235, -874862988, -1308833307, 1650369865, -2128822711, -2073238424, 326982218, 2109196476, 415713396, -254376282, 538953266, 797615209, -1563177630, 758489223, 380448963, -739153597
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u32m2 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    585271117, 411288366, -3127077888, 1633503743, 1176555963, 2411605646, -398996616, -1757231517, 2929447377, -1789475972, -1891136037, 603848182, 171276041, -1510347701, -1455930978, -204898509
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
