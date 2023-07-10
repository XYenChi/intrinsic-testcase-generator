/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    3992904914759533954, 5494250977882522662, 12927193350152313952, 6492291514244234392, 8416856195437557821, 3833298130242273394, 12548243790498490046, 1466812721338011863, 5147816191310752808, 746099020760259970, 16153179454031365862, 17429132136948910666, 631799215481894528, 6326726420128523269, 18130578394670091078, 2917124863816386680
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    5495864951320780347, 3691447759610909126, 3835695659365038504, 10482470696185980379, 6722006459950115406, 11789499997450611351, 4550022898851443822, 14826390760433023125, 10172393138352031117, 3568515129010650095, 9751798898118324770, 7094617072379024515, 16975340327271466944, 5791185431519321189, 5415988614762182790, 492973237253410268
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const uint out_data[] = {
    0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1
    };
    const uint64_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0
    };
    const uint8_t *mask = &masked[0];
    vuint64m8_t data1_v = __riscv_vle64_v_u64m8 (in1, vl);
    vuint64m8_t data2_v = __riscv_vle64_v_u64m8 (in2, vl);
    vuint64m8_t out_v = __riscv_vle64_v_u64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m8 (uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    9488769866080314301, 0, 16762889009517352456, 16974762210430214771, 0, 15622798127692884745, 1, 0, 15320209329662783925, 4314614149770910065, 1, 6077005135618383565, 17607139542753361472, 12117911851647844458, 1, 1
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
