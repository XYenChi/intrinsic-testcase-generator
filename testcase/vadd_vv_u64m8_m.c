/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    4098584283255509773, 15620235915662513511, 5888873990336738000, 4768612787125665650, 13574307977052540403, 13171989202125396056, 5416463483504452199, 7221451502648185405, 14659275495101943093, 2049346934061577646, 7401691923508887570, 9699404045492971551, 9665956713709764164, 11802616669065959586, 15463424712459252405, 11870495430516865588
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    9365109013462372572, 2839403885585712748, 6323607021211011464, 10384965169983444846, 4041049063744900280, 17899095511472172559, 4492204482779230757, 16733031747981405452, 3321123633616524517, 11665193289579401451, 11766185038637369815, 5664222903255430667, 6455480563582008114, 850544797794502252, 9878537486110523574, 2590509571043677715
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const uint out_data[] = {
    0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1
    };
    const uint64_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1
    };
    const uint8_t *mask = &masked[0];
    vuint64m8_t data1_v = __riscv_vle64_v_u64m8 (in1, vl);
    vuint64m8_t data2_v = __riscv_vle64_v_u64m8 (in2, vl);
    vuint64m8_t out_v = __riscv_vle64_v_u64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m8 (uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    13463693296717882345, 1, 12212481011547749464, 1, 17615357040797440683, 0, 9908667966283682956, 5507739176920039241, 17980399128718467610, 13714540223640979097, 0, 1, 0, 12653161466860461838, 6895218124860224363, 14461005001560543303
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
