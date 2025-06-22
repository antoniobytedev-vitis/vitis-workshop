void axi_example(int* A, int scalar, hls::stream<int>& s_in, hls::stream<int>& s_out) {
#pragma HLS INTERFACE m_axi port=A bundle=gmem
#pragma HLS INTERFACE s_axilite port=scalar bundle=control
#pragma HLS INTERFACE axis port=s_in
#pragma HLS INTERFACE axis port=s_out
#pragma HLS INTERFACE s_axilite port=return bundle=control

    int temp = A[0] + scalar;
    s_out.write(temp);
}