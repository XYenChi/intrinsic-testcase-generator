/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1806676039, -940647829, 256283128, -732698821, 301216419, -1351566248, 1993200669, 621136266, -9175381, -1665623187, 635874620, -47003156, -743796592, -11947138, 218253964, 304671833
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1378215125, -263227661, 1152586739, 2144425947, -1162869472, -86271721, 1505851683, 1159757594, -1273026948, 1113411997, 2054200163, -477616730, -162540086, 1734782754, 1638938054, 1206424665
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vx_i32mf2(op1, op2, vl);
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1110076132, 3091091806, 1408869867, 1411727126, 3433314243, 2857129327, 3499052352, 1780893860, 3012764967, 3742756106, 2690074783, 3770347410, 3388630618, 1722835616, 1857192018, 1511096498
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
    -387174612, -998585620, -1923823682, -1174629994, 1725752909, -1498652331, -1621828754, -1059044790, -772804084, -369672794, -522681638, 1588333299, 1804245503, -166569412, -1119907711, 1834721061
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    677639512, 1211632085, 1260692741, 2084408068, -1306322530, -1836833728, 1280411698, -468907960, 491052011, -217164120, -590950254, -1825885839, 1442911266, -245084128, 1294176731, 1029658877
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    290464900, 213046465, 3631836355, 909778074, 419430379, 959481237, 3953550240, 2767014546, 4013215223, 3708130382, 3181335404, 4057414756, 3247156769, 3883313756, 174269020, 2864379938
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
