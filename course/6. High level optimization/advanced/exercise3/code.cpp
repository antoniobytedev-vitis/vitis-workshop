#include <cmath>
void calculate_log(int x[128],int y[128]){
  #pragma HLS inline ?
  for(int j=0;j<128;j++)
         {
             #pragma HLS PIPELINE II=1
             x[j] = log(y[j]);
         }
}

void top_function(int input[128][128], int output[128][128]){
    #pragma HLS ARRAY_PARTITION variable=input dim=2 type=cyclic factor=4
    #pragma HLS ARRAY_PARTITION variable=output dim=2 type=cyclic factor=4

     for(int i=0;i<128;i++)
     {
         #pragma HLS UNROLL factor=8
         calculate_log(input[i], output[i]);
     }

}