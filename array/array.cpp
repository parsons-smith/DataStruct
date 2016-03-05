/************************************************************
Copyright:  wust
Author: sean
Date:  2016-03-01
Description:  self define array
**************************************************************/
#include <string>
#include <iostream>
using namespace std;

template<class DataType>
class Array
{
public:
    Array(int size);
    ~Array();
    inline DataType &operator [ ](int index);
    void changeSize(int newSize);
    inline int length() const;
    string err() const;
private:
    DataType *elements;
    int capacity;
    DataType dud;
    int errorCode;
};

template<class DataType>
Array<DataType>::Array(int size)
{
    if(size < 1){
        capacity = 1;
        errorCode = 1;
    }else{
        capacity = size;
        errorCode = 0;
    }
    elements = new DataType [capacity];
}

template<class DataType>
Array<DataType>::~Array()
{
    delete [] elements;
}


template<class DataType>
inline DataType &Array<DataType>::operator [](int index)
{
#ifdef DEBUG_ARRAY
    if(index < 0 || index >= capacity){
        errorCode |= 2;
        return dud;
    }
#endif
    return elements[index];
}

template<class DataType>
void Array<DataType>::changeSize(int newSize)
{
    if(newSize <1 )
    {
        errorCode |= 4;
        return ;
    }
    DataType *newArray = new DataType[newSize];
    int limit = (newSize > capacity)?capacity:newSize;
    for(int i=0; i< limit; i++)
        newArray[i] = elements[i];
    delete [] elements;
    elements = newArray;
    capacity = newSize;
}


template<class DataType>
inline int Array<DataType>::length() const
{
    return capacity;
}


template<class DataType>
string Array<DataType>::err() const
{
    if(errorCode == 0)
        return "No error.\n";
    string errorMessage = "";
    if(errorCode&1){
        errorMessage += "Nonpositive size passed into constructor,so\n";
        errorMessage += "the capacity was set to 1 by default.\n";
    }
    if(errorCode&2){
        errorMessage += "Index out of range.\n";
    }
    if(errorCode&4){
        errorMessage += "Nonpositive size passed into changeSize,so\n";
        errorMessage += "the size of the array was not changed.\n";
    }
    return errorMessage;
}


int main(){
    Array<string> a(10);
    for (int i = 0; i < 10 ; i++){
        a[i] = "xxx";
    }
    for (int i = 0; i < 10 ; i++){
        cout<<a[i]<<"  ";
    }
    cout<<endl;
    return 0;
}
