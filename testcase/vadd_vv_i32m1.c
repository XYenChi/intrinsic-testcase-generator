/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    99495955, 1750008077, -1603125052, 1038987519, 956495267, 53119267, 714408085, -1428746186, 651354610, 688386950, 1598180651, -1735096420, 1973576657, -1250857301, 772941078, 986428401
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    479896244, 408527600, 1650966101, 1206611116, 124028234, -355422191, 1981099372, 279182506, 1031313570, 1108603275, 190312564, -1184957369, 2040132577, 26379406, 1535713988, 111916548
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vv_i32m1(op1, op2, vl);
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    579392199, 2158535677, 47841049, 2245598635, 1080523501, 3992664372, 2695507457, 3145403616, 1682668180, 1796990225, 1788493215, 1374913507, 4013709234, 3070489401, 2308655066, 1098344949
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
    -1367641945, -415657831, 2060513953, -2143347438, 1536141147, 1181612261, 154208370, 1335935201, -635895194, 412426280, 1056715415, -676386173, 1017842901, 286484147, 613119654, 1295013769
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    769963962, -949044576, -501609475, -792469083, 1780337656, 916526436, 846539383, -713174167, 1647676782, -647239877, 1727174655, -1549344140, 1513304078, 429734800, 277105445, 2058910741
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3697289313, 2930264889, 1558904478, 1359150775, 3316478803, 2098138697, 1000747753, 622761034, 1011781588, 4060153699, 2783890070, 2069236983, 2531146979, 716218947, 890225099, 3353924510
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
