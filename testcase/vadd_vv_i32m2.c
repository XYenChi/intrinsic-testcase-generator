/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1555879689, -1214195764, 2079529516, 939774989, 2012635170, 147584244, -741433534, 1082641454, -1471692667, -1418804394, -937496415, 1719369731, -471384794, -1476121420, 2092625432, 331406427
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    299357712, -1103948912, -685811079, -999240011, 265504465, -747622842, 685533487, 2141522928, 1556747888, 1497751958, 1456732990, -638863911, 1940895981, -1585135076, -1740854519, -1868078490
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vv_i32m2(op1, op2, vl);
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3038445319, 1976822620, 1393718437, 4235502274, 2278139635, 3694928698, 4239067249, 3224164382, 85055221, 78947564, 519236575, 1080505820, 1469511187, 1233710800, 351770913, 2758295233
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
/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1193164797, 79772395, 1522403435, -1806634967, -1656940555, 150924933, 224068312, 1676336459, 336251457, 222557442, -246216400, -1319037821, -294010010, -273606504, 677724637, -380246485
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1878505364, 727443448, 1415300135, 1905584251, 242696407, 1943420237, -1325655267, -1397168528, 1957219779, -2066167864, 2141841212, -599015063, 1595580627, 391501418, 1961515754, -364766058
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3071670161, 807215843, 2937703570, 98949284, 2880723148, 2094345170, 3193380341, 279167931, 2293471236, 2451356874, 1895624812, 2376914412, 1301570617, 117894914, 2639240391, 3549954753
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
