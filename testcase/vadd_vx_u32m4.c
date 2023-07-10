/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    3677097169, 3593905076, 4166944471, 1422204101, 1367632728, 549147255, 2923440914, 3655235707, 1986277404, 1344290025, 246376278, 2843035560, 1883376732, 4140407424, 688940001, 378953009
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    3210385198, 3669779516, 2418784606, 4274799943, 2605540962, 4248103720, 462411084, 2194405054, 3427547798, 1202423160, 1665558347, 3543219391, 3643957120, 230810215, 2136298000, 373728414
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4 (in1, vl);
    vuint32m4_t data2_v = __riscv_vle32_v_u32m4 (in2, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vx_u32m4(op1, op2, vl);
        void __riscv_vse32_v_u32m4 (uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    2592515071, 2968717296, 2290761781, 1402036748, 3973173690, 502283679, 3385851998, 1554673465, 1118857906, 2546713185, 1911934625, 2091287655, 1232366556, 76250343, 2825238001, 752681423
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
    1359849309, 1320120198, 1836840738, 1516227084, 1271846917, 1870637478, 4214951630, 2946997686, 1012600704, 4108806659, 1332412490, 3481144713, 1979775148, 788584207, 1581280748, 1307244226
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    3215947511, 1473578363, 2693455594, 2089336685, 1770734652, 1470734672, 1989963953, 3642261935, 2244584804, 3073890623, 3443718586, 2294810594, 1891415572, 2945869849, 2885737406, 2961498366
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4 (in1, vl);
    vuint32m4_t data2_v = __riscv_vle32_v_u32m4 (in2, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m4 (uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    280829524, 2793698561, 235329036, 3605563769, 3042581569, 3341372150, 1909948287, 2294292325, 3257185508, 2887729986, 481163780, 1480988011, 3871190720, 3734454056, 172050858, 4268742592
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
