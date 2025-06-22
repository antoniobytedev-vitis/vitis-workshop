void stream_example(hls::stream<int>& in, hls::stream<int>& out) {
#pragma HLS INTERFACE axis port=in
#pragma HLS INTERFACE axis port=out
#pragma HLS INTERFACE s_axilite port=return bundle=control

    int val = in.read();
    out.write(val * 2);
}
