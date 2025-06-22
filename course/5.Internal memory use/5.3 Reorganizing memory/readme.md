# Memory reorganization for performance
In FPGA design, memory access patterns are just as critical as the computations themselves. Even with fully pipelined loops and efficient datapaths, poor memory layout can become a major bottleneck. This is especially true in high-throughput designs where data must be processed continuously or in parallel.

Unlike CPUs, FPGAs have strict limitations on:

* How many data elements can be accessed per cycle

* The width of memory ports (e.g., 32 or 64 bits)

* The number of available memory ports on BRAM or URAM blocks

If the memory layout doesn't align with these architectural constraints, your design might:

* Waste bandwidth (e.g., using only 8 bits of a 32-bit memory port)

* Fail to achieve full pipelining

* Introduce unnecessary stalls or resource duplication

To achieve optimal performance, it's often necessary to reorganize how arrays are laid out in memory — ensuring that memory width and access patterns align with the datapath.

## Array reshape
In Vitis HLS, #pragma HLS ARRAY_RESHAPE is used to reorganize how an array is physically mapped into memory, so that multiple elements can be packed together and accessed in a single, wide word.

This technique helps maximize bandwidth utilization, reduce access latency, and improve loop pipelining, especially when dealing with narrow data types and wide interfaces.

Like with array partitioning there are 3 main types:

```cpp
#pragma HLS ARRAY_RESHAPE variable=<array> factor=<N>  type=<style>
```
factor: How many elements to group together.

type: The reshaping style (cyclic, block, or complete).

If type is omitted, cyclic is the default.

🔧 Reshaping Styles
Vitis HLS supports three reshaping styles:

1. Cyclic Reshape (default)
```cpp
#pragma HLS ARRAY_RESHAPE variable=a factor=4 dim=1 type=cyclic
```
Elements are grouped round-robin.

Optimized for sequential access patterns.

Great for matching wide memory interfaces.

    Example:
    Original a[8]:   a0 a1 a2 a3 a4 a5 a6 a7
    Reshaped as 2 words (factor=4): [a0 a2 a4 a6], [a1 a3 a5 a7]

2. Block Reshape
```cpp
#pragma HLS ARRAY_RESHAPE variable=a factor=4 dim=1 type=block
```
Elements are grouped into contiguous blocks.

Useful for chunked processing (e.g., tiles or rows).

    Example:
    Original a[8]:   a0 a1 a2 a3 a4 a5 a6 a7
    Reshaped as 2 words: [a0 a1 a2 a3], [a4 a5 a6 a7]

3. Complete Reshape
```cpp
 #pragma HLS ARRAY_RESHAPE variable=a type=complete 
 ```
Reshapes the entire array into a single packed word.

    All elements are grouped together.

    Best for very small arrays when you want full-width access in one cycle.

🧪 Example: Reshape vs. No Reshape
Without Reshape (1 element per access):
```cpp
void process(char a[8], char out[8]) {
#pragma HLS PIPELINE
    for (int i = 0; i < 8; i++) {
        out[i] = a[i] + 1;
    }
}
```
Accesses one char (8 bits) per cycle — inefficient if using a 32-bit memory port.

With Cyclic Reshape (4 elements per access):
```cpp
void process(char a[8], char out[8]) {
#pragma HLS ARRAY_RESHAPE variable=a factor=4 dim=1 type=cyclic
#pragma HLS ARRAY_RESHAPE variable=out factor=4 dim=1 type=cyclic
#pragma HLS PIPELINE
    for (int i = 0; i < 8; i++) {
        out[i] = a[i] + 1;
    }
}
```
Now, up to 4 chars (32 bits) can be accessed per cycle → 4× faster memory throughput.

## Reshape vs Partition
| Feature             | `ARRAY_RESHAPE`                | `ARRAY_PARTITION`                   |
| ------------------- | ------------------------------ | ----------------------------------- |
| Memory structure    | Groups elements in wider words | Splits elements into separate banks |
| Resource usage      | ✅ Low (1 BRAM)                 | ❌ Higher (multiple BRAMs/registers) |
| Access type         | Grouped (burst-style)          | Parallel (fully independent)        |
| Best use case       | Bandwidth optimization         | Full parallel processing            |
| Can combine with... | Pipelining, wide buses         | Loop unrolling                      |


### When to Use Each Reshape Type
| Reshape Type | Best For                                   |
| ------------ | ------------------------------------------ |
| `cyclic`     | Regular, interleaved access patterns       |
| `block`      | Chunked or tile-based processing           |
| `complete`   | Small arrays that fit into one memory word |










