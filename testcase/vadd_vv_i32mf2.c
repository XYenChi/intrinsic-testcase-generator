/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1285025739, 1817079170, -886216823, 390825637, 1822075514, -647907259, -1625764922, 1587961785, -900894552, -2056942825, 1889869886, 1181583006, -909342370, 1253857025, -1181293472, 763776197
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -742027946, 164138055, -317817779, 1902749668, -2035448691, -1442940424, 1132650460, -869790369, 665123405, -1896392490, -1203406545, 402936585, 703987530, -1808075889, -1205802095, 1325242064
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
		out = __riscv_vadd_vv_i32mf2(op1, op2, vl);
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    542997793, 1981217225, 3090932694, 2293575305, 4081594119, 2204119613, 3801852834, 718171416, 4059196149, 341631981, 686463341, 1584519591, 4089612456, 3740748432, 1907871729, 2089018261
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
    -284594915, -2143492323, 1985491489, -12015782, -2068696499, 6433618, 1020600594, 211961719, -1856214395, 1295899111, -346046748, 2055403696, 860730827, -264221247, -1366820793, 1003186496
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1677791723, -2029509471, -513312914, -1604655103, -1175368961, 1570760930, -1554171729, 755525378, -252956240, -320325794, -160397807, 1400169286, -1127787713, -1302783965, 79618325, 606029197
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
    2332580658, 121965502, 1472178575, 2678296411, 1050901836, 1577194548, 3761396161, 967487097, 2185796661, 975573317, 3788522741, 3455572982, 4027910410, 2727962084, 3007764828, 1609215693
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
