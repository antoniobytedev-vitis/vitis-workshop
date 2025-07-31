# Problems in Pipelining – Minimum II Constrained by Available Memory Ports
In FPGA designs using Vitis HLS, on-chip BRAM typically offers two ports, allowing two simultaneous memory accesses—either reads, writes, or both—in a single clock cycle. When loops in your design require more memory accesses per iteration than the number of available ports, this imposes a hard limit on how frequently new iterations can begin. Specifically, it increases the minimum achievable initiation interval (II), meaning that even if the computational logic could support processing data every cycle, the memory subsystem becomes a bottleneck.

## Example
Consider the following loop, which processes pairs of elements from an array and stores their sum:

```cpp
void accumulate_shifted(int a[256], int result[256]) {
    int temp = 0;
    for (int i = 0; i < 256; i++) {
        temp = a[i] + (temp >> 1);
        result[i] = temp;
    }
}
```
Each iteration requires two reads from the array a. Because BRAM provides two read ports, it is theoretically possible to execute one iteration per cycle. However, if the loop is not pipelined, each iteration executes sequentially, which makes the timing entirely dependent on memory access latency, and throughput is reduced.

## The Solution
To ensure that the loop takes full advantage of the memory’s capabilities, pipelining can be applied. With pipelining, multiple loop iterations overlap, and Vitis HLS will attempt to initiate new iterations every clock cycle. Whether this is successful depends on resource constraints like available memory ports.

```cpp
void accumulate_shifted(int a[256], int result[256]) {
    int temp = 0;
    for (int i = 0; i < 256; i++) {
        #pragma HLS PIPELINE II=2
        temp = a[i] + (temp >> 1);
        result[i] = temp;
    }
}
```

## Why Memory Port Count Affects II
The number of memory ports available directly impacts how quickly a loop can be pipelined. If your loop requires more memory accesses than can be served in a single cycle, Vitis HLS must delay the start of the next iteration, increasing the II. Understanding this limitation is essential when designing for high throughput.





