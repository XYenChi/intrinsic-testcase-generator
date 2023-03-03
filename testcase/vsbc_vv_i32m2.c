/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    556620773, 3322169665, 3759201320, 297486852, 1344627929, 3655726800, 1228609036, 215366354, 554867080, 1599316989, 774414676, 2359272231, 1061438914, 3149878136, 3115474064, 1664197211
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3310255285, 1485209247, 3475656314, 3923418925, 584140404, 3209144110, 1576378669, 3812261626, 579572849, 4096599169, 3683279563, 874167196, 2709171010, 1195799032, 2226808811, 1230411352
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -2753634512, 1836960418, 283545006, -3625932073, 760487525, 446582690, -347769633, -3596895272, -24705769, -2497282180, -2908864887, 1485105035, -1647732096, 1954079104, 888665253, 433785859
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
