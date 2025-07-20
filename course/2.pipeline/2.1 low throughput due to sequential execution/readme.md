# Problems in pipelining – Low Throughput Due to Sequential Execution
In FPGA designs using Vitis HLS, loop throughput is often a bottleneck. Loops in C/C++ execute sequentially, completing each iteration before starting the next. On FPGA hardware, this behavior wastes cycles and underutilizes resources, especially when your design needs to process large arrays or continuous data streams at high speed.

Consider a simple addition loop:
```cpp
void add_arrays(int a[100], int b[100], int c[100]) {
    for (int i = 0; i < 100; i++) {
        c[i] = a[i] + b[i];
    }
}
```

Without any optimization:

Each addition operation may take multiple cycles internally (e.g., 3 cycles).

Each loop iteration waits for the previous to finish before starting.

You require:

100
 iterations
×
3
 cycles
=
300
 cycles
100 iterations×3 cycles=300 cycles
to process the entire array.

If we run the c synthesis in vitis we get the following results:

![Cycles without pipeline](../../resources/cycles%20without%20pipeline.png)


## The Solution: Using #pragma HLS PIPELINE
By using:

```cpp
#pragma HLS PIPELINE II=1
```
you instruct Vitis HLS to pipeline the loop, allowing:

* A new iteration to start every cycle (when possible).

* Hardware operations from different iterations to overlap.

* Continuous utilization of FPGA resources.

This enables your design to achieve II=1, processing one element per cycle, greatly improving throughput. 
```
Note that even if you do not use #pragma HLS PIPELINE, vitis may add pipeline anyway to optimize throughput. To make sure this doesn't happen use "#pragma HLS PIPELINE off" instead.
```
## Pipelining example
```cpp
void add_arrays_pipelined(int a[100], int b[100], int [100]) {

    for (int i = 0; i < 100; i++) {
        #pragma HLS PIPELINE II=1
        c[i] = a[i] + b[i];
    }
}

```
The latency per operation (4 cycles) remains unchanged, meaning each addition still takes 4 cycles to complete internally.

However, the initiation interval (II) becomes 1, allowing:

A new input (a[i], b[i]) to enter the pipeline each cycle.

The FPGA to process one element per clock cycle.

Now, for 100 elements:

The first result is available after 3 cycles (pipeline fill).

Subsequent results appear every cycle.

### Total cycles: 101 (3+99-1) 
![Cycles with pipeline](../../resources/cycles%20with%20pipeline.png)

Pipelining transforms a slow, sequential design into a high-performance, cycle-accurate hardware pipeline capable of processing new data every clock cycle while reusing hardware resources efficiently.

This is the first and most essential optimization in Vitis HLS to achieve meaningful acceleration on FPGAs.