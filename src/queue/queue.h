#ifndef QUEUE_H
#define QUEUE_H
#include "../../!include/link_list/link_list.h"
#include <ostream>
using namespace std;



template <class T>
class Queue
{
public:
    class Iterator{
        //the nested class
    public:
        friend class Queue;
        //allowing Queue to access the private member of Iterator
        //constructor
        Iterator(node<T>* p = NULL):_ptr(p){}
        //dereference oprator
        T& operator *(){
            assert(_ptr);
            return _ptr->_item;
        }
        //casting operator: true if _ptr not NULL
        operator bool(){
            if(_ptr != NULL){
                return true;
            }
            return false;
        }
//         //member access operator
//        T* operator ->(){
//        }

        //it++
        friend Iterator operator ++(Iterator& it,
                                    int unused){
            Iterator hold;
            hold = it;
            it._ptr = it._ptr->_next;
            return hold;
        }
        //++it
        Iterator& operator ++(){
            _ptr = _ptr->_next;
            return *this;
        }
        friend bool operator !=(const Iterator& left,
                                const Iterator& right){
            return left._ptr != right._ptr;
        }
        friend bool operator ==(const Iterator& left,
                                const Iterator& right){
            return left._ptr == right._ptr;
        }

    private:
        node<T>* _ptr;
    };

    Queue();
    //big3
    ~Queue();
    Queue(const Queue<T> &copyThis);
    //becareful with queue copy constructor
    Queue& operator =(const Queue& RHS);

    Iterator Begin() const         //an iterator to the start of List
    {
        return Iterator(_front);
    }
    Iterator End() const           //an iterator to the end of List
    {
        return Iterator(_rear);
    }
    void push(const T& item);

    T pop();
    T front();
    bool empty();
    void print(std::ostream &outs=std::cout) const;
    template <class U>
    friend std::ostream& operator <<(std::ostream& outs,
                                     const Queue<T> &printMe);

private:
    int _size;
    node<T>* _front;
    node<T>* _rear;
};

template <class T>
Queue<T>::Queue()
{
    //Initializes the object to an empty queue
    _size = 0;
    _front = NULL;
    _rear = NULL;
}

template <class T>
Queue<T>::~Queue(){
    node<T>* walker=_front;

    while(walker != NULL){
        _DeleteNode(_front,walker);
        walker = walker->_next;
    }

}
template <class T>
Queue<T>::Queue(const Queue<T> &copyThis){
    _size = copyThis._size;
    _front = NULL;
    _rear = _CopyListWdest(_front,copyThis._front);
}
template <class T>
Queue<T>& Queue<T>::operator =(const Queue<T>& RHS){
    if(this == &RHS){
        return *this;
    }
    delete _front;
    _front = NULL;
    _size = RHS._size;
    _rear = _CopyListWdest(_front,RHS._front);
    return *this;
}
template <class T>
bool Queue<T>::empty(){
    if(_front == NULL){
        return true;
    }
    return false;
}
template <class T>
void Queue<T>::push(const T& item){
    //if empty
    if(empty()){
        //insert at _front
        _front =_InsertHead(_front,item);
        //_front and _rear point same place
        _rear =_front;
    }
    else{
        //add items at after _rear
        _rear = _InsertAfter(_front,_rear,item);
    }
    _size++;
}
template <class T>
T Queue<T>::pop(){
    //assert that the queue is empty
    assert(_front != NULL);
    _size--;

    //if the queue has only one element
    if( _front == _rear){
        _rear = NULL;
    }
    //item pops in order item pushed
    return _DeleteNode(_front,_front);
}
template <class T>
T Queue<T>::front(){
    return _front->_item;
}
template <class T>
void Queue<T>::print(std::ostream& outs) const{
    node<T>* walker=_front;
    while (walker != NULL){
        outs<<"["<<walker->_item<<"]->";
        walker = walker->_next;
    }
    outs<<"|||    ";
    if(_front!=NULL)
        outs<<"front: "<<_front->_item<<"  ";
    else
        outs<<"front: NULL";
    if (_rear)
        outs<<"rear: "<<_rear->_item;
    else
        outs<<"rear: NULL"<<endl;
    outs<<endl;
}
template <class U>
ostream& operator <<(std::ostream& outs, const Queue<U> &printMe){
    printMe.print();
    return outs;
}


#endif // QUEUE_H
