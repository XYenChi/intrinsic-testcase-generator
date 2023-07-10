/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    2390317395, 4128735891, 2899340799, 1556636322, 3504368713, 2583913405, 3719610011, 2426392639, 2424263207, 373089434, 280397584, 3146473362, 2793323088, 99450077, 2646591367, 314145169
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    1816199123, 1988229004, 1794677899, 1818045234, 2061400206, 559707264, 725031269, 1266095599, 341390724, 3081842785, 320791699, 1282924968, 1120007221, 3129849966, 2932446716, 3883056930
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1 (in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_u32m1 (in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vx_u32m1(op1, op2, vl);
        void __riscv_vse32_v_u32m1 (uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    4206516518, 1821997599, 399051402, 3374681556, 1270801623, 3143620669, 149673984, 3692488238, 2765653931, 3454932219, 601189283, 134431034, 3913330309, 3229300043, 1284070787, 4197202099
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
    const uint32_t data1[] = {
    1603686966, 2425338978, 3255834553, 3477718847, 970533688, 247908484, 3029253089, 4133422259, 4074529495, 2707594461, 2462954349, 1535206577, 93035240, 1809636900, 3230846227, 3938644528
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    3987563977, 3664916978, 1381623667, 97946631, 4281758804, 316274037, 2149640961, 1594045314, 2237628881, 3278278875, 151714889, 3412987378, 795148185, 2179144812, 2646983510, 3440602884
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1 (in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_u32m1 (in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m1 (uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    1296283647, 1795288660, 342490924, 3575665478, 957325196, 564182521, 883926754, 1432500277, 2017191080, 1690906040, 2614669238, 653226659, 888183425, 3988781712, 1582862441, 3084280116
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
