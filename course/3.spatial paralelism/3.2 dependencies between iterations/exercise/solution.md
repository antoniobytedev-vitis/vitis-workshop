

```cpp
void cumulative_sum(double in[256], double &sum) {
double partial_sums[16] = {0};
 
    for (int i = 0; i < 256; i++) {
        #pragma HLS UNROLL
        partial_sums[i % 16] += in[i]-(i%2)*2;
    }

    sum=0;
    for (int j = 0; j < 16; j++) {
        #pragma HLS UNROLL
        sum += partial_sums[j];
    }

}
```