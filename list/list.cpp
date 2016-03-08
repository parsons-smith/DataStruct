/************************************************************
Copyright:  wust
Author: sean
Date:  2016-03-01
Description:  list
**************************************************************/
#include <iostream>
using namespace std;

template<class DataType>
struct Node{
    DataType info;
    Node<DataType> *next;
};

template<class DataType>
class List
{
public:
    List();
    List(const List<DataType> &aplist);
    ~List();
    List<DataType> & operator =( const List<DataType> &rlist);
    void insert( const DataType element);
    bool first( DataType & listEl);
    inline bool getNext( DataType &listEl);
    bool find( const DataType &element);
    bool retrieve( DataType &element);
    bool replace( const DataType &newElement);
    bool remove( DataType &element);
    bool isEmpty() const;
    void makeEmpty();
    bool getSize(int &size);
    void inverse();
    void sort();
private:
    Node<DataType> *start;
    Node<DataType> *current;
    inline void deepCopy( const List<DataType> & original);
};

template <class DataType>
List<DataType>::List()
{
    start = current = NULL;
}


template <class DataType>
List<DataType>::List(const List<DataType> & aplist)
{
    deepCopy(aplist);
}


template <class DataType>
List<DataType>::~List()
{
    makeEmpty();
}


template <class DataType>
List<DataType> &List<DataType>::operator =( const List<DataType> &rlist)
{
    if( this == &rlist )
        return *this;
    makeEmpty();
    deepCopy(rlist);
    return *this;
}


template <class DataType>
void List<DataType>::insert(const DataType element)
{
    current = NULL;
    Node<DataType> *newNode = new Node<DataType>;
    newNode->info = element;
    newNode->next = start;
    start = newNode;
}


template <class DataType>
bool List<DataType>::first( DataType & listEl)
{
    if(start == NULL)
        return false;
    current = start;
    listEl = start->info;
    return true;
}


template <class DataType>
inline bool List<DataType>::getNext( DataType & listEl)
{
    if(current == NULL)
        return false;
    if(current->next == NULL){
        current = NULL;
        return false;
    }
    current = current->next;
    listEl = current->info;
    return true;
}


template <class DataType>
bool List<DataType>::find( const DataType &element)
{
    DataType item;
    if( !first(item))
        return false;
    do{
        if(item == element)
            return true;
    }while(getNext(item));
    return false;
}


template <class DataType>
bool List<DataType>::retrieve( DataType & element)
{
    if( !find(element))
        return false;
    element = current->info;
    return true;
}


template <class DataType>
bool List<DataType>::replace( const DataType & newElement)
{
    if(current == NULL)
        return false;
    current->info = newElement;
    return true;
}


template <class DataType>
bool List<DataType>::remove( DataType &element)
{
    current = NULL;
    if(start == NULL)
        return false;
    Node<DataType> *ptr = start;
    if(ptr->info == element){
        element = ptr->info;
        start = start->next;
        delete ptr;
        return true;
    }
    while(ptr->next != NULL ){
        if(ptr->next->info == element){
            Node<DataType> *tempPtr = ptr->next;
            element = tempPtr->info;
            ptr->next = tempPtr->next;
            delete tempPtr;
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

template <class DataType>
bool List<DataType>::isEmpty() const
{
    return start == NULL;
}

template <class DataType>
void List<DataType>::makeEmpty()
{
    while( start != NULL){
        current = start;
        start = start->next;
        delete current;
    }
    current = NULL;
}


template <class DataType>
inline void List<DataType>::deepCopy( const List<DataType> & original)
{
    start = current = NULL;
    if(original.start == NULL)
        return ;
    Node<DataType> *copyptr = start = new Node<DataType>;
    Node<DataType> *originalptr = original.start;
    copyptr->info = originalptr->info;
    if( originalptr == original.current)
        current = copyptr;
    while(originalptr->next != NULL){
        originalptr = originalptr->next;
        copyptr->next = new Node<DataType>;
        copyptr = copyptr->next;
        copyptr->info = originalptr->info;
        if(originalptr == original.current)
            current = copyptr;
    }
    copyptr->next = NULL;
}

template <class DataType>
bool List<DataType>::getSize( int &size)
{
    size = 0;
    Node<DataType> *ptr = start;
    while(ptr != NULL){
        size++;
        ptr = ptr->next;
    }
    return true;
}


template <class DataType>
void List<DataType>::inverse()
{
    current = NULL;
    Node<DataType> *p1 = NULL, *p2 = NULL;
    while(start != NULL)
    {
        p2 = start->next;
        start->next = p1;
        p1 = start;
        start = p2;
    }
    start =  p1;
}

template <class DataType>
void List<DataType>::sort()
{
    Node<DataType> *p = NULL;
    for(current = start; current != NULL; current = current->next){
        for(p = current->next; p != NULL; p = p->next){
            if(current->info > p->info){
                p->info = p->info + current->info;
                current->info = p->info - current->info;
                p->info = p->info - current->info;
            }
        }
    }
    current = NULL;
}

int main(){
    List<int> l;
    for(int i = 0; i< 10; i++){
        l.insert(i);
    }
    int x;
    cout<<"traversal"<<endl;
    l.first(x);
    cout<< x << "   ";
    for(;l.getNext(x);){
        cout<< x << "   ";
    }
    l.getSize(x);
    cout<<endl<<x<<endl;

    cout<<"sort"<<endl;
    l.sort();
    l.first(x);
    cout<< x << "   ";
    for(;l.getNext(x);){
        cout<< x << "   ";
    }
    l.getSize(x);
    cout<<endl<<x<<endl;

    cout<<"inverse"<<endl;
    l.inverse();
    l.first(x);
    cout<< x << "   ";
    for(;l.getNext(x);){
        cout<< x << "   ";
    }
    l.getSize(x);
    cout<<endl<<x<<endl;

    cout<<"delete"<<endl;
    l.first(x);
    l.getNext(x);
    l.getNext(x);
    l.remove(x);

    l.first(x);
    cout<< x << "   ";
    for(;l.getNext(x);){
        cout<< x << "   ";
    }
    l.getSize(x);
    cout<<endl<<x<<endl;
    return 0;
}
