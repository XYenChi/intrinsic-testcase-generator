/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1965766714, 861779979, -403751496, -856208207, 998215327, 693129678, -1295039966, -791517572, 1988391290, 2137089964, -5061342, -251000638, -698386530, 1608467456, -890278116, -1701296930
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1634997142, -1549637929, -390585704, 1615682679, -709685548, -1702726392, 1718440009, 2101994408, -129163423, 381554939, -677976930, -41694840, 1637250677, -339744689, -578924287, -1514121780
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vv_i32m4(op1, op2, vl);
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    694203440, 3607109346, 3500630096, 759474472, 288529779, 3285370582, 423400043, 1310476836, 1859227867, 2518644903, 3611929024, 4002271818, 938864147, 1268722767, 2825764893, 1079548586
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
    const int32_t data1[] = {
    -1432132050, -2065023785, 436485625, -148467310, -1322203130, -1050804281, -1178623076, -1207721720, -552608571, 830546180, 280511246, -1249198686, -339698010, 1103126643, 987347075, -975217714
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2016175719, -456440315, 1168005476, -1745874035, -1859991358, -281844888, -896758707, -1300986286, 991728614, -1189944625, -395954464, 750112908, -1715371255, 1947395554, 1065336074, -2096749810
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    584043669, 1773503196, 1604491101, 2400625951, 1112772808, 2962318127, 2219585513, 1786259290, 439120043, 3935568851, 4179524078, 3795881518, 2239898031, 3050522197, 2052683149, 1222999772
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
