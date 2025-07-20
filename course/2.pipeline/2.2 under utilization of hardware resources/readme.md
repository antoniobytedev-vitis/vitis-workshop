# Problems in pipelining – Underutilization of Hardware When Accessing 2-Port BRAM
In FPGA designs using Vitis HLS, on-chip BRAM (block RAM) typically offers 2 ports, allowing two simultaneous reads or writes per cycle. However, if your loop accesses this memory sequentially, it underutilizes the available ports, leaving one or both idle for many cycles, limiting potential throughput and wasting FPGA resources.

```cpp
void sum_pairs(int a[256], int result[128]) {
    for (int i = 0; i < 128; i++) {
        result[i] = a[2 * i] + a[2 * i + 1];
    }
}

```
What happens:

Each iteration reads a[2 * i] and a[2 * i + 1] and sums them.

Without pipelining:

* The design reads two values per iteration sequentially.

* Only one iteration executes at a time.

* If the adder takes 1 cycle, and reads are scheduled conservatively:

* Each iteration takes 2 cycles.

* The second BRAM port may remain idle depending on how the reads are scheduled.

## The solution
you instruct Vitis HLS to pipeline the loop, allowing:

* Multiple iterations to overlap.

* The BRAM to issue new read commands every cycle, maintaining both ports active.

* The adder to compute sums every cycle without idle time.

```cpp
void sum_pairs_pipelined(int a[256], int result[128]) {
#pragma HLS PIPELINE
    for (int i = 0; i < 128; i++) {
        result[i] = a[2 * i] + a[2 * i + 1];
    }
}
```
* The two BRAM ports remain active every cycle.

* The adder is utilized every cycle.

* Results are produced every cycle, achieving II = 1

