/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    444029730, 194863837, 111679200, -1461427277, -868832944, 512652321, 235135743, -998805312, -1248651782, -762811165, 1597036185, 688420037, -1133507230, -1030550839, 917057, 1134467294
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1209312006, -1244630871, 1551115959, -431689762, 1662912917, 976144190, 2007892643, 2088923164, 1266913088, 626846624, 2117949783, -2000238520, -495993892, -1310226995, 2077448291, -374323243
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vx_i32m8(op1, op2, vl);
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1653341736, 3245200262, 1662795159, 2401850257, 794079973, 1488796511, 2243028386, 1090117852, 18261306, 4159002755, 3714985968, 2983148813, 2665466174, 1954189462, 2078365348, 760144051
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
    -1080729745, 1719235491, -1347725384, -2007332811, 233907618, -917288307, -1436022315, -693001146, -550250902, 1636027912, -1451917207, -902733550, -2091927452, 1894779642, -881051679, 993531029
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1572470031, 1085350553, 1822340775, 1207757729, 1289115957, -1111076786, 1640465724, 821478353, -975336966, 973558329, 425414464, -353951081, 1952898398, -1136211532, 707280337, 2109821469
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1641767520, 2804586044, 474615391, 3495392214, 1523023575, 2266602203, 204443409, 128477207, 2769379428, 2609586241, 3268464553, 3038282665, 4155938242, 758568110, 4121195954, 3103352498
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
