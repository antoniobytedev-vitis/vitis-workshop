<<<<<<< Updated upstream
#define ROWS 8
#define COLS 64
void datapath1(int A[ROWS][COLS], int B[ROWS][COLS]) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=16
            B[r][c] = A[r][c] * 2;
        }
=======
#define N 128

void partition_exercise_opt(int A[N], int B[N]) {
    for (int i = 0; i < N - 2; i++) {
        #pragma HLS PIPELINE II=1
        int sum = A[i] + A[i + 1] + A[i + 2];
        B[i] = sum;
>>>>>>> Stashed changes
    }
}