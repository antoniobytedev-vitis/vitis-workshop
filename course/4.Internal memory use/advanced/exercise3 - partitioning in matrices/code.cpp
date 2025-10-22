#define ROWS 8
#define COLS 64
<<<<<<< Updated upstream
void datapath1(int A[ROWS][COLS], int B[ROWS][COLS]) {
=======
void top_function(int A[ROWS][COLS], int B[ROWS][COLS]) {
>>>>>>> Stashed changes
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            #pragma HLS PIPELINE II=1
            #pragma HLS UNROLL factor=16
            B[r][c] = A[r][c] * 2;
        }
    }
}