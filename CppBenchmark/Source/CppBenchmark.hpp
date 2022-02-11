#include <unordered_map>
#include <vector>
#include <iostream>
#include<sstream>
#include<numeric>
#include<string>
using namespace std;

void printHelloWorld();

class SlicedTable
{
private:
    /* data */
    string sliceName;
    vector<vector<int>*>* groupedRows;
public:
    SlicedTable();
    SlicedTable(string sliceName, vector<vector<int>*>& groupedRows);
    SlicedTable(const SlicedTable& stb);
    string toString();
    ~SlicedTable();
};

class Table
{
private:
    /* data */
    vector<vector<int>>* table;

public:
    friend class SlicedTable;
    Table();
    Table(vector<vector<int>>* table);
    void addRow(vector<int> row);
    string toString();
    vector<SlicedTable> splitOn(vector<int>& cols);
    ~Table();
};
