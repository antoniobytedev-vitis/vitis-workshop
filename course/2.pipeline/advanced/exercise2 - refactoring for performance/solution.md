# Solution
```cpp
#define N 128
void bubble_sort(int A[N]) {
    #pragma HLS ARRAY_PARTITION variable=A dim=1 type=complete   
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            #pragma HLS PIPELINE II=1
            int tmp=A[j];
            A[j] = (A[j]>A[j+1]) ? A[j+1] : A[j];
            A[j+1]=(A[j]>A[j+1]) ? tmp : A[j+1];
        }
    }
}
```
## Finished table
| Metric                        | **Without Refactoring** | **With refactoring** | 
| ----------------------------- | ------------------------------- | ---------------------------------- |
| **Total Latency (cycles)**    |                        |                                 |                                    |
| **LUTs Used**                 |                        |                                 |                                    |
| **FFs Used**                  |                        |                                 |                                    |
| **DSPs Used**                 |                        |                                 |                                    |
| **BRAMs Used**                |                        |                                 |                                    |