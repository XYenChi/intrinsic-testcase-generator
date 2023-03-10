/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -6700306248286708543, -1643208073864317815, -2901538416041789651, -9181938249385346619, -4639342655846359565, -1960009076770380019, -309272947155550805, -1898451947570291485, 3351191363887101920, -8756687707885666072, -4738110302860916036, -2587253585284941225, -778378212708641033, 3249044174401725809, -7841110967552763346, -4448046641337378793
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    4883937235977942914, -6869069260945827485, -8215454742215034892, -6020526170705898643, -5944602839618220406, 4671590372800092588, 4661142690057530000, 967380994348280939, 6271567452580450778, 5858466877117462887, 4234872058008680709, -8361423821555988000, -7877350732955904079, -64604598097872839, 5538534261211417256, -8748841871441301747
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    bool32_t masked[] = {
    1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    4883937235977942914, -1643208073864317815, -8215454742215034892, -9181938249385346619, -5944602839618220406, -1960009076770380019, 4661142690057530000, -1898451947570291485, 6271567452580450778, -8756687707885666072, -4738110302860916036, -8361423821555988000, -7877350732955904079, -64604598097872839, -7841110967552763346, -4448046641337378793
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
