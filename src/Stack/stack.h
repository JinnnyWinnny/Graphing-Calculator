#ifndef STACK_H
#define STACK_H
#include "../../!include/list/list.h"

template <class T>
class Stack
{
public:
    class Iterator{
    public:
        friend class Stack;
        Iterator(){
            //constructor
            typename List<T>::Iterator();
        }
        Iterator(typename List<T>::Iterator p){
            _it = p;
        }
        operator bool()
        {
            if(_it){
                //not empty
                return true;
            }
            //empty
            return false;
        }
        T& operator *(){
            //return dereference of _it
            return *_it;
        }
        bool is_null(){
            if(_it()){
                return true;
            }
            return false;
        }
        friend bool operator !=(const Iterator& left,
                                const Iterator& right){
            return left._it != right._it;
        }
        //true if left == right
        friend bool operator ==(const Iterator& left,
                                const Iterator& right){
            return left._it == right._it;
        }
        friend Iterator operator++(Iterator& it,
                                    int unused){
            return it._it++;
        }

        Iterator& operator ++(){
            ++_it;
            return *this;
        }
    private:
        typename List<T>::Iterator _it;
    };

    Stack();
    void push(const T& item);
    T pop();
    bool empty();
    T top();
    void print() const;
    Iterator Begin() const;
    Iterator End() const;
    template <class U>
    friend ostream& operator <<(ostream& outs,          //insertion operator for list
                                const Stack<U>& s);
private:
    int size;
    List<T> _stack;
};
template <class T>
Stack<T>::Stack(){
    //initializes the object to an empty stack
    size = 0;
}
template <class T>
T Stack<T>::top(){
    assert(size>0);
    //return begin of the stack
    return *(_stack.Begin());
}
template <class T>
void Stack<T>::push(const T& item){
    //add item to the stack
    _stack.InsertHead(item);
    size++;
}
template <class T>
bool Stack<T>::empty(){
    //returns true if the stack is empty
    //otherwise, false
    if(size<=0){
        return true;
    }
    return false;
}

template <class T>
T Stack<T>::pop(){
    //assert the stack is not empty
    //    Iterator begin = top();
    assert(size>0);
    size--;
    //removes top element from the stack
    return _stack.Delete(_stack.Begin());
}

template <class T>
void Stack<T>::print() const{
    _stack.Print();

}
template <class U>
ostream& operator <<(ostream& outs,const Stack<U>& s){

    s.print();
    return outs;

}
template <class T>
typename Stack<T>::Iterator Stack<T>::Begin() const{
    return Iterator(_stack.Begin());
}
template <class T>
typename Stack<T>::Iterator Stack<T>::End() const{
    return Iterator(_stack.End());
}


#endif // STACK_H
