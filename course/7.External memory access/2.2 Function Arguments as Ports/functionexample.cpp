void port_example(int a, int* A, int B[10]) {
#pragma HLS INTERFACE s_axilite port=a bundle=control
#pragma HLS INTERFACE m_axi port=A offset=slave bundle=gmem
#pragma HLS INTERFACE m_axi port=B offset=slave bundle=gmem
#pragma HLS INTERFACE s_axilite port=return bundle=control

    A[0] = a + B[0];
}