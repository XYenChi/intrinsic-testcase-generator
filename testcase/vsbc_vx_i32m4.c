/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    736005748, 231296598, 3853888894, 3019898201, 1024371454, 3502176195, 4081727593, 2959873493, 2246880297, 1286217276, 1302115497, 2892180969, 433671604, 282331701, 2005897163, 3971769353
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1603552274, 1196714693, 2028242328, 1722282657, 3126798313, 421356231, 2833857118, 3959739523, 2174375855, 4039087469, 2480245064, 288809380, 2751176250, 1807429897, 4257183365, 94234538
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
        out_v = __riscv_vsbc_vx_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -867546526, -965418095, 1825646566, 1297615544, -2102426859, 3080819964, 1247870475, -999866030, 72504442, -2752870193, -1178129567, 2603371589, -2317504646, -1525098196, -2251286202, 3877534815
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
