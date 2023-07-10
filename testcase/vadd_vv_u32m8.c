/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    890892899, 739252012, 1019221324, 2528759758, 1437971264, 1221582968, 208510891, 2672092874, 2230449389, 3943710099, 1993405998, 1926320147, 4239050058, 4038986661, 148739032, 4199866972
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    1923171097, 1912744525, 4040142443, 2378975112, 584894668, 1888288829, 3488845369, 1790627225, 2119101431, 2056724588, 1933609780, 243257772, 1449120136, 4093723981, 594210016, 1258855282
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8 (in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_u32m8 (in2, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vv_u32m8(op1, op2, vl);
        void __riscv_vse32_v_u32m8 (uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    2814063996, 2651996537, 764396471, 612767574, 2022865932, 3109871797, 3697356260, 167752803, 54583524, 1705467391, 3927015778, 2169577919, 1393202898, 3837743346, 742949048, 1163754958
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
    const uint32_t data1[] = {
    3331109357, 1929415174, 1342847847, 3144880288, 1442645793, 2072608568, 2587758184, 1333838444, 522467491, 1869819321, 3081302723, 2143520078, 2503957753, 1319664472, 316210072, 341269687
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    1409741596, 4173030016, 223907432, 2282977983, 1692081154, 1903133378, 94118104, 595362716, 2318111413, 2358630683, 4086863360, 2184177680, 2891204724, 2281510306, 38072666, 1851039824
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8 (in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_u32m8 (in2, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m8 (uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    445883657, 1807477894, 1566755279, 1132890975, 3134726947, 3975741946, 2681876288, 1929201160, 2840578904, 4228450004, 2873198787, 32730462, 1100195181, 3601174778, 354282738, 2192309511
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
