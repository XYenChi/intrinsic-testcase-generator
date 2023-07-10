/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    57376, 36008, 62687, 60698, 6341, 63222, 34457, 28560, 53292, 3588, 35668, 39061, 53024, 33083, 9053, 48745
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    34327, 23583, 28283, 31825, 8858, 54842, 29188, 44109, 6200, 29638, 65066, 52395, 51911, 38431, 14790, 11514
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16mf4_t data1_v = __riscv_vle16_v_u16mf4 (in1, vl);
    vuint16mf4_t data2_v = __riscv_vle16_v_u16mf4 (in2, vl);
    vuint16mf4_t out_v = __riscv_vle16_v_u16mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vv_u16mf4(op1, op2, vl);
        void __riscv_vse16_v_u16mf4 (uint16_t *out, vuint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    26167, 59591, 25434, 26987, 15199, 52528, 63645, 7133, 59492, 33226, 35198, 25920, 39399, 5978, 23843, 60259
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
/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    10091, 5012, 63138, 40400, 58514, 8653, 16411, 23336, 11415, 9872, 48660, 17553, 44386, 36322, 50973, 12062
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    39311, 22045, 13728, 8272, 12977, 33296, 55729, 32678, 9194, 30361, 25790, 40384, 48839, 46311, 35719, 62348
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16mf4_t data1_v = __riscv_vle16_v_u16mf4 (in1, vl);
    vuint16mf4_t data2_v = __riscv_vle16_v_u16mf4 (in2, vl);
    vuint16mf4_t out_v = __riscv_vle16_v_u16mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16mf4 (uint16_t *out, vuint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    49402, 27057, 11330, 48672, 5955, 41949, 6604, 56014, 20609, 40233, 8914, 57937, 27689, 17097, 21156, 8874
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
