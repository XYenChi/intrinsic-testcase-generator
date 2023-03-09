/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2656205951, 3900866626, 2379853683, 3659137023, 2649327435, 677615470, 116267855, 3479270278, 902861629, 3353360053, 1113598012, 421058932, 4066389119, 1514036489, 1958026197, 2508665942
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    530521177, 2327348387, 934606214, 3046371731, 2872703844, 1970282935, 4130996322, 624119302, 1494106216, 3485328066, 924369463, 2681606210, 651424899, 1667906043, 2837150339, 3176462384
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    bool64_t masked[] = {
    1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2 (in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32mf2 (uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    530521177, 3900866626, 2379853683, 3659137023, 2649327435, 1970282935, 4130996322, 624119302, 1494106216, 3353360053, 924369463, 421058932, 651424899, 1667906043, 1958026197, 2508665942
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
