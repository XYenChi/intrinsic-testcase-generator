/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3623455737, 346306216, 1556121714, 479226289, 3003326713, 4196358602, 3863678966, 2969485437, 4226183381, 2733076093, 227453194, 236309137, 4231427808, 1668078508, 1641699741, 1963004957
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    441756605, 3545874347, 2278963612, 3180867357, 3901515708, 3625087787, 630537968, 2855198180, 2709864497, 2692352596, 554318923, 353705408, 3417390981, 730452838, 405939883, 1275988753
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
        out_v = __riscv_vsub_vv_u32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3181699132, -3199568131, -722841898, -2701641068, -898188995, 571270815, 3233140998, 114287257, 1516318884, 40723497, -326865729, -117396271, 814036827, 937625670, 1235759858, 687016204
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
