/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    12976, 60639, 42467, 27360, 22877, 864, 11995, 53372, 44305, 14733, 37754, 27373, 59814, 35009, 25694, 10197
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    35779, 11450, 29025, 48115, 60199, 30691, 45425, 3352, 57792, 60506, 10911, 65032, 38527, 44984, 18610, 46017
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    41159, 52762, 23773, 8169, 4623, 29395, 26989, 44135, 15476, 3738, 4557, 58760, 46547, 56314, 54789, 23460
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    41159, 60639, 42467, 48115, 60199, 29395, 26989, 44135, 15476, 60506, 4557, 58760, 46547, 44984, 54789, 23460
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
