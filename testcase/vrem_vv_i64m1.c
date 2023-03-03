/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    35324179713084958, 8552517460410812368, 2231135235269787820, 6652645065077042234, 4092569118986464194, 3897026585222772625, 821413950188595572, 5197126525937793664, 528561313050682882, 2785005455051609399, 2717298416409279131, 3605284627111857471, 281923686614966872, 16279754839037070243, 10690339353728892442, 329323332271279043
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    4766045736194739921, 1990804967497724827, 21794893664204044, 1883068093996782511, 9016255937417569531, 2787979531001314028, 13102853204536159711, 17461464961134914996, 3218072318041696688, 13565594167504458476, 11674498183407619192, 17582473755114255517, 16205310860378173559, 15933975681770042329, 6674275078151146494, 17408993432483365516
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m1(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (*in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1 (*in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i64m1 (data1_v, data2_v, vl);
        void vint64m1_t __riscv_vse64_v_i64 (int64m1_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    32605654641355549, 1990804967497724827, 21794893664204044, 1883068093996782511, 831117699444641143, 2787979531001314028, 781643951707226131, 1870085383321534004, 46704439737599396, 2425572347298020880, 805304517770502668, 3161335246666825633, 135660723325061855, 15933975681770042329, 6674275078151146494, 284180154376855280
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
