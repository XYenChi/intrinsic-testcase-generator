/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    11109640322442154451, 14192386153780022877, 2372690775936866819, 5007935903804820278, 6801081613784652829, 18027198821958597885, 4714832757462448878, 662051030313524078, 7311670065862156314, 6166105948114517446, 5536827260156558782, 6503976262819722597, 9673275710775957302, 6621610840935612827, 6719794172184401443, 1166943485543311127
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    11566620581767186677, 6309873487800682596, 11340060890029356415, 803622658192791990, 15864235631520714012, 2996318149021602534, 8640056572614588513, 15228438522695190819, 7728271215436119859, 15245562898445660014, 8286448219339344376, 15004491393699762994, 7257157835138158998, 6586047905774639247, 15225094027701825685, 17075078013846426756
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m2(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (*in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (*in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i64m2 (data1_v, data2_v, vl);
        void vint64m2_t __riscv_vse64_v_i64 (int64m2_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    1, 0, 4, 0, 2, 0, 1, 23, 1, 2, 1, 2, 0, 0, 2, 14
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
