void best_practice(int* A, int scalar, hls::stream<int>& out) {
#pragma HLS INTERFACE m_axi port=A bundle=gmem
#pragma HLS INTERFACE s_axilite port=scalar bundle=control
#pragma HLS INTERFACE axis port=out
#pragma HLS INTERFACE s_axilite port=return bundle=control

#pragma HLS PIPELINE II=1
    for (int i = 0; i < 8; i++) {
        int temp = A[i] + scalar;
        out.write(temp);
    }
}