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
    for(rowPtr = this->table->begin(); rowPtr < this->table->end(); rowPtr++){
        vector<int> row = *rowPtr;
        vector<int>::iterator elePtr;
        for(elePtr = row.begin(); elePtr < row.end(); elePtr++){
            ss<<*elePtr<<"   ";
        }
        ss<<endl;
    }
    ss<<"========="<<endl;
    return ss.str();
}

vector<Table> Table::splitOn(int cols[])
{
    // cout<<"Start Splitting~"<<endl;
    vector<vector<int>>::iterator rowPtr;
    unordered_map<string, vector<vector<int>>> subTables;
    for(rowPtr = this->table->begin(); rowPtr < this->table->end(); rowPtr++){
        vector<int> row = *rowPtr;
        stringstream ss;
        int size = (sizeof(cols)/sizeof(*cols));
        cout<<size<<endl;
        cout<<row.size()<<endl;
        for(int i = 0; i < size; i++){
            ss<<row[cols[i]]<<":";
        }
        // ss<<row[0]<<":"<<row[1];
        string key = ss.str();
        if(subTables.find(key)!=subTables.end())
        {
            subTables.at(key).push_back(row);
        }else{
            vector<vector<int>> subTable;
            subTable.push_back(row);
            subTables[key] = subTable;
        }
    }
    // cout<<"Split done"<<endl;
    // cout<<"split size:"<<subTables.size()<<endl;
    vector<Table> splitedTables;
    unordered_map<string, vector<vector<int>>>:: iterator itr;
    for (itr = subTables.begin(); itr != subTables.end(); itr++)
    {
        // cout<<"key: "<<itr->first<<endl;
        vector<vector<int>> rows = itr->second;
        // cout<<"rows: "<<endl;
        // for(int i = 0; i < rows.size(); i++){
        //     for(int j = 0; j < rows[i].size(); j++){
        //         cout<< rows[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }
        Table table(&(rows));
        splitedTables.push_back(table);
        // cout<<"Get table" <<endl;
        // cout<<rows.size()<<endl;
        // cout<< table.toString()<<endl;
    }
    return splitedTables;
}

Table::~Table()
{
    
}