# Solution

```cpp
#define N 1024
void offset(float in[N], float out[N]) {
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=2
        out[i] = in[i] + 10.0f;
    }
}
```
## Finished table
| Metric                     | **No pragmas** | **Only pipeline** | **Only unroll** | **Unroll and Pipeline** |
| -------------------------- | -------------- | ----------------- | --------------- | ----------------------- |
| **Total Latency (cycles)** | 769            | 259               | 385             | 131                     |
| **LUTs Used**              | 102            | 109               | 124             | 134                     |
| **DSPs Used**              | 54             | 62                | 93              | 11                      |

Pipeline let's us increase throughput more while using less resources than unrolling. However, it is crucial to note that to get the most out of these two techniques they have to be combined.

 With pipelining, latency decreases because the hardware overlaps operations, but only one element is processed per cycle.

With unrolling, multiple elements are processed in parallel per iteration, but the loop finishes faster by using more hardware resources.

With both, the design achieves the highest throughput, combining parallelism and overlapped execution.