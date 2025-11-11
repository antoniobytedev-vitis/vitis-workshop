#define N 32

void matmul(int mat1[N][N], int mat2[N][N], int result[N][N]) {
    
    #pragma HLS ARRAY_PARTITION variable=mat1 dim=2 type=complete
    #pragma HLS ARRAY_PARTITION variable=mat2 dim=2 type=complete
    #pragma HLS ARRAY_PARTITION variable=result dim=2 type=complete

    row:for(int i=0;i<N;i++)
    {
        col:for(int j=0;j<N;j++)
        {
            result[i][j]=0;
            product:for(int k=0;k<N;k++)
            {      
                result[i][j] += mat1[i][k]*mat2[k][j];
            }
        }
    }
}