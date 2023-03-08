/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    1074959799966562092, -280891531865344423, 8006984774054518699, 581690246640735260, -827615622701191185, 7948203248064112738, -1131132535031911963, -8710573201686241329, -4286698790200387708, 5042962083159035493, -122955144598852781, -6095266897806621691, -7221630367338817213, 8812290604118082888, -4118014877906601043, 7807489190440921893
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -2367553278119025590, 6662555295427354844, -8734006211440391949, 539994226758354073, 3725911059722347121, 3661378169282027782, 7065949310700668023, 4021162256181355837, 4952801264265754723, 153092144342395709, -7506527698241512551, -672107615937927916, -8486603828088949900, 3373477862544778943, -1632029029794347555, -3807638887488965686
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int out_data[] = {
    -8249686835327980497, -7556756633279485323, 7654851853483280259, 3688076941461026081, 3009601536641064734, 3619572467862152755, -945822535713061690, 7200225325222145864, 8825374509105150768, -4202895823035399586, 7380168995818651351, 6914158855530214292, -7413865983338974477, 2938620859929553045, -7935854327657309215, -8316582313335840855
    };
    const int64_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2_m (mask, *in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2_m (mask, *in2, vl);
    vint64m2_t data1_v = __riscv_vle64_v_i64m2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u64m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m2 (bool64_t mask, int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    -8249686835327980497, -7556756633279485323, 7654851853483280260, 3688076941461026082, 3009601536641064735, 3619572467862152755, -945822535713061690, 7200225325222145865, 8825374509105150769, -4202895823035399585, 7380168995818651352, 6914158855530214292, -7413865983338974477, 2938620859929553046, -7935854327657309214, -8316582313335840855
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