#include "CppBenchmark.hpp"


using namespace std;

static vector<string> smallNumbers{"0", "1", "2", "3", "4", "5", "6"};

const string& smallIntToString(unsigned int val) {
    return smallNumbers[val < smallNumbers.size() ? val : 0];
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
            ss<<"Row elements: "<<endl;
            ss<<*elePtr<<"   ";
        }
        ss<<endl;
    }
    ss<<"========="<<endl;
    return ss.str();
}

SlicedTableGroup Table::splitOn(vector<int>& cols)
{
    unordered_map<string, vector<vector<int>*>> subTables;
    for(int idx = 0; idx < this->table->size(); idx++){
        vector<int>& row = this->table->at(idx);
        string key="";
        for(int i = 0; i < cols.size(); i++){
            // key+=to_string(row[cols[i]]);
            key+=smallIntToString(row[cols[i]])+"~";
            // key+=lexical_cast(row[cols[i]]);
        }
        if(subTables.find(key)!=subTables.end())
        {
            subTables.at(key).push_back(&(row));
        }else{
            vector<vector<int>*> subTable;
            subTable.push_back(&(row));
            subTables[key] = subTable;
        }
    }
    vector<SlicedTable> splitedTables;
    unordered_map<string, vector<vector<int>*>>:: iterator itr;
    for (itr = subTables.begin(); itr != subTables.end(); itr++)
    {
        vector<vector<int>*>& rowsPtr = itr->second;
        SlicedTable stb(itr->first, rowsPtr);
        splitedTables.push_back(stb);
    }
    SlicedTableGroup stbGroup(splitedTables);
    return stbGroup;
}

Table::~Table()
{
    
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

const string SlicedTable::toString()
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


bool SlicedTable::operator == (const SlicedTable& a) const
{
    if(this->getSliceName() != a.getSliceName())
    {
        cout<<"left:"<<this->getSliceName()<<endl;
        cout<<"right"<<a.getSliceName()<<endl;
        return false;
    }
    return true;
}

string SlicedTable::getSliceName() const
{
    return this->sliceName;
}

vector<vector<int>*>* SlicedTable::getGroupedRows() const
{
    return this-> groupedRows;
}


SlicedTable::~SlicedTable()
{
}

SlicedTableGroup::SlicedTableGroup()
{
    
}

SlicedTableGroup::SlicedTableGroup(vector<SlicedTable>& vtr_slt)
{
    this->vtr_slt = new vector<SlicedTable>(vtr_slt.begin(), vtr_slt.end());
}

bool SlicedTableGroup::operator == (const SlicedTableGroup& a) const
{
    if(*(this->getVTR_SLT())==*(a.getVTR_SLT()))
    {
        return true;
    }
    return false;
}

vector<SlicedTable>* SlicedTableGroup::getVTR_SLT() const
{
    return this->vtr_slt;
}


string SlicedTableGroup::toString() const
{
    vector<SlicedTable>:: iterator itr;
    stringstream ss;
    ss<<"start iteration"<<endl;
    for (itr = this->vtr_slt->begin(); itr != this->vtr_slt->end(); itr++)
    {
        ss<<itr->toString()<<endl;
    }
    return ss.str();
}

SlicedTableGroup::~SlicedTableGroup()
{
    
}