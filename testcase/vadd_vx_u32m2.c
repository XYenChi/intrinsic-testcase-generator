/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    1358230038, 874230735, 2400654558, 1625645406, 1867271111, 1533351671, 1973696280, 2030600950, 2515644577, 195325758, 4293736391, 1391115457, 3184437264, 3623300307, 284987046, 3494769794
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    2405835761, 1674561822, 2373190268, 2391631851, 2236306798, 951846927, 3281325494, 714695630, 1366904025, 2097495378, 3497554068, 4035848279, 2505600076, 2087692294, 386529650, 518548585
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2 (in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_u32m2 (in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vx_u32m2(op1, op2, vl);
        void __riscv_vse32_v_u32m2 (uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    3764065799, 2548792557, 478877530, 4017277257, 4103577909, 2485198598, 960054478, 2745296580, 3882548602, 2292821136, 3496323163, 1131996440, 1395070044, 1416025305, 671516696, 4013318379
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
    1280004341, 3712302670, 4251256278, 242864552, 555529476, 3310491256, 1798211902, 3909052272, 63365403, 2496911815, 1936766762, 259444180, 233769169, 3914605587, 1010169694, 247724272
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    2462544531, 2310675206, 1672635950, 1430888318, 3471851650, 1584794172, 494447751, 1582178178, 3449490138, 2078398568, 3860167235, 2351114532, 252680557, 247018822, 538619293, 1626756262
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2 (in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_u32m2 (in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m2 (uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    3742548872, 1728010580, 1628924932, 1673752870, 4027381126, 600318132, 2292659653, 1196263154, 3512855541, 280343087, 1501966701, 2610558712, 486449726, 4161624409, 1548788987, 1874480534
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
