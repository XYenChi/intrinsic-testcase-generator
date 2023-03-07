/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1820406152, -1890203455, -488667850, 1323030474, 1477394873, 1354602876, 833586763, 1317317303, 206398158, 1092453263, -1712370503, 30692378, 611818976, 64317416, -232505608, -1750282207
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -475811994, -1065712327, -2097065820, 688640943, 620750497, -857415387, -98652052, -931325016, 1030019502, 796346415, -1014096988, -1497945815, -420785444, -295199283, 1407051414, 863676181
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u32mf2 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -289307704, -1954158043, 344623828, 1344752018, -478248070, 1306716088, 318965151, 1963631048, -1732319478, -827721615, -3563184607, 1988030638, 2177899394, 831637442, 652123066, -270414672
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
