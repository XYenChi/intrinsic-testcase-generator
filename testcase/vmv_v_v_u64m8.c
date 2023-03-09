/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    5733998720413390698, 17164289860384779156, 6908719823153559093, 15909350105698580827, 1475557901036516847, 17288737628357570417, 8597057460895057932, 14065372099649664731, 2532528264676332083, 8384232818955147538, 18198404677030568620, 17829635667811114026, 1374335426084601660, 10871093875481596272, 144621215980554939, 15021332624118267054
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vuint64m8_t data1_v = __riscv_vle64_v_u64m8 (in1, vl);
    vuint64m8_t out_v = __riscv_vle64_v_u64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_v_u64m8 (src, vl);
        void __riscv_vse64_v_u64m8 (uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    5733998720413390698, 17164289860384779156, 6908719823153559093, 15909350105698580827, 1475557901036516847, 17288737628357570417, 8597057460895057932, 14065372099649664731, 2532528264676332083, 8384232818955147538, 18198404677030568620, 17829635667811114026, 1374335426084601660, 10871093875481596272, 144621215980554939, 15021332624118267054
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
