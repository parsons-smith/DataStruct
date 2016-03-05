/************************************************************
Copyright:  wust
Author: sean
Date:  2016-03-01
Description:  stack(list)
**************************************************************/
#include <iostream>
using namespace std;

template<class DataType>
struct Node{
    DataType info;
    Node<DataType> *next;
    Node(DataType d){
        info = d;
        next = NULL;
    }
};

template<class DataType>
class Stack{
private:
    Node<DataType> *top,*current,*base;
public:
    Stack();
    Stack(const Stack<DataType> &orign);
    ~Stack();
    void Push(DataType element);
    bool Pop(DataType &element);
    int getSize();
    bool first(DataType &element);
    inline bool getNext(DataType &element);
    bool last(DataType &element);
    void makeEmpty();
};


template<class DataType>
Stack<DataType>::Stack()
{
    top = base = current = NULL;
}


template<class DataType>
Stack<DataType>::Stack(const Stack<DataType> &orign)
{
    makeEmpty();
    current = NULL;
    Node<DataType> *oritop = orign.top;
    if(NULL == oritop) return;
    Node<DataType> *newNode = Node<DataType>(oritop->info);
    top = base = newData;
    while(NULL != oritop->next){
        oritop = oritop->next;
        Node<DataType> *tNode = Node<DataType>(oritop->info);
        tNode->next = top;
        top = tNode;
    }
}

template<class DataType>
Stack<DataType>::~Stack(){
    makeEmpty();
}

template<class DataType>
void Stack<DataType>::Push(DataType element){
    current = NULL;
    Node<DataType> *newNode = new Node<DataType>(element);
    if(NULL == top)
        top = base = newNode;
    else{
        newNode->next = top;
        top = newNode;
    }
}

template<class DataType>
bool Stack<DataType>::Pop(DataType &element){
    current = NULL;
    if(NULL == top)
        return false;
    element = top->info;
    Node<DataType> *t = top;
    top = top->next;
    delete t;
    return true;
}

template<class DataType>
int Stack<DataType>::getSize(){
    int count = 0;
    Node<DataType> *t = top;
    while(t != base){
        t = t->next;
        count++;
    }
    return count;
}


template<class DataType>
bool Stack<DataType>::first(DataType &element){
    if(NULL == top)
        return false;
    current = top;
    element = top->info;
    return true;
}


template<class DataType>
inline bool Stack<DataType>::getNext(DataType &element){
    if(NULL == current || NULL == current->next)
        return false;
    current = current->next;
    element = current->info;
    return true;
}

template<class DataType>
bool Stack<DataType>::last(DataType &element){
    if(NULL == base)
        return false;
    current = base;
    element = base->info;
    return true;
}

template<class DataType>
void Stack<DataType>::makeEmpty(){
    if(NULL == top)
        return ;
    Node<DataType> *t;
    while(top != base){
        t = top;
        top = top->next;
        delete t;
    }
}


int main(){
    Stack<int> s;
    for(int i = 0; i < 10 ; i++){
        s.Push(i);
    }


    int x;
    s.first(x);
    cout<<x<<"   ";
    while(s.getNext(x)){
        cout<<x<<"    ";
    }
    cout<<endl;

    s.Pop(x);
    s.first(x);
    cout<<x<<"   ";
    while(s.getNext(x)){
        cout<<x<<"    ";
    }
    cout<<endl;
    return 0;
}
