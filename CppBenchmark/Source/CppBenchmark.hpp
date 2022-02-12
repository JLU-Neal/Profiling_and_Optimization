#include <unordered_map>
#include <vector>
#include <iostream>
#include<sstream>
#include<numeric>
#include<string>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

const string& smallIntToString(unsigned int val);
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
    const string toString();
    bool operator == (const SlicedTable& a) const;
    string getSliceName() const;
    vector<vector<int>*>* getGroupedRows() const;

    ~SlicedTable();
};

class SlicedTableGroup
{
private:
    vector<SlicedTable>* vtr_slt;
public:
    SlicedTableGroup();
    SlicedTableGroup(vector<SlicedTable>& vtr_slt);
    bool operator == (const SlicedTableGroup& a) const;
    vector<SlicedTable>* getVTR_SLT() const;
    string toString() const;
    ~SlicedTableGroup();
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
    SlicedTableGroup splitOn(vector<int>& cols);
    ~Table();
};
