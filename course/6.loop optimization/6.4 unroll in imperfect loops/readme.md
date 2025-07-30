# Problems in Loops - Unrolling in semi-perfect and imperfect loops

## Perfect loops
In perfect loops, unrolling works exactly as intended because the tool knows the loop bounds at compile time and there are no operations interfering between nested loops. Vitis HLS can replicate the hardware required for each unrolled iteration, allowing the FPGA to execute multiple operations in parallel and reducing the total number of cycles significantly. For example, in the following perfect loop structure, unrolling by a factor of 8 will let the design compute 8 additions in parallel per cycle, reducing latency while efficiently utilizing FPGA resources.

```cpp
void add_arrays(int a[256], int b[256], int c[256]) {
    for (int i = 0; i < 256; i++) {
#pragma HLS UNROLL factor=8
        c[i] = a[i] + b[i];
    }
}
```
## Semi perfect loops
In semi-perfect loops, the inner loop typically has a fixed bound, while the outer loop has a variable runtime-determined bound. In these cases, unrolling is possible for the inner loop, as its bounds are known at synthesis time, enabling parallelism where it is most impactful. However, unrolling the outer loop is not possible since the tool does not know the number of iterations at compile time. For example, in the following semi-perfect loop, unrolling the inner loop by a factor of 4 will enable 4 multiplications to happen in parallel, while the outer loop executes sequentially according to the runtime variable rows.

```cpp
void scale_matrix(int a[64][64], int c[64][64], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 64; j++) {
#pragma HLS UNROLL factor=4
            c[i][j] = a[i][j] * 5;
        }
    }
}
```
## Imperfect loops
In imperfect loops, unrolling becomes impractical. Imperfect loops often have operations such as preprocessing steps or function calls between nested loops, or they may contain variable loop bounds that depend on runtime values, preventing Vitis HLS from safely replicating the operations in parallel. Attempting to unroll such loops typically leads to synthesis warnings and has no impact on performance. For instance, in the example below, the call to preprocess_row(i) outside the inner loop makes this loop structure imperfect, and the unroll directive on the inner loop will be ignored by Vitis HLS.

```cpp
void process_matrix(int a[64][64], int c[64][64]) {
    for (int i = 0; i < 64; i++) {
        preprocess_row(i);
        for (int j = 0; j < 64; j++) {
#pragma HLS UNROLL factor=4
            c[i][j] = a[i][j] + 1;
        }
    }
}
```
To enable unrolling in cases where your loop is currently imperfect, it is necessary to restructure your design so that computations happen inside the innermost loop, ensuring the bounds are fixed and there are no interfering operations. By doing so, Vitis HLS will be able to apply unrolling, allowing you to reduce latency and increase throughput while making full use of your FPGA’s parallel computation capabilities.