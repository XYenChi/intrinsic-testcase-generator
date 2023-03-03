/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    720679629, 1406855322, 697186266, 3644035683, 1120236885, 3971768883, 3763827937, 1360922793, 2536416252, 1452243592, 1100037930, 2161100634, 1574310900, 1346661809, 3503308192, 1899488419
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1638594480, 1716969832, 3567164360, 3020342463, 1330513, 3553565458, 2580750117, 2985709006, 3212468752, 2359955012, 3913774716, 1178147447, 1555924517, 2561831643, 3589219553, 3127225877
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1180901661927847920, 2415528145862645904, 2486978000356679760, 11006235710052107229, 1490489738572005, 14113940709788043414, 9713499388780618629, 4063319439530773758, 8148157951614957504, 3427229543585283104, 4305300637074977880, 2546095194657181398, 2449508926690335300, 3449920834715822187, 12574142262911478176, 5940129336958618463
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
