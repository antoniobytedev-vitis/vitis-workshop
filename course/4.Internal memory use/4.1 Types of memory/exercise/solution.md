
# SOLUTION

```cpp
void top_function(int[256] vitis)
{
    #pragma HLS INTERFACE m_axi port=vitis
    int is = 0;
    int[1024] fun;
}
```
In this tutorial we won't put much focus on external memory but it's crucial to identify all memory types when designing an fpga.