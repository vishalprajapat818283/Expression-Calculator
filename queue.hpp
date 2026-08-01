#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <iostream>
#include <stdexcept>

template <typename T>
class queue{

    private:
    struct node{
    T info;
    struct node* link;
    };
    node* F=nullptr;
    node* R=nullptr;

    public:

    bool is_empty(){
        if(F==nullptr && R==nullptr){
            return true;
        }
       return false;
    }

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


    //destructer
        ~queue() {
        while(F != nullptr) {
            node* temp = F;
            F = F->link;
            delete temp;  // frees each node
        }
        R=nullptr;
    }

};




#endif