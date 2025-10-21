Pipelining is one of the most powerful features in HLS for increasing performance. This section dives into #pragma HLS PIPELINE and the concept of initiation interval (II), showing how to turn sequential loops into deeply pipelined hardware stages. We’ll also discuss how dependencies and loop structure affect pipeline efficiency.


Las siguientes carpetas contienen:
- 2.1 Explicacion de qué es el pipeline y ejercicio básico
- 2.2 Explicación de que no siempre se puede conseguir II=1 pero que aun así es importante usar pipeline. Y ejercicio para elegir el II mínimo sin que haya conflictos de memoria.
- 2.3 Es un poco más nicho pero esta sección se basa en eliminar dependencias falsas que pueden ocurrir a la hora del pipeline.
- 2.4 Explica la diferencia entre hacer pipeline en el bucle más interno o en el de fuera.
- Advanced: he escogido 3 ejercicios, el primero es de elegir si hacer pipeline dentro o fuera del bucle y comparar los resultados, el segundo de eliminar ifs reemplazandolos por operadores ternarios para ver cómo influye al rendimiento y el último es otro ejercicio de pipeline dentro o fuera pero esta vez con un bucle de tamaño variable.
