# Solution
```cpp
#define N 128

void pipeline_off(int A[N], int B[N]) {
    for (int i = 0; i < N - 2; i++) {
        #pragma HLS PIPELINE off
        int sum = A[i] + A[i + 1] + A[i + 2];
        B[i] = sum;
    }
}

void partitioned(int A[N], int B[N]) {
    #pragma HLS ARRAY_PARTITION variable=A factor=2
    for (int i = 0; i < N - 2; i++) {
        #pragma HLS PIPELINE II=1
        int sum = A[i] + A[i + 1] + A[i + 2];
        B[i] = sum;
    }
}
```
## Finished Table
| Metric                        | **Without Partitioning** | **With Partitioning** |**Without Pipeline**
| ----------------------------- | ---------------------- | ------------------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |                       |   |                              |                                    |
| **LUTs Used**                 |           |            |                                 |                                    |
| **FFs Used**                  |           |             |                                 |                                    |
 **BRAMs used**                  |           |             |                                 | 
 |**DSP used**||||
