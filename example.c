/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <riscv_vector.h>
int main(){
    const int8_t data1[] = {
    120, 122, 72, 30, 22, 54, 252, 87, 158, 173, 78, 61, 156, 232, 218, 35
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    254, 188, 77, 149, 227, 234, 154, 70, 1, 73, 167, 222, 74, 167, 82, 155
    };
    const int8_t *in2 = &data2[0];
    size_t vl = __riscv_vsetvl_e8m1(64);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1 (in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1 (in2, vl);
    vint8m1_t out_v = __riscv_vle8_v_i8m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i8m1 (data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m1 (int8_t *out, vint8m1_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    374, 310, 149, 179, 249, 288, 406, 157, 159, 246, 245, 283, 230, 399, 300, 190
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

