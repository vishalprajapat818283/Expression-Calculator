#ifndef STACK_HPP
#define STACK_HPP
#include <stdexcept>
#include <iostream>

    template <typename T>
class stack{
    private:
    struct node{
    T info;
    struct node* link;
    };

    node* topNode=nullptr;
    public:

    bool is_empty(){
        if(topNode==nullptr){
            return true;
        }
        return false;
    }

    int size(){
        int s=0;
        node* tempNode=topNode;
        while(tempNode!=nullptr){
            s++;
            tempNode=tempNode->link;
        }
        tempNode=nullptr;
        return s;
    }

    void push(T value){
        node* newNode=new node;
        newNode->info=value;
        newNode->link=topNode;
        topNode=newNode;
        return;
    }
    
    T pop(){
        if(topNode==nullptr){
            // std::cout<<"stack is empty"<<std::endl;
            throw std::underflow_error("stack is empty");
        }
        T temp=topNode->info;
        node* tempNode=topNode;
        topNode=topNode->link;
        delete tempNode;
        return temp;
        
    }

    void display(){
        node* tempNode=topNode;
        if(topNode==nullptr){
            std::cout<<"stack is empty"<<std::endl;
            return;
        }
        while(tempNode!=nullptr){
            std::cout<<tempNode->info<<std::endl;
            tempNode=tempNode->link;
        }
        return;
    }

    T top(){
        if(topNode==nullptr){
            std::cout<<"stack is empty";
        throw std::underflow_error("stack is empty");
        }
        T temp=topNode->info;
        return temp;
    }

    //destructer
    ~stack() {  // destructor
        while(topNode != nullptr) {
            node* temp = topNode;
            topNode = topNode->link;
            delete temp;  // frees each node
        }
    }
};

#endif