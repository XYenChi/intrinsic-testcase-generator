/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3040165720, 1493080595, 3605198695, 2553451245, 3440697212, 1214622694, 429339469, 2164764490, 227111782, 543053336, 556874341, 11969287, 1528581844, 2725941699, 2109803131, 1070632886
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1409996525, 3517268370, 4035786342, 2890332216, 3704959917, 2569710720, 1676105738, 936161567, 2337746192, 836049852, 2117948903, 360832304, 3752281167, 2110151554, 2796049015, 3782818330
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    const int out_data[] = {
    3899113779, 1779823405, 1704690669, 3960905514, 2037209749, 3358645503, 1482294219, 1146383633, 3907438654, 2589739784, 2926262390, 921283851, 225009844, 3136496529, 2483952761, 2067233578
    };
    const int32_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4286623104523236779, 5251565152434103555, 14549811655181914359, 7380322399369714434, 12747645259030861153, 3121228960885725183, 719618349023067341, 2026569318290739463, 530929707436272798, 454019663780646056, 1179431402556060313, 4318906326731099, 5735668865684341792, 5752150115394746775, 5899112968760418726, 4050009707928833958
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
