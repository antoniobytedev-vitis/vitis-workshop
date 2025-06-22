# Main issues
When designing FPGA-based systems using VITIS HLS, it is important to understand that while we are using c++ the underlying hardware imposes restrictions on us that are not normally present in the language.

Let's take a look at the following examples:
```cpp
void example1(int a[256],int result[64]) 
{
    for(int i=0;i<64;i++)
    {   
        result[i] = a[i]+a[i+1];
    }
}
```
```cpp
void example2(int a[256],int result[64]) 
{
    for(int i=0;i<64;i++)
    {   
        result[i] = a[i]+a[i+1]+a[i+2];
    }
}
```
They look pretty similar but when you run the c synthesis of the second one we get the following warning:

**WARNING: [HLS 200-885] The II Violation in module 'example2' (loop 'VITIS_LOOP_7_1'): Unable to schedule 'load' operation 32 bit ('a_load_1', example2.cpp:9) on array 'a' due to limited memory ports (II = 1). Please consider using a memory core with more ports or partitioning the array 'a'.**

But why is this?

## Limited accesses per cycle
BRAM and URAM are limited to **2 accesses per cycle**. 
```cpp
result[i] = a[i]+a[i+1]+a[i+2];
```
Here we try to access the same memory three times in the same cycle which leads to vitis not being able to optimize the system properly.



# The fix: Array Partitioning
Array partitioning is a feature in Vitis HLS that splits an array into smaller pieces (like putting slices of it into separate drawers). Each part gets its own memory block, which means more access ports.

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