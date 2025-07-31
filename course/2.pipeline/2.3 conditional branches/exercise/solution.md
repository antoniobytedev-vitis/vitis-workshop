# SOLUTION
```cpp
#define SIZE 256
#define TOKENS 64

void count_tokens(int stream[SIZE], int counts[TOKENS]) {
    int acc = 0;
    int old_token = stream[0];
    int current;

#pragma HLS DEPENDENCE variable=counts intra RAW false
    for (int i = 0; i < SIZE; i++) {
#pragma HLS PIPELINE II=1
        current = stream[i];
        if (current == old_token) {
            acc++;
        } else {
            counts[old_token] = acc;
            acc = counts[current] + 1;  // False dependency here if old_token ≠ current
        }
        old_token = current;
    }

    counts[old_token] = acc;
}
```
## Finished table
| Metric                        | **Without Pipelining** | **With `#pragma HLS PIPELINE`** | **Pipelined and Fixed Dependency** |
| ----------------------------- | ---------------------- | ------------------------------- | ---------------------------------- |
| **Total Latency (cycles)**    |                        |                                 |                                    |
| **LUTs Used**                 |                        |                                 |                                    |
| **FFs Used**                  |                        |                                 |                                    |
| **DSPs Used**                 |                        |                                 |                                    |
| **BRAMs Used**                |                        |                                 |                                    |