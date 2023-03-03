/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1809691456, 4089932137, 1232985656, 3296837219, 541015985, 1596424565, 2481244334, 2216409648, 2350251780, 4214283658, 3250915062, 1688890480, 1745949428, 1864241187, 3541535, 775710627
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3787835001, 212882067, 2926350957, 1408074199, 2104693287, 638881336, 1639694951, 3183013430, 2815970787, 2493258776, 472728378, 3516604880, 3940646371, 543981576, 3039357561, 1709341493
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    1730107457, 1899561478, 1513639779, 344085887, 4202299947, 2309893679, 2688775676, 433411593, 4003242461, 2753212263, 1984307664, 2715657761, 4151621173, 4187561417, 1653303941, 1980916485
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1730107457, 1899561478, 1513639779, 344085887, 2104693287, 2309893679, 1639694951, 433411593, 2815970787, 2493258776, 1984307664, 2715657761, 3940646371, 543981576, 1653303941, 1709341493
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
