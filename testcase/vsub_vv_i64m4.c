/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    10878974205187357486, 7477532537301066624, 7170927408265033946, 14095904909822809217, 14557482454001547759, 2958582853238133558, 6186469557261969806, 4847282729610189432, 13672768586853945062, 15189960554926859457, 6459587116069700561, 9079843960647734654, 8781398649448893077, 11090913693904820267, 9981311609643152033, 5958439229251908224
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    17701720477095516366, 10259430227191442093, 9183811817512615173, 14004124408983248577, 12272490378413913549, 5359554330746817782, 16606959366721983375, 1014098684043600817, 5596610749823323005, 15304082371292328077, 3799557673590342246, 535518840358523431, 103790547652418709, 122815773095836754, 899948034176114802, 14434149682795101058
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m4(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (*in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4 (*in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u64m4 (data1_v, data2_v, vl);
        void vint64m4_t __riscv_vse64_v_i64 (int64m4_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    -6822746271908158880, -2781897689890375469, -2012884409247581227, 91780500839560640, 2284992075587634210, -2400971477508684224, -10420489809460013569, 3833184045566588615, 8076157837030622057, -114121816365468620, 2660029442479358315, 8544325120289211223, 8677608101796474368, 10968097920808983513, 9081363575467037231, -8475710453543192834
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
