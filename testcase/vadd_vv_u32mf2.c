/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    1958290126, 3800666191, 4278308887, 1376166912, 3512477314, 1864040596, 153145226, 404574379, 725789018, 3855265033, 3274748856, 2208094175, 3020933252, 2523018348, 3592149019, 1610671975
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    3350831096, 3804241161, 2373155797, 2741895423, 2418034897, 2465949631, 396149882, 1543506984, 4260679327, 1885300652, 1084603472, 1577381930, 2266099072, 1894074290, 532952655, 3776500395
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2 (in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_u32mf2 (in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vv_u32mf2(op1, op2, vl);
        void __riscv_vse32_v_u32mf2 (uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    1014153926, 3309940056, 2356497388, 4118062335, 1635544915, 35022931, 549295108, 1948081363, 691501049, 1445598389, 64385032, 3785476105, 992065028, 122125342, 4125101674, 1092205074
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
    2698528481, 75920114, 3130319306, 1853286573, 552741312, 28363863, 1620876048, 2813710808, 2140703631, 2253630908, 3324820575, 515174976, 2718075953, 1275474837, 4291510892, 2969363429
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    2261779245, 4145852730, 3816662870, 3273970318, 273522564, 2461467115, 175549150, 419787396, 2437476656, 388746252, 2371628052, 2686081897, 3992594385, 1967384422, 4055117502, 1335335962
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2 (in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_u32mf2 (in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32mf2 (uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    665340430, 4221772844, 2652014880, 832289595, 826263876, 2489830978, 1796425198, 3233498204, 283212991, 2642377160, 1401481331, 3201256873, 2415703042, 3242859259, 4051661098, 9732095
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
