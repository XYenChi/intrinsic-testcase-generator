/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    173974685, 1347219773, 1681713756, 153502274, 2322856523, 2056686885, 4002664234, 932119721, 1448286778, 3647179254, 1003808566, 604353571, 318050062, 3149001531, 3302782376, 1201527664
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3352493026, 457342407, 3521230144, 1514429482, 453717580, 3869337513, 680882894, 2265630920, 34092552, 1982226370, 3927274809, 2743432502, 3020356586, 1729929278, 839785405, 2981522608
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    1158050571, 591263703, 3562813832, 1119239053, 2422838536, 1516963496, 2509987468, 1579580579, 2208983437, 2639872522, 489362551, 2016407105, 2811188017, 2889034039, 4018325334, 810288706
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1158050571, 591263703, -1839516388, -1360927208, 1869138943, -1812650628, 2509987468, 1579580579, 2208983437, 1664952884, 489362551, 2016407105, 2811188017, 2889034039, 4018325334, -1779994944
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
