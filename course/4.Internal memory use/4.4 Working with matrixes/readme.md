# Problems with 2D Arrays – Memory Bottlenecks Due to Limited Ports

In FPGA designs using Vitis HLS, two-dimensional arrays are commonly used to represent images, matrices, and tabular data. By default, Vitis HLS maps these arrays to block RAMs (BRAMs). However, most FPGA BRAMs only support two memory ports (dual-port RAM). This means that at most two reads/writes can occur per cycle, regardless of how much parallelism is available in the computation.

When a loop attempts to access multiple elements of a 2D array in parallel, the limited number of ports creates a bottleneck, stalling the pipeline and preventing the design from reaching an initiation interval (II) of 1.

# Example

Consider a matrix-vector multiplication, where each row of a 64×64 matrix is multiplied by a vector of 64 elements:
```cpp
void matvec_mult(int A[64][64], int x[64], int y[64]) {
    for (int i = 0; i < 64; i++) {
        int sum = 0;
        for (int j = 0; j < 64; j++) {
#pragma HLS PIPELINE II=1
            sum += A[i][j] * x[j];
        }
        y[i] = sum;
    }
}
```

## What happens here?

Each iteration of the inner loop needs two reads per cycle: one from A[i][j] and one from x[j].

If A is stored in a single BRAM, it can only serve two accesses per cycle.

As a result, Vitis HLS cannot achieve II = 1, and the pipeline stalls, wasting cycles.

## The Solution

You can use array partitioning to split a 2D array into multiple smaller arrays, each with its own memory ports. This increases the number of parallel accesses available per cycle.

By using dim=1 we can partition the first dimension(rows), whereas by using dim=2 we can partition the columns.

To enable this, apply the #pragma HLS ARRAY_PARTITION directive. For example, we can partition the second dimension of A completely:

```cpp
void matvec_mult_partition(int A[64][64], int x[64], int y[64]) {
#pragma HLS ARRAY_PARTITION variable=A dim=2 complete
    for (int i = 0; i < 64; i++) {
        int sum = 0;
        for (int j = 0; j < 64; j++) {
#pragma HLS PIPELINE II=1
            sum += A[i][j] * x[j];
        }
        y[i] = sum;
    }
}

```
## What changes?

Partitioning along dim=2 (columns) breaks each row of A into 64 separate registers.

This allows all 64 elements in a row to be accessed in parallel.

Now the loop can be fully pipelined with II = 1, ensuring maximum throughput.

## Why Array Partitioning Matters

Without array partitioning, 2D arrays stored in block RAM limit memory bandwidth and prevent parallelism. This creates pipeline stalls and significantly increases execution latency.

Partitioning maps array elements into separate memory resources (registers, LUTRAMs, or multiple BRAMs), providing more simultaneous access ports. This aligns with the FPGA’s ability to perform many parallel operations, enabling the design to run at full throughput.