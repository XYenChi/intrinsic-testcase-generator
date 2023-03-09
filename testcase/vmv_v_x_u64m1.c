/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    11271635448286576997, 18089181630000899257, 3819799493988401159, 4998050784336098705, 6977121559119714304, 12868930509289812016, 425271184309999378, 12717389448880125097, 3166015646208469348, 11936849415221146279, 10130533021062762529, 2266247212862452736, 14914011937910171824, 6599960748124972769, 9514421044609002991, 8248530848949353256
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vuint64m1_t data1_v = __riscv_vle64_v_u64m1 (in1, vl);
    vuint64m1_t out_v = __riscv_vle64_v_u64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_x_u64m1 (src, vl);
        void __riscv_vse64_v_u64m1 (uint64_t *out, vuint64m1_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    11271635448286576997, 18089181630000899257, 3819799493988401159, 4998050784336098705, 6977121559119714304, 12868930509289812016, 425271184309999378, 12717389448880125097, 3166015646208469348, 11936849415221146279, 10130533021062762529, 2266247212862452736, 14914011937910171824, 6599960748124972769, 9514421044609002991, 8248530848949353256
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
