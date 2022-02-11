#include "CppBenchmark.hpp"


using namespace std;


void printHelloWorld(){
    cout<<"Mother fucker i am back!";
}
Table::Table()
{
    this->table = new vector<vector<int>>();
}

Table::Table(vector<vector<int>>* table)
{
    this->table = table;
}

void Table::addRow(vector<int> row){
    this->table->push_back(row);

}

string Table::toString(){
    stringstream ss;
    vector<vector<int>>::iterator rowPtr;
    ss<<"========="<<endl;
    // cout<<this->table->size()<<endl;
    for(rowPtr = this->table->begin(); rowPtr < this->table->end(); rowPtr++){
        vector<int> row = *rowPtr;
        vector<int>::iterator elePtr;
        // cout<<row.size()<<endl;
        for(elePtr = row.begin(); elePtr < row.end(); elePtr++){
            ss<<"Row elements: "<<endl;
            ss<<*elePtr<<"   ";
        }
        ss<<endl;
    }
    ss<<"========="<<endl;
    return ss.str();
}

vector<SlicedTable> Table::splitOn(vector<int>& cols)
{
    // cout<<"Start Splitting~"<<endl;

    unordered_map<string, vector<vector<int>*>> subTables;
    // cout<<table->size()<<endl;
    for(int idx = 0; idx < this->table->size(); idx++){
        // cout<<idx<<endl;
        vector<int>& row = this->table->at(idx);
        // stringstream ss;
        string key="";
        for(int i = 0; i < cols.size(); i++){
            // ss<<row[cols[i]]<<":";
            key+=to_string(row[cols[i]])+"~";
        }
        // string key = ss.str();
        if(subTables.find(key)!=subTables.end())
        {
            subTables.at(key).push_back(&(row));
        }else{
            vector<vector<int>*> subTable;
            subTable.push_back(&(row));
            subTables[key] = subTable;
        }
    }
    // cout<<"Split done"<<endl;
    // cout<<"split size:"<<subTables.size()<<endl;
    vector<SlicedTable> splitedTables;
    unordered_map<string, vector<vector<int>*>>:: iterator itr;
    for (itr = subTables.begin(); itr != subTables.end(); itr++)
    {
        // cout<<"key: "<<itr->first<<endl;
        vector<vector<int>*>& rowsPtr = itr->second;
        // cout<<"rows: "<<endl;
        // for(int i = 0; i < rows.size(); i++){
        //     for(int j = 0; j < rows[i].size(); j++){
        //         cout<< rows[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }
        // Table table(&(rows));
        SlicedTable stb(itr->first, rowsPtr);
        splitedTables.push_back(stb);

        // cout<<stb.toString()<<endl;
    }



    vector<SlicedTable>:: iterator iter;
    // cout<<"start iteration"<<endl;
    // for (iter = splitedTables.begin(); iter != splitedTables.end(); iter++)
    // {
    //   cout<<iter->toString()<<endl;
    // }
    return splitedTables;
}

Table::~Table()
{
    // cout<<"destruct"<<endl;
}

SlicedTable::SlicedTable()
{

}

SlicedTable::SlicedTable(string sliceName, vector<vector<int>*>& groupedRows)
{
this->sliceName = sliceName;
this-> groupedRows = &(groupedRows);
}

SlicedTable::SlicedTable(const SlicedTable& stb)
{
    this->sliceName = stb.sliceName;
    this->groupedRows = new vector<vector<int>*> (stb.groupedRows->begin(), stb.groupedRows->end());
}

string SlicedTable::toString()
{
    vector<vector<int>*>::iterator itr;
    stringstream ss;
    ss<<this->sliceName<<endl;
    ss<<"============="<<endl;
    for(itr = this->groupedRows->begin(); itr != this->groupedRows->end(); itr++)
    {
        vector<int> table = *(*itr);
        ss<<"row: ";
        vector<int>::iterator itr;
        for(itr = table.begin(); itr != table.end(); itr++)
        {
            ss<<*itr<<" ";
        }
        ss<<endl;
    }
    ss<<"============="<<endl;
    return ss.str();
}

SlicedTable::~SlicedTable()
{

}