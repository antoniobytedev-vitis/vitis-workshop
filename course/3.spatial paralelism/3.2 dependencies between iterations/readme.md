# Problems in Unrolling – Dependencies Between Iterations
In FPGA designs using Vitis HLS, loop unrolling is a powerful technique for increasing parallelism by executing multiple iterations of a loop simultaneously. However, unrolling requires that each iteration of the loop can execute independently without depending on the results of another iteration. If there are dependencies between iterations, Vitis HLS cannot safely unroll the loop, preventing you from fully utilizing the FPGA's parallel resources and limiting your achievable throughput.

## Example
Consider the following simple accumulation loop, which calculates the sum of all elements in an array:

```cpp
void sum_array(double in[256], int &sum) {
    sum = 0;
    
    for (int i = 0; i < 256; i++) {
        #pragma HLS UNROLL factor=2
        sum += in[i];
    }
}
```
In this example, each iteration depends on the sum value calculated in the previous iteration, creating a loop-carried dependency. Because the current iteration cannot proceed without the result of the previous iteration, unrolling this loop is not possible. Attempting to unroll this structure will result in either a synthesis error or Vitis HLS ignoring the unroll directive, leaving the loop to execute sequentially. This limits your design's ability to achieve high throughput and prevents the FPGA from executing multiple additions in parallel.

## The Solution
To allow unrolling, you need to restructure your code to remove dependencies between iterations. For accumulation patterns like this, you can use a parallel reduction tree to compute the sum without sequential dependencies, enabling unrolling(ignore the array_partition pragma as it'll be explained in later chapters).

```cpp
void sum_array_unrolled(double in[256], double &sum) {
double partial_sums[16] = {0};
#pragma HLS ARRAY_PARTITION variable=partial_sums type=cyclic factor=16
#pragma HLS ARRAY_PARTITION variable=in  type=cyclic factor=16

 
    for (int i = 0; i < 256; i++) {
        #pragma HLS UNROLL
        partial_sums[i % 16] += in[i];
    }

    sum=0;
    for (int j = 0; j < 16; j++) {
        #pragma HLS UNROLL
        sum += partial_sums[j];
    }

}
```

However, sometimes it's more optimal to fix it using pipeline or other directives. There is no one way solution for this issue.

```cpp
void sum_array_pipelined(double in[256], double &sum) {
    double partial_sums[16] = {0};
#pragma HLS ARRAY_PARTITION variable=partial_sums complete
#pragma HLS ARRAY_PARTITION variable=in complete

    #pragma HLS PIPELINE II=1
    for (int i = 0; i < 256; i++) {

        partial_sums[i % 16] += in[i];
    }

    sum=0;
    for (int j = 0; j < 16; j++) {
        #pragma HLS PIPELINE off
        sum += partial_sums[j];
    }

}
```

## Why Avoiding Dependencies Matters
If your loops have dependencies between iterations, you cannot unroll them, and your design will execute sequentially, wasting the FPGA’s parallel compute capabilities. By restructuring your code to eliminate these dependencies, you allow Vitis HLS to unroll your loops fully or partially, significantly improving throughput by allowing your design to process multiple data elements in parallel. This enables your FPGA to execute your workloads faster while maintaining efficient use of the hardware resources you have available.
