1.

2.

3.

4.
```cpp
#define order 5

void datapath1(float x[1024], float F[1024])
{

#pragma HLS ARRAY_PARTITION variable=x dim=1 type=cyclic factor=2
#pragma HLS ARRAY_PARTITION variable=F dim=1 type=cyclic factor=2
const float coef[order]={-3.4, 2, -1.25, 0.68, 1};
float sal;

 DataLoop: for (int i=0; i<1024; i++) {
    sal=0;
    #pragma HLS PIPELINE II=1
    #pragma HLS UNROLL factor=4
    evalLoop: for (int j=order-1; j>=0; j--){
    	sal=sal*x[i]+coef[j];
    }

    F[i]=sal;
 }
}
```

5.







# Finished table
| metric          | Baseline | Fully Iterative | Latency Reduction(Parallelization) |
| --------------- | -------- | --------------- | ---------------------------------- |
| Latency(Cycles) |     1072 |       46084          |       304                             |
| LUTs            |   1823       |      673           |       6990                             |
| FFs             |   2336       |       621          |           9004                         |
| DSPs            |       25   |         5        |                   100                 |
| BRAMs           |        0  |          0       |                       0             |