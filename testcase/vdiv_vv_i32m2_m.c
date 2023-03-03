/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    988107881, 3332490945, 1056214455, 927566126, 545880021, 352897529, 1748649178, 3965964803, 1888854890, 66015299, 2612389956, 3231170270, 2569010274, 2391614449, 3145505299, 1207551648
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1894683895, 341619138, 3393008492, 3096167307, 867959810, 1512176432, 3857900536, 3747368011, 2011793970, 125079082, 345264206, 1166056185, 2638343977, 4021259303, 2736383919, 2955303202
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    2938828540, 430730526, 3849587426, 1890998997, 919923962, 4240022606, 1843888444, 1327402707, 3317780410, 3417179154, 1314016502, 3863477155, 1790352181, 44801578, 2496443197, 2604203122
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2938828540, 0, 3, 1890998997, 919923962, 4, 2, 0, 3317780410, 1, 1314016502, 0, 1790352181, 44801578, 2496443197, 2604203122
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
