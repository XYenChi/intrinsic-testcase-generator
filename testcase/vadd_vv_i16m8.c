/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16m8_t data1[] = {
    7822, 153, 28797, 55712, 63112, 39851, 22972, 8194, 7995, 60974, 33688, 12256, 12983, 14118, 55629, 49502, 15198, 8305, 19794, 45091, 26177, 5072, 20618, 38484, 37624, 45003, 8384, 6064, 36465, 17447, 51566, 62788, 43870, 41973, 22656, 20629, 61482, 27976, 8464, 46962, 34640, 41036, 38142, 44834, 33832, 51705, 19632, 47062, 19323, 62649, 48366, 3284, 59857, 26384, 42387, 20757, 51220, 12052, 31524, 25640, 15245, 5272, 15097, 7512
    };
    const vint16m8_t *in1 = &data1[0];
    vint16m8_t data2[] = {
    36241, 58804, 7483, 51615, 39756, 5082, 13672, 51241, 15474, 26541, 46729, 26438, 38319, 22918, 58876, 60814, 30254, 35365, 47716, 17636, 33930, 21983, 36088, 9971, 51917, 56807, 21856, 46281, 46383, 975, 23820, 47973, 27625, 61269, 55259, 63274, 4974, 24826, 42956, 9730, 11782, 54269, 22201, 53920, 1368, 29141, 1360, 36203, 50096, 58355, 61231, 64920, 5943, 1372, 53181, 46291, 28760, 51103, 20854, 28058, 37974, 40418, 9596, 45278
    };
    const vint16m8_t *in2 = &data2[0];
    vint16m8_t out_data[64];
    vint16m8_t *out = &out_data[0];
    for (int n = 64, Q_element = 16;n >= 0; n -= Q_element) {
        vint16m8_t out = __riscv_vadd_vv_i16m8 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16m8_t golden[] = {
    44063, 58957, 36280, 107327, 102868, 44933, 36644, 59435, 23469, 87515, 80417, 38694, 51302, 37036, 114505, 110316, 45452, 43670, 67510, 62727, 60107, 27055, 56706, 48455, 89541, 101810, 30240, 52345, 82848, 18422, 75386, 110761, 71495, 103242, 77915, 83903, 66456, 52802, 51420, 56692, 46422, 95305, 60343, 98754, 35200, 80846, 20992, 83265, 69419, 121004, 109597, 68204, 65800, 27756, 95568, 67048, 79980, 63155, 52378, 53698, 53219, 45690, 24693, 52790
    };
    int fail = 0;
    for (int i = 0; i < 64; i++){
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
