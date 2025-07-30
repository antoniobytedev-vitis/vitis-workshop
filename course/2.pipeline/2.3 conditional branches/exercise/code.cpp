#define N 1024
void offset(float in[N], float out[N]) {
    for (int i = 0; i < N; i++) {
        out[i] = in[i] + 10.0f;
    }
}
