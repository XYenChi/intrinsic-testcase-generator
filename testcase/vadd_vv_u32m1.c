/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    487762527, 1603720153, 2440724207, 430940050, 3409049364, 1643989956, 3498246598, 3994430542, 2956661032, 20280541, 1524638520, 99960521, 2635033387, 2042741352, 2451559092, 2204628227
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    3262245250, 350153961, 3570556781, 3326624382, 1787488801, 3316735287, 4057300917, 3764317833, 924817421, 2395203474, 3419696029, 430482905, 1741627352, 1402079141, 3307104744, 3030028655
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
		out = __riscv_vadd_vv_u32m1(op1, op2, vl);
        void __riscv_vse32_v_u32m1 (uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    3750007777, 1953874114, 1716313692, 3757564432, 901570869, 665757947, 3260580219, 3463781079, 3881478453, 2415484015, 649367253, 530443426, 81693443, 3444820493, 1463696540, 939689586
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
    3955888646, 4272701251, 3833054714, 1166976357, 1734810060, 3117999382, 408325812, 584084458, 1566945753, 3230120614, 2112847280, 38942727, 1741616743, 627487541, 1013417703, 1643111401
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    2155140422, 203541378, 230978478, 4094537159, 2564766033, 3919556438, 3710996924, 2623302611, 507007370, 210974036, 544510712, 3928650701, 1222452855, 321278234, 483779587, 2591753179
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
    1816061772, 181275333, 4064033192, 966546220, 4608797, 2742588524, 4119322736, 3207387069, 2073953123, 3441094650, 2657357992, 3967593428, 2964069598, 948765775, 1497197290, 4234864580
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
