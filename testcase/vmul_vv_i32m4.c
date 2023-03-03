/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    718168055, 306606023, 3237864462, 2802621140, 3293669403, 1975039685, 733466037, 1614628497, 460085263, 1321245433, 1946768621, 2460883629, 2698416631, 423019348, 2775160818, 3358059667
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1625143880, 1985039815, 2015919205, 2235533495, 352333466, 1444832780, 3911655201, 250337469, 843117746, 2113140522, 2486937480, 524344412, 88904899, 3347143573, 35997242, 3628091884
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1167126419394753400, 608625163173805745, 6527273152132792710, 6265353432265084300, 1160469956617140798, 2853602078688874300, 2869066238387908437, 404202011314254093, 387906049908377198, 2791977263979736026, 4841491848452815080, 1290350579448431148, 239902458038975269, 1415906491912850404, 99898135554463956, 12183349023830442628
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
