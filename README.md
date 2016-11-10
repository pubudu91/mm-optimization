# mm-optimization
An assignment for Concurrent Programming module to explore various methods of optimizing matrix multiplication

To compile this project, you need to have CMake 3 or higher installed. To install CMake, follow the following instructions:

```
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:george-edison55/cmake-3.x
sudo apt-get update
sudo apt-get install cmake
```

To compile and build the project, create a directory for the build named "build" in the project root. 
Navigate to this build directory and enter the following commands:

```
cmake ..
make
```

You also need BLAS and OpenMP to run this program. 

To install BLAS: 
```sudo apt-get install libblas-dev```

If the build was successful, it will have created an executable file named "lab4_5_final" in the build directory.
To run the program, pass the following arguments: program_version (possible values: 1, 2, 3)

i.e: ```./lab4_5_final 1```

To run the various optimization based solutions, use the following format: ```./lab4_5_final 3 <optimized_version_no>```

optimized_version_no can be any number from 1-5. 
* 1 - Sequential i-k-j
* 2 - Parallel i-k-j
* 3 - BLAS Level 1
* 4 - BLAS Level 3
* 5 - Transposing matrix B
