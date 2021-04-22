#ZBench

A simple microbenchmarking library that I built to learn more about measuring performance.

```c++
#include <zbench/ZBench.h>

BENCH(TestName, MyFunction);

ZBENCH_MAIN
```

##Build Instructions
Requires git, CMake 3.0.0 or greater, and a C++ compiler that supports at least C++11. 
```bash
git clone https://github.com/zgalvin/ZBench.git

mkdir build && cd build

cmake -S .. -B .

cmake --build .
```

##Usage

Coming soon.