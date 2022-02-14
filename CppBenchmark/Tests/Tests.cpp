#include "../Source/CppBenchmark.hpp"
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
using namespace std;


static Table table;


TEST_CASE( "SlicedTable operator ==", "[factorial]" ) {
    
    int cols = 2;
    int rows = 10;
    //initialize table
    for(int i = 0; i < rows; i++){
        vector<int> row;
        for(int j = 0 ; j < cols; j++){
            row.push_back(i%3+j);
        }
        table.addRow(row);

    }

    vector<int> input{0, 1};



    //initialize vector of slicedtables
    vector<vector<int>*>* rows0 = new vector<vector<int>*>();
    vector<int> rows0_0{1, 2};
    vector<int> rows0_1{1, 2};
    vector<int> rows0_2{1, 2};
    rows0->push_back(&rows0_0);
    rows0->push_back(&rows0_1);
    rows0->push_back(&rows0_2);
    string str0("1~2~");
    SlicedTable slt0(str0, *rows0);

    vector<vector<int>*>* rows1 = new vector<vector<int>*>();
    vector<int> rows1_0{1, 2};
    vector<int> rows1_1{1, 2};
    vector<int> rows1_2{1, 2};
    rows1->push_back(&rows1_0);
    rows1->push_back(&rows1_1);
    rows1->push_back(&rows1_2);
    string str1("1~2~");
    SlicedTable slt1(str1, *rows1);

    REQUIRE( slt0 == slt1);

    // REQUIRE( true);

}


TEST_CASE( "SlicedTableGroup operator ==", "[factorial]" ) {
    
    int cols = 2;
    int rows = 10;
    //initialize table
    for(int i = 0; i < rows; i++){
        vector<int> row;
        for(int j = 0 ; j < cols; j++){
            row.push_back(i%3+j);
        }
        table.addRow(row);

    }

    vector<int> input{0, 1};



    //initialize vector of slicedtables
    vector<vector<int>*>* rows0 = new vector<vector<int>*>();
    vector<int> rows0_0{1, 2};
    vector<int> rows0_1{1, 2};
    vector<int> rows0_2{1, 2};
    rows0->push_back(&rows0_0);
    rows0->push_back(&rows0_1);
    rows0->push_back(&rows0_2);
    string str0("1~2~");
    SlicedTable slt0(str0, *rows0);

    vector<vector<int>*>* rows1 = new vector<vector<int>*>();
    vector<int> rows1_0{1, 2};
    vector<int> rows1_1{1, 2};
    vector<int> rows1_2{1, 2};
    rows1->push_back(&rows1_0);
    rows1->push_back(&rows1_1);
    rows1->push_back(&rows1_2);
    string str1("1~2~");
    SlicedTable slt1(str1, *rows1);

    vector<SlicedTable> vtr_slt0{slt0};
    vector<SlicedTable> vtr_slt1{slt1};
    SlicedTableGroup sltGroup0(vtr_slt0);
    SlicedTableGroup sltGroup1(vtr_slt1);
    REQUIRE( sltGroup0 == sltGroup1);

}

TEST_CASE( "SplitOn", "[factorial]" ) {
    
    int cols = 2;
    int rows = 10;
    //initialize table
    for(int i = 0; i < rows; i++){
        vector<int> row;
        for(int j = 0 ; j < cols; j++){
            row.push_back(i%3+j);
        }
        table.addRow(row);

    }

    vector<int> input{0, 1};



    //initialize vector of slicedtables
    vector<vector<int>*>* rows0 = new vector<vector<int>*>();
    vector<int> rows0_0{1, 2};
    vector<int> rows0_1{1, 2};
    vector<int> rows0_2{1, 2};
    rows0->push_back(&rows0_0);
    rows0->push_back(&rows0_1);
    rows0->push_back(&rows0_2);
    string str0("1~2~");
    SlicedTable slt0(str0, *rows0);

    vector<vector<int>*>* rows1 = new vector<vector<int>*>();
    vector<int> rows1_0{2, 3};
    vector<int> rows1_1{2, 3};
    vector<int> rows1_2{2, 3};
    rows1->push_back(&rows1_0);
    rows1->push_back(&rows1_1);
    rows1->push_back(&rows1_2);
    string str1("2~3~");
    SlicedTable slt1(str1, *rows1);


    vector<vector<int>*>* rows2 = new vector<vector<int>*>();
    vector<int> rows2_0{0, 1};
    vector<int> rows2_1{0, 1};
    vector<int> rows2_2{0, 1};
    vector<int> rows2_3{0, 1};
    rows2->push_back(&rows2_0);
    rows2->push_back(&rows2_1);
    rows2->push_back(&rows2_2);
    string str2("0~1~");
    SlicedTable slt2(str2, *rows2);    

    vector<SlicedTable> vtr_slt{slt1, slt0, slt2};
    SlicedTableGroup stbGroup(vtr_slt);
    REQUIRE( table.splitOn(input) == stbGroup);


}