#include <math.h>
#include <stdint.h>

#define N 256     // FFT size (must be power of 2)
#define PI 3.14159265358979323846
#define stages 8

// Vitis-friendly complex struct
typedef struct {
    float real;
    float imag;
} complex_t;

void fft(complex_t x[N], complex_t X[N]) {

    // Local buffer to avoid aliasing issues
    complex_t a[N];

    // Copy input
    copy_loop:
    for (int i = 0; i < N; i++) {
#pragma HLS PIPELINE
        a[i] = x[i];
    }

    // Bit-reversal permutation
    bitrev_loop:
    for (int i = 0; i < N; i++) {
        int rev = 0;
        int t = i;

        // Reverse 8 bits for N = 256 (log2(256) = 8)
        for (int j = 0; j < 8; j++) {
            rev = (rev << 1) | (t & 1);
            t >>= 1;
        }

        if (rev > i) {
            complex_t temp = a[i];
            a[i] = a[rev];
            a[rev] = temp;
        }
    }

    // Iterative FFT
    

stage_loop:
    for (int s = 1; s <= 8; s++) {

        int m = 1 << s;
        int half_m = m >> 1;

    butterfly_outer:
        for (int k = 0; k < N; k += m) {

        butterfly_inner:
            for (int j = 0; j < N; j++) {



                float angle = -2.0f * PI * j / m;
                float wr = cosf(angle);
                float wi = sinf(angle);

                complex_t t_val;
                complex_t u_val;

                u_val = a[k + j];

                float r = a[k + j + half_m].real;
                float i2 = a[k + j + half_m].imag;

                t_val.real = wr * r - wi * i2;
                t_val.imag = wr * i2 + wi * r;

                // Butterfly
                a[k + j].real          = u_val.real + t_val.real;
                a[k + j].imag          = u_val.imag + t_val.imag;

                a[k + j + half_m].real = u_val.real - t_val.real;
                a[k + j + half_m].imag = u_val.imag - t_val.imag;
            }
        }
    }

    // Copy results
    write_loop:
    for (int i = 0; i < N; i++) {
        X[i] = a[i];
    }
}
