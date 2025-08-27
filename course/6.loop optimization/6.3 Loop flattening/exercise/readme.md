# Task
In FPGA designs, image-processing algorithms often use nested loops to process pixels row by row. However, if the loop structure is imperfect  Vitis HLS cannot flatten them into a single loop. This adds overhead cycles during loop transitions, hurting throughput.

Your task is to identify and fix this inefficiency by removing the problematic lines and using loop flattening and pipelining.
## Finished Table