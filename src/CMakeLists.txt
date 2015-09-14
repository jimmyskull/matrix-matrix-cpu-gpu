
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
find_package(Eigen REQUIRED)

add_executable(multcompare
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
  eigens.cpp)

include_directories(multcompare ${Eigen_INCLUDE_DIRS})
target_link_libraries(multcompare ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})
