/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    669647910, 746765846, 726666650, -1111399642, -1931306165, -1007466378, -2116315793, -1218031997, -319034407, -618073280, 1866729530, 734685711, -1500086951, 1872352944, 1795762567, 1870812392
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1420625265, 1481306143, 1867029897, -772700641, -1705444967, -869584663, 187372310, -431976243, -904078543, 1995229520, -1605011315, 1730681870, 214233320, -1037567684, -797898242, 1282493598
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m4 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -528547054, -216786031, -968085786, -1725338146, -1982193486, 974686800, -2123215340, -1006828892, 235568722, -1510081976, 3972505525, 393137671, -100272315, 320919415, 2196088265, 2604834474
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
