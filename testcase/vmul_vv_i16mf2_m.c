/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    51000, 24976, 32959, 6783, 25310, 55820, 28165, 36241, 45508, 28724, 55729, 26247, 7777, 64613, 57576, 60547
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    16294, 43864, 35969, 35184, 53670, 6722, 12137, 34743, 39020, 39175, 40214, 24323, 63569, 13507, 34691, 46430
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    52863, 48259, 21042, 6108, 50734, 15064, 30863, 52482, 21226, 61994, 31456, 38933, 20269, 36134, 36294, 38379
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    52863, 48259, 21042, 238653072, 1358387700, 15064, 30863, 1259121063, 21226, 1125262700, 2241086006, 38933, 494376113, 872727791, 36294, 2811197210
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
