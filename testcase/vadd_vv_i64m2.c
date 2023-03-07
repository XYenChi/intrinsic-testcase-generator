/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -2587043411261592283, 4085184582862793175, 8808178832764171623, 2838523980621539086, 1782675586463182065, 5025382288004171045, -9125810504022164186, 3162891343830370009, 4774899841347901505, 2780825067987976436, -4545628872598413738, 256937590246575427, -6502862752474047061, 5482698905230617005, -7743195713452329390, -7588805600222190872
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    3369297540138714749, 3568146732587997693, 3402871399115306057, -7343519282719838419, 9185371482283172152, -3692032752705810900, 1556140377095687034, -6165069711541518337, 2555718466482729159, -7004250761394174664, 8353187125785146075, -7536954477093701853, -1997419652341640124, -4181982408609660850, 1116518241981346539, -7410581306417277691
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (*in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (*in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i64m2 (data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    5736367744075675502, 4597949819303149441, 1023262503187130385, 4997267954536300637, 2081518631257031350, 7164553920186167994, -16691261707588118004, 8343209753739403415, 3402050510145342317, 440196228153884994, -1146245800727761801, 3921701978764638245, -8309513307616152986, 2046218552626560508, -13631159455271492777, -1507011629154976035
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
