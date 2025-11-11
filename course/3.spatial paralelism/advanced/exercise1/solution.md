# Solution
```cpp
#define N 16

void matrix_inner_unroll(int in[N][N],int out[N][N])
{
    for(int i=0;i<N;i++)
    {
        #pragma HLS PIPELINE off
        for(int j=0;j<N;j++)
        { 
            #pragma HLS UNROLL
            #pragma HLS PIPELINE off
            out[j][i]=in[i][j]*2;
        }
    }
}

void matrix_outer_unroll(int in[N][N],int out[N][N])
{
    for(int i=0;i<N;i++)
    {
        #pragma HLS UNROLL
        #pragma HLS PIPELINE off
        for(int j=0;j<N;j++)
        { 
            #pragma HLS PIPELINE off
            out[j][i]=in[i][j]*2;
        }
    }
}
```
Unrolling the inner loop is the most efficient because by doing this we copy the inner logic of the loop, so we get N*latency cycles. However, if we choose to unroll the outer loop we get N loops of N iterations with its latency, because we aren't pipelining choosing the former option is much more efficient.
# Finished table
| Metric                        | **No unroll** | **Unroll inner** | **Unroll outer** |
| ----------------------------- | ---------------------- | ------------------------------- | ---------------------------------- |
| **Latency in second loop (cycles)**    |                      |                              |                                   |
| **LUTs Used**                 |                  |                               |                                    |
| **FFs Used**                  |                    |                                 |                              |
| **DSPs Used**                 |                     |                               |                                   |
|