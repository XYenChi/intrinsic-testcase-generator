/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -654188823, 209387309, -1954048804, 453057625, 1291513324, 1953267158, -704854782, 20392881, 1303768194, -1243073305, 315250726, -1662728858, 1886208563, -1597546507, -182657024, 2038052692
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1549687504, -1539411372, 619517182, 23007916, -1339490797, 54043222, 530242735, 554390841, -790381117, 1490639443, -937144387, 418639460, 2013122719, 353183492, 111983563, -1772644047
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vx_i32m2(op1, op2, vl);
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    895498681, 2964943233, 2960435674, 476065541, 4246989823, 2007310380, 4120355249, 574783722, 513387077, 247566138, 3673073635, 3050877898, 3899331282, 3050604281, 4224293835, 265408645
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
    -347110106, 1490769388, 895559919, -41919097, 1671933711, 2032193520, -1621356858, -593362920, -1822514537, -2146011622, 425198870, -1668743399, 2008192135, -641117357, -1894502342, -2078705979
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -2143281095, 1336474441, -1507606109, 1034145191, -1796114212, -2046611903, -796572586, -144162476, -501368753, -436966737, 382623958, 34413434, -1165387119, -1172038208, -1071061434, -1560368682
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1804576095, 2827243829, 3682921106, 992226094, 4170786795, 4280548913, 1877037852, 3557441900, 1971084006, 1711988937, 807822828, 2660637331, 842805016, 2481811731, 1329403520, 655892635
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
