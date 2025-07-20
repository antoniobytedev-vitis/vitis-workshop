
# Problems in Loops – Extra Cycles Due to Imperfect Loop Nesting
In FPGA designs using Vitis HLS, nested loops are common for processing two-dimensional data or multi-step computations. However, when loops are imperfectly nested—meaning there are operations between the loops or in outer loops—it prevents Vitis HLS from flattening them. This leads to extra cycles spent transitioning between outer and inner loops, reducing throughput and underutilizing the FPGA's computational resources.

## Example
Consider a simple matrix addition where each element of two matrices is added together and stored in a result matrix:

```cpp
void add_matrices(int a[64][64], int b[64][64], int c[64][64]) {
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}
```
In this case, the nested loops will execute sequentially. Each iteration of the inner loop will compute the addition for one element, and then the design will transition to the next iteration, and eventually to the next row in the outer loop. Each transition between loops typically costs one extra clock cycle, resulting in 128 additional cycles (64 cycles for entering and 64 for exiting the inner loop) for this structure.

## The Solution
You can use loop flattening to merge the nested loops into a single loop, removing the overhead caused by loop transitions. Flattening transforms the nested loops into one linear loop, enabling Vitis HLS to pipeline the operations continuously, maximizing resource utilization and reducing latency.

To enable this, you can use the #pragma HLS LOOP_FLATTEN directive:

```cpp
void add_matrices_flatten(int a[64][64], int b[64][64], int c[64][64]) {
#pragma HLS LOOP_FLATTEN
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
#pragma HLS PIPELINE II=1
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}
```

By flattening the loops, Vitis HLS merges them into a single loop with 64 x 64 = 4096 iterations, eliminating the transition cycles between the outer and inner loops. Combined with pipelining, this allows one addition to execute per cycle, achieving II = 1 without additional control overhead. Your design now uses the FPGA’s adder resources efficiently, continuously processing data each cycle without stalls, and reducing total execution latency.

## Why Loop Flattening Matters
Without loop flattening, designs with nested loops will suffer from unnecessary cycles during loop transitions, which add up in large loops and reduce effective throughput. Flattening loops aligns with the FPGA’s capability to process data streams continuously, ensuring that the hardware resources remain active and efficient across the entire computation.
