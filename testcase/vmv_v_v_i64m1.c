/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -7113059809272933285, -4902123177820700690, 3151276966754450231, -4560514241338620890, 1009509295302431605, 6915419573567262346, 740818952144369306, 6298645786524054699, 4955377890289270696, 8245899999651361852, 4784781631987922485, -7095737360223573973, 5082689658842809329, -8384247715773871382, -5471815045716095004, -8471751720507000740
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (in1, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_v_i64m1 (src, vl);
        void __riscv_vse64_v_i64m1 (int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    -7113059809272933285, -4902123177820700690, 3151276966754450231, -4560514241338620890, 1009509295302431605, 6915419573567262346, 740818952144369306, 6298645786524054699, 4955377890289270696, 8245899999651361852, 4784781631987922485, -7095737360223573973, 5082689658842809329, -8384247715773871382, -5471815045716095004, -8471751720507000740
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
