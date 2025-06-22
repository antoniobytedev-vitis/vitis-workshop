void mem_io_example(int* A, int* B) {
#pragma HLS INTERFACE m_axi port=A bundle=gmem
#pragma HLS INTERFACE m_axi port=B bundle=gmem
#pragma HLS INTERFACE s_axilite port=return bundle=control

    B[0] = A[0] + 1;
}