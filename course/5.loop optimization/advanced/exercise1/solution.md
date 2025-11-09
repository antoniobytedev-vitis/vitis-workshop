# Solution
```cpp
#define N 128
void prevent_merge(int a[N][N], int b[N][N], int c[N][N]) {
int buffer[N][N];
#pragma HLS LOOP_MERGE
initialize:for(int i=0;i<N;i++)
{
    #pragma HLS PIPELINE off
    for(int j=0;j<N;j++)
    {
        #pragma HLS LOOP_FLATTEN off
        buffer[i][j]=a[i][j];
    }
}
main:for(int i=0;i<N;i++)
{
    #pragma HLS PIPELINE off
    buffer[i][i] = 1;
    for(int j=0;j<N;j++)
    {
        #pragma HLS LOOP_FLATTEN pff
        c[i][j]=buffer[i][j]+b[i][j];
    }
}
}
```
To merge a nested loop it first needs to be flattened. Normally this is done automatically but by turning it off manually we prevent the merging of loops.
## Finished Table
| Metric                        | **Without Flattening** | **With Flattening** 
| ----------------------------- | ---------------------- | ------------------------------- | 
| **Total Latency (cycles)**    |                      |                                 |                                    |
| **LUTs Used**                 |                        |                                 |                                    |
| **FFs Used**                  |                        |                                 |                                    |
|**BRAMs Used**||
|**DSPs Used**||