#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>

// Linked-list based generic stack (LIFO).
    template <typename T>
class stack{
    private:
    // Internal node for stack storage.
    struct node{
    T info;
    struct node* link;
    };

    node* topNode=nullptr;
    public:

    // Push value to the top.
    void push(T value){
        node* newNode=new node;
        newNode->info=value;
        newNode->link=topNode;
        topNode=newNode;
        return;
    }
    
    // Pop and return the top value.
    T pop(){
        if(topNode==nullptr){
            throw std::underflow_error("stack is empty");
        }
        T temp=topNode->info;
        node* tempNode=topNode;
        topNode=topNode->link;
        delete tempNode;
        return temp;
        
    }

    // Print elements from top to bottom.
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

    // Returns true when stack has no element.
    bool is_empty(){
        if(topNode==nullptr){
            return true;
        }
        else{
            return false;
        }
    }
    
    // Returns top element without removing it.
    T top(){
        if(topNode==nullptr){
            std::cout<<"stack is empty";
        throw std::underflow_error("stack is empty");
        }
        T temp=topNode->info;
        return temp;
    }


};

#endif