/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m2_t data1[] = {
    52454, 5757, 54650, 47872, 2790, 33447, 31833, 19252, 23341, 1432, 12029, 4825, 42435, 53136, 46075, 22443
    };
    const vint16m2_t *in1 = &data1[0];
    vint16m2_t data2[] = {
    41054, 60252, 16967, 30029, 6046, 64473, 35708, 12402, 26571, 11957, 15512, 10645, 63757, 64657, 55443, 50917
    };
    const vint16m2_t *in2 = &data2[0];
    vint16m2_t out_data[64];
    vint16m2_t *out = &out_data[0];
    for (int n = 16, Q_element = 16;n >= 0; n -= Q_element) {
        vint16m2_t out = __riscv_vadd_vv_i16m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16m2_t golden[] = {
    93508, 66009, 71617, 77901, 8836, 97920, 67541, 31654, 49912, 13389, 27541, 15470, 106192, 117793, 101518, 73360
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
