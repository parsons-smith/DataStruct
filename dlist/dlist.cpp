/************************************************************
Copyright:  wust
Author: sean
Date:  2016-03-01
Description:  double way list
**************************************************************/

#include <iostream>
using namespace std;

template<class DataType>
struct Node{
    DataType info;
    Node<DataType> *pre;
    Node<DataType> *next;
    Node(DataType d){
        info = d;
        pre = NULL;
        next = NULL;
    }
};

template<class DataType>
class DList
{
public:
    DList();
    DList(const DList<DataType> &apDList);
    ~DList();
    DList<DataType> & operator =( const DList<DataType> &rDList);
    void insert( const DataType element);
    bool first( DataType & DListEl);
    inline bool getNext( DataType &DListEl);
    inline bool getPre( DataType &DListEl);
    bool find( const DataType &element);
    bool retrieve( DataType &element);
    bool replace( const DataType &newElement);
    bool remove( DataType &element);
    bool isEmpty() const;
    void makeEmpty();
    bool getSize(int &size);
private:
    Node<DataType> *head;
    Node<DataType> *current;
    inline void deepCopy( const DList<DataType> & original);
};

template <class DataType>
DList<DataType>::DList()
{
    head = current = NULL;
}


template <class DataType>
DList<DataType>::DList(const DList<DataType> & apDList)
{
    deepCopy(apDList);
}


template <class DataType>
DList<DataType>::~DList()
{
    makeEmpty();
}


template <class DataType>
DList<DataType> &DList<DataType>::operator =( const DList<DataType> &rDList)
{
    if( this == &rDList )
        return *this;
    makeEmpty();
    deepCopy(rDList);
    return *this;
}


template <class DataType>
void DList<DataType>::insert(const DataType element)
{
    current = NULL;
    Node<DataType> *newNode = new Node<DataType>(element);
    if(!head){
        head = newNode;
    }else{
        newNode->next = head;
        head->pre = newNode;
        head = newNode;
    }
}


template <class DataType>
bool DList<DataType>::first( DataType & DListEl)
{
    if(head == NULL)
        return false;
    current = head;
    DListEl = head->info;
    return true;
}


template <class DataType>
inline bool DList<DataType>::getNext( DataType & DListEl)
{
    if(current == NULL)
        return false;
    if(current->next == NULL){
        current = NULL;
        return false;
    }
    current = current->next;
    DListEl = current->info;
    return true;
}


template <class DataType>
inline bool DList<DataType>::getPre( DataType & DListEl)
{
    if(current == NULL)
        return false;
    if(current->next == NULL){
        current = NULL;
        return false;
    }
    current = current->pre;
    DListEl = current->info;
    return true;
}


template <class DataType>
bool DList<DataType>::find( const DataType &element)
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
bool DList<DataType>::retrieve( DataType & element)
{
    if( !find(element))
        return false;
    element = current->info;
    return true;
}


template <class DataType>
bool DList<DataType>::replace( const DataType & newElement)
{
    if(current == NULL)
        return false;
    current->info = newElement;
    return true;
}


template <class DataType>
bool DList<DataType>::remove( DataType &element)
{
    current = NULL;
    if(head == NULL)
        return false;
    Node<DataType> *ptr = head;
    if(ptr->info == element){
        element = ptr->info;
        head = head->next;
        head->pre = NULL;
        delete ptr;
        return true;
    }
    while(ptr->next != NULL ){
        if(ptr->next->info == element){
            Node<DataType> *tempPtr = ptr->next;
            element = tempPtr->info;
            ptr->next = tempPtr->next;
            ptr->next->pre = ptr;
            delete tempPtr;
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

template <class DataType>
bool DList<DataType>::isEmpty() const
{
    return head == NULL;
}

template <class DataType>
void DList<DataType>::makeEmpty()
{
    while( head != NULL){
        current = head;
        head = head->next;
        delete current;
    }
    current = NULL;
}


template <class DataType>
inline void DList<DataType>::deepCopy( const DList<DataType> & original)
{
    head = current = NULL;
    if(original.head == NULL)
        return ;
    Node<DataType> *copyptr = head = new Node<DataType>;
    Node<DataType> *originalptr = original.head;
    copyptr->info = originalptr->info;
    if( originalptr == original.current)
        current = copyptr;
    while(originalptr->next != NULL){
        originalptr = originalptr->next;
        copyptr->next = new Node<DataType>;
        copyptr->next->pre = copyptr;
        copyptr = copyptr->next;
        copyptr->info = originalptr->info;
        if(originalptr == original.current)
            current = copyptr;
    }
    copyptr->next = NULL;
}

template <class DataType>
bool DList<DataType>::getSize( int &size)
{
    size = 0;
    Node<DataType> *ptr = head;
    while(ptr != NULL){
        size++;
        ptr = ptr->next;
    }
    return true;
}


int main(){
    DList<int> l;
    for(int i = 0; i< 10; i++){
        l.insert(i);
    }
    int x;
    l.first(x);
    cout<< x << "   ";
    for(;l.getNext(x);){
        cout<< x << "   ";
    }
    l.getSize(x);
    cout<<endl<<x<<endl;

    l.first(x);
    l.getNext(x);
    l.getNext(x);
    l.getPre(x);
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
