// Copyright © 2015, Paulo Urio.
#include <iostream>

#include "benchmark.hpp"
#include "reader.hpp"
#include "simple.hpp"
#include "blas.hpp"
#include "strassen.hpp"
#include "boost.hpp"
#include "eigend.hpp"
#include "eigens.hpp"
#include "cust-cpu.hpp"
#include "cust-gpu.hpp"
#include "cublas.hpp"
#include "armadillodense.hpp"
#include "armadillosparse.hpp"
#include "cusparse.hpp"

static void test(const reader::Entry& entry, core::Benchmark& bench,
  core::Algorithm&  alg) {
    alg.Init(entry);
    std::cout << alg.name() << ": " << std::flush;
    bench.Start();
    alg.Compute();
    bench.Stop();
    alg.Finalize();
    std::cout << bench.duration() << "ms" << std::endl;
}

int main(void) {
  reader::FileList files("../data/list.txt");

  core::Benchmark bench;

  std::cout << "Processing " << files.count() << " files\n";
  for (const reader::Entry& entry : files) {
    std::cout << entry.str() << std::endl;

    if (entry.vertices != 1000)
      continue;

    // core::Simple simple;
    core::BLAS blas;
    core::Strassen strassen;
    core::Boost boost;
    core::EigenDense eigend;
    core::EigenSparse eigens;
    core::CustCPU cust_cpu;
    core::CustGPU cust_gpu;
    core::CUBLAS cublas;
    core::ArmadilloDense armadense;
    core::ArmadilloSparse armasparse;
    core::CUSPARSE cusparse;
    // test(entry, bench, simple);
    test(entry, bench, blas);
    test(entry, bench, blas);
    // test(entry, bench, eigend);
    // test(entry, bench, eigens);
    // test(entry, bench, strassen);
    // test(entry, bench, boost);
    // test(entry, bench, cust_cpu);
    // test(entry, bench, cust_gpu);
    test(entry, bench, cublas);
    test(entry, bench, cublas);
    test(entry, bench, armadense);
    test(entry, bench, armadense);
    test(entry, bench, armasparse);
    test(entry, bench, armasparse);
    test(entry, bench, cusparse);
  }

  return 0;
}
