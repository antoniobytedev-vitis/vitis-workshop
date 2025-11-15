# Solution
```cpp
#define N 128
void datapath1(int A[N], int B[N]) {
#pragma HLS LOOP_MERGE
int buffer[N];
copy_loop:
for (int i = 0; i < N; i++) {
    buffer[i] = A[i];
}


scale_loop:
for (int i = 0; i < N; i++) {
    B[i] = buffer[i] * 2 +5;
}

}
```
The loop can't be merged due to a carried dependency. B is written in the first loop and the written and read from in the second loop. The simplest way to fix this is to add a buffer and make it so that B is only written to in the second loop.
## Finished Table
| Metric                        | **Without Flattening** | **With Flattening** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |                      |                                 |                                    |
| **LUTs Used**                 |                        |                                 |                                    |
| **FFs Used**                  |                        |                                 |                                    |
|**BRAMs Used**||
|**DSPs Used**||