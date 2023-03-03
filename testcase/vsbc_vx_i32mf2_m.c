/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3411609103, 1165247390, 2280177640, 2014089067, 2139276710, 531263045, 819644227, 1634591984, 730227390, 1407498130, 3777128753, 3933909619, 732994459, 4095262770, 3621766281, 1576766213
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2862981503, 3298486827, 2258841824, 1976251108, 3487120346, 4228508593, 849959064, 3881598158, 3191911695, 3192516649, 2788034519, 414299788, 4008823956, 2241128826, 409684568, 1522489305
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    1826459026, 883136070, 3015101267, 4266356730, 2361138311, 4205048364, 2156789563, 2467783503, 3570852449, 3016686562, 2563751685, 4244238145, 3759793828, 1399267047, 2451736274, 1358638328
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    548627600, -2133239438, 21335815, 37837959, -1347843636, -3697245549, -30314837, -2247006175, -2461684305, -1785018520, 989094233, 3519609831, -3275829498, 1854133943, 3212081712, 54276907
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
