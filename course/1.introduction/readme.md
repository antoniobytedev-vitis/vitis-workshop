# Creating a Vitis HLS Project and Running C Synthesis — Step-by-step

This section describes, in a sequence of concrete steps, how to create a Vitis HLS project, configure its settings, perform C simulation and run C synthesis.

## A. Preparatory Remarks

Before starting a project in Vitis HLS, ensure the following:

- Source files (`.cpp/.c/.h`) and an optional **C testbench** file are available in a known folder.  
- The **top-level function** (the function to be synthesized) must be implemented in the sources.  
- Loop bounds and array sizes used for synthesis should ideally be **compile-time constants**.  
- If using command-line flow, a terminal with access to the `vitis_hls` executable must be available.  
- Preserve synthesis outputs — results and reports are stored under the **solution directory**.  


## B. Creating a New Project (GUI Flow)

### 1. Launch Vitis HLS
Open the Vitis HLS application.

### 2. Create a New Project
Navigate to:
File → New Component → HLS
