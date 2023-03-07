/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -498247217, -1674955859, 1365470849, -1708371554, -1096295840, 962774820, 399168068, 1830097342, 714346086, -1718608544, 1563717540, -1176123870, 588367332, 126116826, -372044626, -1853358183
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    517316095, -1020077687, -524087261, 1589870629, -709194794, -868578582, 592059992, 195405102, 594632949, -1622101595, -2000842194, -1470731198, -898151124, 964396741, 1120393860, -1239331100
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int out_data[] = {
    1357334174, 748498403, 1897894635, -1524849453, 1085142308, 1293676675, 134557591, 1438897909, 1855115703, 712466571, 882501844, 64082972, -685681427, 587026703, -1889460607, 249210491
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (bool32_t mask, int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1357334175, 748498403, 1897894636, -1524849452, 1085142309, 1293676675, 134557592, 1438897910, 1855115703, 712466571, 882501844, 64082973, -685681427, 587026703, -1889460606, 249210491
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
