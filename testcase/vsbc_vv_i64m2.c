/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    14364833493352334931, 15069901789487459375, 5291180334009644222, 394623219842754443, 10687417552029008219, 1349489365461064060, 17728013915815518339, 10462734437758822790, 9847309441864652720, 2401777599437456903, 7476693276892902650, 3561695438734783795, 18154280955100353451, 12447932098106275166, 706994975698323275, 1763985168966692301
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    2304215693585542194, 9438498360031385870, 12223827523189685470, 12848225007856607803, 13284387229140811691, 9803506991488089431, 6385676168529080375, 5618606464962661784, 15736114720995789571, 9404602170845218294, 9743214204119544219, 13663146894377046277, 8500484878152305180, 10557788988090221717, 599571475234745484, 7291310225131591252
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
        out_v = __riscv_vsbc_vv_i64m2 (data1_v, data2_v, vl);
        void vint64m2_t __riscv_vse64_v_i64 (int64m2_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    12060617799766792737, 5631403429456073505, -6932647189180041248, -12453601788013853360, -2596969677111803472, -8454017626027025371, 11342337747286437964, 4844127972796161006, -5888805279131136851, -7002824571407761391, -2266520927226641569, -10101451455642262482, 9653796076948048271, 1890143110016053449, 107423500463577791, -5527325056164898951
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