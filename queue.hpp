#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <iostream>
#include <stdexcept>

// Generic queue using a singly linked list (FIFO).
template <typename T>
class queue{

    private:
    // One node in the linked list.
    struct node{
    T info;         // value stored in this node
    struct node* link; // pointer to next node
    };
    // F points to front, R points to rear.
    node* F=nullptr;
    node* R=nullptr;

    public:

    // Check whether queue is empty.
    bool is_empty(){
        // Queue is empty only when both front and rear are null.
        if(F==nullptr && R==nullptr){
            return true;
        }
       return false;
    }

    // Count elements from front to rear.
    int size(){
        int s=0;
        node* tempNode=F;
        while(tempNode!=nullptr){
            s++;
            tempNode=tempNode->link;
        }
        tempNode=nullptr;
        return s;
    }

    // Insert one element at rear.
    void equeue(T x){
        node* next=new node; // create new node for inserted value
        next->info=x;
        next->link=nullptr;
        // If queue is empty, new node becomes rear.
        if(R==nullptr){
            R=next;
        }
        else{
            R->link=next;
            R=next;
        }

        // For first insertion, front should also point to it.
        if(F==nullptr){
            F=R;
        }
        return;
    }

    // Remove and return one element from front.
    T dequeue(){
        if(F==nullptr){
            throw std::underflow_error("queue is empty");
        }

        T y=F->info; // value to return
        node* tempNode;
        if(F==R){
            // Single node case: queue becomes empty.
            tempNode=F;
            F=nullptr;
            R=nullptr;
        }
        else{
            // Move front to next node.
            tempNode=F;
            F=F->link;
        }
        delete tempNode; // free removed node
        return y;

    }


    // Destructor: delete all nodes.
        ~queue() {
        while(F != nullptr) {
            node* temp = F;
            F = F->link;
            delete temp; // delete each node one by one
        }
        R=nullptr; // rear must also reset
    }

};




#endif