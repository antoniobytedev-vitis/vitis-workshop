void example(int a[1024],int result[1024]) 
{
    

    for(int i=0;i<128;i++)
    {
        result[i]=0;
        result[i]+=(a[i]+a[i+128]+a[i+1]);
    }
}