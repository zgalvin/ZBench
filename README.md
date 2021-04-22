#ZBench

A simple microbenchmarking library that I built to learn more about measuring performance.

```c++
#include <zbench/ZBench.h>

BENCH(TestName, MyFunction);

ZBENCH_MAIN
```

##Build Instructions

```bash
git clone https://github.com/zgalvin/ZBench.git

mkdir build && cd build

cmake -S .. -B .

cmake --build .
```