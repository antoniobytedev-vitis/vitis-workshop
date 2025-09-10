#define N 256

int dot_product(int a[N], int b[N]) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        #pragma HLS PIPELINE II=1
        #pragma HLS UNROLL factor=4
        sum += a[i] * b[i];
    }
    return sum;
}