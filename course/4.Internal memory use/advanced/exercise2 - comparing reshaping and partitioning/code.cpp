#include <ap_int.h>
#define N 256

void top_function(ap_int<32> A[N], ap_int<32> B[N], ap_int<32> C[N]) {
    for (int i = 0; i < N; i += 4) {
        for (int j = 0; j < 4; j++) {
            #pragma HLS UNROLL factor=4
            int idx = i + j;
            C[idx] = A[idx] + B[idx];
        }
    }
}