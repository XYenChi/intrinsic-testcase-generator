/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    809601830, 740627530, 1986023008, 2235366343, 868061027, 2679829141, 1006596710, 2234048327, 809481646, 406160572, 1354409750, 1103539939, 1008721354, 3308599203, 3652031635, 1296199149
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1142696277, 3222659590, 1335166924, 446034777, 206213102, 3014978071, 955869720, 2681030080, 262465648, 3809186550, 3121399711, 2774142832, 3130639301, 1729736666, 2457071449, 518405281
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    2389726301, 2389449668, 1069312930, 3272735733, 4003949415, 1962331572, 53765396, 1419847479, 617644931, 2621367923, 2663249383, 2370564552, 814890121, 1767281918, 1877127509, 891756979
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1, 2389449668, 1069312930, 0, 0, 1962331572, 0, 1419847479, 0, 9, 2, 2370564552, 3, 1767281918, 1877127509, 0
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
