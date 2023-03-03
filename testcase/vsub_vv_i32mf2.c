/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1511468311, 3418760071, 3841893053, 2788939539, 3758496456, 1811221102, 2518888505, 318873240, 2436800394, 809350830, 3006690416, 197931960, 3547593759, 208804359, 977710171, 1339650249
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1559080869, 761546793, 1345893828, 2121846628, 3569616726, 1385176398, 3420148079, 1831909418, 933693018, 2079394065, 4206084467, 1198468156, 1573350745, 3107766448, 2383924954, 1528294178
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -47612558, 2657213278, 2495999225, 667092911, 188879730, 426044704, -901259574, -1513036178, 1503107376, -1270043235, -1199394051, -1000536196, 1974243014, -2898962089, -1406214783, -188643929
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
