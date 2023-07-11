/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    2725652165, 4270479597, 801406560, 4178328259, 3875545357, 77058726, 1972944428, 3020736911, 1761355619, 406108862, 896628158, 482487688, 1579425718, 1025910351, 1460615512, 428079089
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    2182753292, 1875763481, 1717926136, 1197623558, 542506923, 2112757028, 3325161462, 488479158, 2367735171, 3993254271, 1888432663, 1926788799, 3020682674, 4229965139, 1558740043, 190396345
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
		out = __riscv_vadd_vx_u32m8(op1, op2, vl);
        void __riscv_vse32_v_u32m8 (uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    613438161, 1851275782, 2519332696, 1080984521, 123084984, 2189815754, 1003138594, 3509216069, 4129090790, 104395837, 2785060821, 2409276487, 305141096, 960908194, 3019355555, 618475434
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
    1279452229, 1707200213, 2445535168, 787900568, 3463293336, 2106558638, 970247842, 1225584773, 2802081596, 3922446218, 127862374, 2295510020, 595727659, 515834922, 2179364985, 936271305
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    330842396, 481666910, 1131367990, 2104800027, 240970550, 1290360067, 939875878, 3349966723, 1527898066, 1657361259, 4081110689, 3898500651, 1373001619, 3956372268, 3536881712, 998921989
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
    1610294625, 2188867123, 3576903158, 2892700595, 3704263886, 3396918705, 1910123720, 280584200, 35012366, 1284840181, 4208973063, 1899043375, 1968729278, 177239894, 1421279401, 1935193294
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
