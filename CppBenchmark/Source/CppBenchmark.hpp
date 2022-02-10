#include <unordered_map>
#include <vector>
#include <iostream>
#include<sstream>
using namespace std;

void printHelloWorld();
class Table
{
private:
    /* data */
    vector<vector<int>>* table;
public:
    Table();
    Table(vector<vector<int>>* table);
    void addRow(vector<int> row);
    string toString();
    vector<Table> splitOn(int cols[]);
    ~Table();
};


