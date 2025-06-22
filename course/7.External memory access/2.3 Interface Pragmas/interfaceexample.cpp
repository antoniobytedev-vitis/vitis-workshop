void interface_example(int* A, int b, hls::stream<int>& in_stream) {
#pragma HLS INTERFACE m_axi port=A offset=slave bundle=gmem
#pragma HLS INTERFACE s_axilite port=b bundle=control
#pragma HLS INTERFACE axis port=in_stream
#pragma HLS INTERFACE s_axilite port=return bundle=control

    int x = in_stream.read();
    A[0] = x + b;
}