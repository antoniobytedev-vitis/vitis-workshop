void scalar_example(int scalar, int* out) {
#pragma HLS INTERFACE s_axilite port=scalar bundle=control
#pragma HLS INTERFACE m_axi port=out bundle=gmem
#pragma HLS INTERFACE s_axilite port=return bundle=control

    out[0] = scalar * 5;
}