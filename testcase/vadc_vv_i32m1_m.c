/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3272691167, 3201295530, 1103389586, 809451098, 3392578998, 2796182131, 3787705429, 3111650139, 1472269284, 712597338, 816046757, 2045741604, 3410359763, 3295406265, 267969057, 2351046551
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2173492165, 453590551, 1220886919, 2473315001, 2436889780, 2255321270, 76915941, 2268864181, 250937721, 3299106938, 4074204038, 1710811263, 1616827254, 334851008, 1850518350, 3619081261
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    921773797, 108571350, 2803951607, 1251511275, 2486255592, 35059586, 3908257818, 956822311, 3522379778, 3298682758, 292967396, 860935784, 429979623, 1854033003, 2525089803, 112308838
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    5446183332, 3654886082, 2324276505, 3282766099, 5829468778, 5051503402, 3864621371, 5380514321, 1723207006, 4011704277, 4890250796, 3756552868, 5027187017, 3630257274, 2118487408, 5970127813
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
