# Problems Accessing Memory – Data Bus Underutilization
In FPGA designs using Vitis HLS, memory bandwidth is often a bottleneck. Modern FPGA systems frequently use wide memory buses (e.g., 16-bit, 32-bit, or 64-bit AXI buses) to transfer data efficiently. However, poor memory layout can lead to underutilization of these buses, reducing performance despite available bandwidth.

## The Problem
Consider an FPGA connected to memory with a 16-bit data bus, but your algorithm uses:
```c
char data[256]; // 8-bit elements
```
Without any optimization:

Each read or write accesses only 8 bits of the 16-bit bus.

50% of the bandwidth is wasted on every transfer.

If your algorithm requires high throughput, this limitation can prevent the loop from achieving II=1 (full pipelining).

### example 1
```cpp
void process(char data[256], char out[256]) {
#pragma HLS PIPELINE
    for (int i = 0; i < 256; i++) {
        out[i] = data[i] + 1;
    }
}

```
Each cycle, only 1 byte (8 bits) is transferred on a 16-bit bus.

You require 256 cycles to process the entire array.

The hardware is underutilized, and throughput is limited.

## The Solution: Using ARRAY_RESHAPE
By using #pragma HLS ARRAY_RESHAPE, you can reorganize the array layout to group multiple elements into a single wider memory word. This allows the hardware to utilize the full width of the bus in each transfer, improving throughput and reducing stalls.

```cpp
void process(char data[256], char out[256]) {
#pragma HLS ARRAY_RESHAPE variable=data factor=2 dim=1 type=block
#pragma HLS ARRAY_RESHAPE variable=out factor=2 dim=1 type=block
#pragma HLS PIPELINE
    for (int i = 0; i < 256; i++) {
        out[i] = data[i] + 1;
    }
}

```
What this does:

factor=2 groups 2 char elements (2×8 bits = 16 bits).

Now, the FPGA can read or write 16 bits per cycle, matching the bus width.

This effectively doubles your memory throughput without increasing resource usage.

### Different types of array reshape
There are 3 main types of array partitioning in Vitis Hls. Let's take a look at possible solutions to last section's problem.

### Block
This separates the memory in n adjacent blocks. 
```cpp 
void example2(int a[256],int result[64]) 
{
 #pragma HLS ARRAY_PARTITION variable=a type=block factor=2
    for(int i=0;i<64;i++)
    {   
        result[i] = a[i]+a[i+1]+a[i+2];
    }
}
```
This will result in storing a in two separate memories. One that stores a[0] to a [127] and another that stores a[128] to a[256]. However this will not fix our problem, as a[i], a[i+1] and a[i+2] are **still on the same memory**.
### Complete
This stores each separate element of the array into flip-flops. Making them independent from each other.
```cpp 
void example2(int a[256],int result[64]) 
{
 #pragma HLS ARRAY_PARTITION variable=a type=complete
    for(int i=0;i<64;i++)
    {   
        result[i] = a[i]+a[i+1]+a[i+2];
    }
}
```
Even though this fixes our problem, it also increases the resources needed inmensely, so doing a complete partitioning is not often recommended if throughput isn't your only priority.

### Cyclic
This separates the memory in n blocks but alternating their elements. For example:
```cpp 
void example2(int a[256],int result[64]) 
{
 #pragma HLS ARRAY_PARTITION variable=a type=cyclic factor=2
    for(int i=0;i<64;i++)
    {   
        result[i] = a[i]+a[i+1]+a[i+2];
    }
}
```
Will store a[0],a[2],a[4]... in one memory and a[1],a[3],a[5] in the other. As a[i] and a[i+1] are now in different memories we can access every element we need while still being under 3 accesses to each memory per cycle.

Cyclic partitioning tends to be the most efficient way to increase throughput as it doesn't increment the area as much as a complete partitioning.

# Assignment
We want to choose the most efficient memory partition for our FPGA. Partition the variable a using each of the methods explained here with a factor of 2.

* Run synthesis for each variant.

* Compare initiation interval (II) and resource usage in the report.

* Observe how ARRAY_PARTITION improves throughput