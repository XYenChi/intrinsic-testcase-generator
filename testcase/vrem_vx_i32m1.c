/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3868869267, 503663419, 1780118441, 527991790, 1982093044, 4196264996, 230576579, 2770541797, 1641096280, 445342834, 3707678551, 417147680, 1076360146, 2772176924, 4254754471, 2648989914
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1182932955, 4139238494, 2979260325, 631963403, 4261813056, 4202866994, 2443438991, 52643654, 1986873876, 983423144, 3763307324, 677461942, 3378970662, 2700601204, 2053348604, 3940580855
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1182932955, 109931142, 1199141884, 103971613, 297626968, 6601998, 137673201, 52643654, 345777596, 92737476, 55628773, 260314262, 149890224, 2700601204, 2053348604, 1291590941
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
