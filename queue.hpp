#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <iostream>

// Linked-list based generic queue (FIFO).
template <typename T>
class queue{

    private:
    // Internal node for queue storage.
    struct node{
    T info;
    struct node* link;
    };
    // F: front pointer, R: rear pointer.
    node* F=nullptr;
    node* R=nullptr;

    public:
    // Insert element at rear.
    void equeue(T x){
        node* next=new node;
        next->info=x;
        next->link=nullptr;
        if(R==nullptr){
            R=next;
        }
        else{
            R->link=next;
            R=next;
        }

        if(F==nullptr){
            F=R;
        }
        return;
    }

    // Remove and return element from front.
    T dequeue(){
        if(F==nullptr){
            throw std::underflow_error("queue is empty");
        }

        T y=F->info;
        node* tempNode;
        if(F==R){
            tempNode=F;
            F=nullptr;
            R=nullptr;
        }
        else{
            tempNode=F;
            F=F->link;
        }
        delete tempNode;
        return y;

    }


};




#endif