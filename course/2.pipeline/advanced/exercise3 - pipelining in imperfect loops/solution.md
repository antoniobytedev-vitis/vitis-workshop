# Solution
```cpp
#define N 16

void pascal_triangle(int P[N][N]) {
    #pragma HLS ARRAY_PARTITION variable=P dim=2 type=cyclic factor=2
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            #pragma HLS PIPELINE II=1
            P[i][j] =(j==0||j==1) ? 1 : P[i - 1][j - 1] + P[i - 1][j];
        }
    }
}
```

Because the inner loop has a variable trip count it can't be unrolled (which is done automatically by pipelining the outer loop). This means that to get the most throughput pipelining the inner loop is the way to go.

## Finished table
| Metric                        | **Without Refactoring** | **With refactoring** | 
| ----------------------------- | ------------------------------- | ---------------------------------- |
| **Total Latency (cycles)**    |                        |                                 |                                    |
| **LUTs Used**                 |                        |                                 |                                    |
| **FFs Used**                  |                        |                                 |                                    |
| **DSPs Used**                 |                        |                                 |                                    |
| **BRAMs Used**                |                        |                                 |                                    |