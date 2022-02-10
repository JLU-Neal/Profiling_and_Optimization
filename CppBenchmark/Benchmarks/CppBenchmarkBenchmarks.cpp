#include "../Source/CppBenchmark.hpp"
#include <benchmark/benchmark.h>
#include <iostream>
using namespace std;


static Table table;

static int cnt = 0;

static void DoSetup(const benchmark::State& state) {
  table = Table();
  int cols = state.range(0);
  int rows = state.range(1);
  
  for(int i = 0; i < rows; i++){
    vector<int> row;
    for(int j = 0 ; j < cols; j++){
      row.push_back(i%3+j);
    }
    table.addRow(row);

  }
  
  // cout<<table.toString()<<endl;
}

static void DummyBenchmark(benchmark::State& state) {
  for (auto _ : state){
    // cout<<cnt<<endl;
    // cnt++;
    int splitOnCols[state.range(0)];
    for(int i = 0; i < state.range(0); i++){
      splitOnCols[i] = i;
    }
    int size = (sizeof(splitOnCols)/sizeof(splitOnCols));
    cout<<size<<endl;
    vector<Table> subTable = table.splitOn(splitOnCols);
    // vector<Table>:: iterator itr;
    // cout<<"start iteration"<<endl;
    // for (itr = subTable.begin(); itr != subTable.end(); itr++)
    // {
    //   cout<<itr->toString()<<endl;
    // }

    // delete subTable;
    // delete itr;
  }
  
}
BENCHMARK(DummyBenchmark)->Args({1, 100})->Args({1, 1000})->Args({1, 10000})->Args({2, 100})->Args({2, 1000})->Args({2, 10000})->Setup(DoSetup); // NOLINT

BENCHMARK_MAIN();
