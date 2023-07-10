/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2049283247, -2123720038, -1224197048, 1471560260, 956516228, 789757767, 797052142, -1415163497, 1089453522, -163259497, 935948771, -17200284, 1071118818, -1291742830, -1001080285, -532293690
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    65662639, 843997625, -1529707635, 528284821, 784261645, 486989888, 611032690, 1023326536, -1482499656, 1697894915, -1631333406, -829327196, 33595511, -1163555263, -28947880, 291507385
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
		out = __riscv_vadd_vv_i32m8(op1, op2, vl);
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2114945886, 3015244883, 1541062613, 1999845081, 1740777873, 1276747655, 1408084832, 3903130335, 3901921162, 1534635418, 3599582661, 3448439816, 1104714329, 1839669203, 3264939131, 4054180991
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
    794754258, 1223219647, -525930893, 1357855728, -1629206009, -798137646, 1507993227, -1682004705, 697462402, 1706584819, 386734932, 923974101, -797899476, 1729792259, -139302446, 1498174075
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    701433425, -1704200583, 630593163, 1403078220, 556063593, 1343084494, -75385346, -803096901, 956546750, -424784417, 827306877, -552374645, 302691548, -1090889879, -1168972542, 871720732
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
    1496187683, 3813986360, 104662270, 2760933948, 3221824880, 544946848, 1432607881, 1809865690, 1654009152, 1281800402, 1214041809, 371599456, 3799759368, 638902380, 2986692308, 2369894807
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
