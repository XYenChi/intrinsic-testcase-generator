/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1880109945, 3418495890, 3204715985, 1301449250, 3431496030, 142375485, 4228300493, 2160276331, 1230429371, 914892608, 4064787918, 787165730, 1356716649, 4148936841, 185194227, 2382446373
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3330320351, 2819234152, 279561318, 3412848099, 4101866894, 3855779869, 3796237366, 2990586275, 2476456803, 3755107509, 1354390383, 35650707, 3692493462, 4199154231, 4193502096, 475799337
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    bool16_t masked[] = {
    0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2 (in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m2 (uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1880109945, 2819234152, 3204715985, 1301449250, 3431496030, 3855779869, 4228300493, 2160276331, 1230429371, 914892608, 1354390383, 35650707, 3692493462, 4199154231, 185194227, 475799337
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
