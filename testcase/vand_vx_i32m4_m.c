/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2149931978, 3740188435, 126164122, 2016396983, 3968309727, 1075139566, 2473481902, 1973386903, 3093483752, 2163691032, 42086795, 595864477, 3545388399, 1049805157, 3044110403, 594427843
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    352660332, 608087260, 442003259, 1950337573, 4178722246, 2026676712, 2658980300, 1265239565, 1130946385, 1972580074, 1046962309, 322558150, 3918607347, 3206641038, 815861150, 3137460709
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    2655244849, 4079366663, 661764698, 1598557116, 3004691296, 1527614344, 2986864571, 4040263517, 206457425, 3017312748, 750187447, 1064587188, 3493953797, 1658509180, 1977111546, 437831494
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2655244849, 4079366663, 661764698, 1598557116, 4178722246, 2026676712, 2658980300, 4040263517, 1130946385, 1972580074, 750187447, 322558150, 3493953797, 1658509180, 1977111546, 3137460709
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
