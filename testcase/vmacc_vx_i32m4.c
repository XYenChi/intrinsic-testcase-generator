/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    18272246, 1667347705, 2044750285, 176452688, 1522583742, 204913131, 514352443, 3889387533, 1361505921, 4132118466, 4183602013, 3401767506, 2806122506, 1152171020, 2484332318, 855070848
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2833836159, 2954365684, 1680302392, 709633861, 3208392282, 2019555766, 1447265285, 734646891, 2592747537, 1881251488, 872057540, 2806018421, 156896805, 3186040455, 1122158498, 515228191
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    const int out_data[] = {
    404043166, 4042839399, 3702907871, 3657195857, 1877932883, 1738401980, 1297858121, 887951099, 1613148537, 3881899752, 4254269341, 4221457125, 3090083626, 3306740824, 1013228369, 3367781299
    };
    const int32_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    51780551824986280, 4925954846990994619, 3435798798631089591, 125216805926464225, 4885045928409412127, 413833496978565326, 744404436306699376, 2857326459900561002, 3530041124896815114, 7773554016636677160, 3648341684050097361, 9545422290016685151, 440271658720076956, 3670863484105354924, 2787814623512966733, 440556609559657267
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
