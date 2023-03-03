/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3290550889, 248982956, 1795960382, 1255678508, 1770431984, 1455121974, 3388606397, 3622951270, 2712564684, 3540283428, 617805273, 2215509465, 1353487348, 4040116361, 3059696647, 3782632707
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    918798044, 2304014046, 4111254978, 4117538635, 2379738404, 2559161204, 2929258111, 1551676869, 2600240460, 3172431543, 3421137900, 19013893, 107938761, 3687785909, 2241271280, 879389024
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2371752845, -2055031090, -2315294596, -2861860127, -609306420, -1104039230, 459348286, 2071274401, 112324224, 367851885, -2803332627, 2196495572, 1245548587, 352330452, 818425367, 2903243683
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
