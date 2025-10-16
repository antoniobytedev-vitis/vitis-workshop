# Solution
```cpp
#include <ap_int.h>
#include <ap_int.h>
#define N 256

void top_function_reshape(ap_int<32> A[N], ap_int<32> B[N], ap_int<32> C[N]) {
#pragma HLS ARRAY_RESHAPE variable=A type=cyclic factor=4 dim=1
#pragma HLS ARRAY_RESHAPE variable=B type=cyclic factor=4 dim=1
#pragma HLS ARRAY_RESHAPE variable=C type=cyclic factor=4 dim=1
    for (int i = 0; i < N; i += 4) {
        for (int j = 0; j < 4; j++) {
            #pragma HLS UNROLL factor=4
            int idx = i + j;
            C[idx] = A[idx] + B[idx];
        }
    }
}

void top_function_partition(ap_int<32> A[N], ap_int<32> B[N], ap_int<32> C[N]) {
#pragma HLS ARRAY_PARTITION variable=A type=cyclic factor=4 dim=1
#pragma HLS ARRAY_PARTITION variable=B type=cyclic factor=4 dim=1
#pragma HLS ARRAY_PARTITION variable=C type=cyclic factor=4 dim=1
    for (int i = 0; i < N; i += 4) {
        for (int j = 0; j < 4; j++) {
            #pragma HLS UNROLL factor=4
            int idx = i + j;
            C[idx] = A[idx] + B[idx];
        }
    }
}
```
## Finished Table
| Metric                        | **Without Partitioning** | **With Partitioning** |Without Pipeline
| ----------------------------- | ---------------------- | ------------------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |                       |   |                              |                                    |
| **LUTs Used**                 |           |            |                                 |                                    |
| **FFs Used**                  |           |             |                                 |                                    |
 **BRAMs used**                  |           |             |                                 | 
 |**DSP used**||||