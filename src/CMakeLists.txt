
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
find_package(Eigen REQUIRED)
find_package(CUDA REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG -O3 -march=native -Wno-deprecated-declarations")
set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -G -gencode arch=compute_30,code=sm_30")

include_directories(multcompare ${Eigen_INCLUDE_DIRS})

cuda_include_directories(${PROJECT_SOURCE_DIR})

cuda_compile(CUST_CPU_O cust-cpu.cu OPTIONS ${CUDA_FLAGS})
cuda_compile(CUST_GPU_O cust-gpu.cu OPTIONS ${CUDA_FLAGS})
cuda_compile(CUBLAS_GPU_O cublas.cu OPTIONS ${CUDA_FLAGS})

cuda_add_executable(multcompare
  main.cpp
  reader.cpp
  benchmark.cpp
  random.cpp
  util.cpp
  algorithm.cpp
  simple.cpp
  blas.cpp
  strassen.cpp
  boost.cpp
  eigend.cpp
  eigens.cpp
  ${CUST_CPU_O}
  ${CUST_GPU_O}
  ${CUBLAS_GPU_O})

cuda_add_cublas_to_target(multcompare)

set_target_properties(multcompare PROPERTIES COMPILE_FLAGS "-std=c++11")
target_link_libraries(multcompare ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})
