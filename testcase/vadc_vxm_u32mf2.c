/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2241664700, 3993175850, 1220089333, 2109879714, 504391573, 2235484286, 971692735, 3717246856, 2580143978, 3225565748, 2695255260, 1950283412, 2472470733, 2104349902, 3990254541, 1291650492
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3459056247, 3468248290, 420523488, 2370153027, 2696895938, 591334632, 900971133, 1282615689, 2779459853, 1758662818, 1616717803, 1741329772, 2752148952, 1298135116, 2409437788, 3489327911
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    bool64_t masked[] = {
    0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2 (in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32mf2 (uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    5700720947, 7461424141, 1640612822, 4480032742, 3201287512, 2826818918, 1872663868, 4999862545, 5359603831, 4984228567, 4311973063, 3691613185, 5224619686, 3402485019, 6399692330, 4780978403
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
