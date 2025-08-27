#define N 1024
void offset(float in[N], float out[N]) {
    for (int i = 0; i < N; i++) {
        out[i] = in[i] + 10.0f;
    }
}
void datapath1(int a[256], int b[128], int c[64], int out[256]) {
    // First loop: copy a to out
    loop1:for (int i = 0; i < 256; i++) {
        out[i] = a[i];
    }
    // Second loop: add c to out (first 64 elements)
    loop2:for (int j = 0; j < 64; j++) {
        out[j] += c[j];
    }
    // Third loop: add b to out (first 128 elements)
    loop3:for (int k = 0; k < 128; k++) {
        out[k] += b[k];
    }
}