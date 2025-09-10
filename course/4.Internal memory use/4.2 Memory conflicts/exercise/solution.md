# SOLUTION

```cpp
#define N 256

void dot_product_no_partition(int a[N], int b[N], int &result) {
    result = 0;
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
#pragma HLS UNROLL factor=4
        result += a[i] * b[i];
    }
}

// Dot product with cyclic partitioning
void dot_product_cyclic(int a[N], int b[N], int &result) {
#pragma HLS ARRAY_PARTITION variable=a cyclic factor=4 
#pragma HLS ARRAY_PARTITION variable=b cyclic factor=4 
    result = 0;
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
#pragma HLS UNROLL factor=4
        result += a[i] * b[i];
    }
}

// Dot product with block partitioning
void dot_product_block(int a[N], int b[N], int &result) {
#pragma HLS ARRAY_PARTITION variable=a block factor=4 
#pragma HLS ARRAY_PARTITION variable=b block factor=4 
    result = 0;
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
#pragma HLS UNROLL factor=4
        result += a[i] * b[i];
    }
}

// Dot product with complete partitioning
void dot_product_complete(int a[N], int b[N], int &result) {
#pragma HLS ARRAY_PARTITION variable=a complete 
#pragma HLS ARRAY_PARTITION variable=b complete 
    result = 0;
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE II=1
#pragma HLS UNROLL factor=4
        result += a[i] * b[i];
    }
}
```

## Complete table

| **Metric**                      | **Without partition** | **Cyclic factor=4** | **Block factor =4** | **Complete** 
|:-------------------------:|:---------------------:|:-------------------:|:-------------------:|:------------:
| **Total Latency(cycles)** |       132              |    68                 |    133                 |     68         |      |      |      |      |      |
| **LUTs used**             | 320                     |        325             |           685          |    2495          |      |      |      |      |      |
| **FFs used**              | 283                 |    501                 |     544                |     565         |      |      |      |      |      |
| **DSPs used**             |  6                   |     12                |                6     |        12      |      |      |      |      |      |

As you can see in the table because we only unrolled by a factor of 4, partitioning by a cyclic factor of 4 is the best option for performance in regards to resources used. Using block partitioning doesn't help us at all, since the memory isn't partitioned in a way the hardware can take advantage from it. Complete partitioning, on the other hand, let's us get the same number of cycles as with cyclic partitioning but with exponentially more resources.