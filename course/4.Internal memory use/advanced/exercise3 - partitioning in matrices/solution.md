

# Solution
```cpp
#define ROWS 8
#define COLS 64

void top_function(int A[ROWS][COLS], int B[ROWS][COLS]) {
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


