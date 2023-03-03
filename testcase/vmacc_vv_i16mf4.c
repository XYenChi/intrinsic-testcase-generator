/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    13911, 23438, 58006, 65048, 55957, 37997, 48869, 37337, 41955, 63495, 17729, 62690, 32914, 62423, 50895, 50862
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    42745, 51748, 35680, 39950, 17214, 33673, 38773, 11576, 56718, 36943, 5566, 1621, 19002, 11301, 21110, 35247
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (*in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (*in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (*out, vl);
    const int out_data[] = {
    57573, 15817, 10888, 19853, 27280, 35569, 49654, 3017, 18548, 39794, 10724, 25531, 18145, 16387, 31901, 57103
    };
    const int16_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i16mf4 (data1_v, data2_v, vl);
        void vint16mf4_t __riscv_vse16_v_i16 (int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    594683268, 1212885441, 2069664968, 2598687453, 963271078, 1279508550, 1894847391, 432216129, 2379622238, 2345735579, 98690338, 101646021, 625449973, 705458710, 1074425351, 1792790017
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
