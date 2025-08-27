# Solution
```cpp
void matvec_mult(int A[64][64], int x[64], int y[64]) {
    #pragma HLS ARRAY_PARTITION variable=A dim=2 type=complete
    for (int i = 0; i < 64; i++) {
        int sum = 0;
        #pragma HLS PIPELINE II=1
        for (int j = 0; j < 64; j++) {

            sum += A[i][j] * x[j];
        }
        y[i] = sum;
    }
}
```
## Finished table
| Metric                        | **Without Partitioning** | **With Complete partitioning** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |                      |                                 |                                    |
| **LUTs Used**                 |                        |                                 |                                    |
| **FFs Used**                  |                        |                                 |                                    |
| **BRAMs used**                  |                        |                                 |                                    |