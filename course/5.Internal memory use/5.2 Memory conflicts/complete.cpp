//Complete
void example(int a[256],int result[128]) 
{
#pragma HLS ARRAY_PARTITION variable=a type=complete
    for(int i=0;i<128;i++)
    {
        result[i] =0;
        result[i]+=(a[i]+a[i+128]+a[i+1]);
    }
}

//Block
void example2(int a[256],int result[128]) 
{
#pragma HLS ARRAY_PARTITION variable=a type=block factor=2
    for(int i=0;i<128;i++)
    {
        result[i] =0;
        result[i]+=(a[i]+a[i+128]+a[i+1]);
    }
}
//Cyclic
void example3(int a[256],int result[128]) 
{
#pragma HLS ARRAY_PARTITION variable=a type=cyclic factor=2
    for(int i=0;i<128;i++)
    {
        result[i] =0;
        result[i]+=(a[i]+a[i+128]+a[i+1]);
    }
}