<<<<<<< Updated upstream


# Solution
```cpp
#define ROWS 8
#define COLS 64
void datapath1(int A[ROWS][COLS], int B[ROWS][COLS]) {
#pragma HLS ARRAY_RESHAPE variable=A type=cyclic factor=8 dim=2
#pragma HLS ARRAY_RESHAPE variable=B type=cyclic factor=8 dim=2

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=16
            B[r][c] = A[r][c] * 2;
        }
    }
}
```
## Complete table
| Metric                        | **Without Partitioning** | **With Partitioning** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |                       |                                 |                                    |
| **LUTs Used**                 |                       |                                 |                                    |
| **FFs Used**                  |                        |                                 |                                    |
 **BRAMs used**                  |                        |                                 | 
 |**DSP used**|||


=======
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
>>>>>>> Stashed changes
