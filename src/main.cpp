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

static void test(const reader::Entry& entry, core::Benchmark& bench,
  core::Algorithm&  alg) {
    alg.Init(entry);
    bench.measure([&](){ alg.Compute(); });
    std::cout << alg.name() << ": " << bench.duration() << "ms" << std::endl;
    alg.Finalize();
}

int main(void) {
  reader::FileList files("../data/list.txt");

  core::Benchmark bench;

  std::cout << "Processing " << files.count() << " files\n";
  for (const reader::Entry& entry : files) {
    std::cout << entry.str() << std::endl;

    core::SimpleSqMult simple;
    core::BLASSqMult blas;
    core::StrassenSqMult strassen;
    core::BoostSqMult boost;
    core::EigenDenseSqMult eigend;
    core::EigenSparseSqMult eigens;
    test(entry, bench, simple);
    test(entry, bench, blas);
    test(entry, bench, eigend);
    test(entry, bench, eigens);
    test(entry, bench, strassen);
    test(entry, bench, boost);
  }

  return 0;
}
