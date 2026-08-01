#ifndef STACK_HPP
#define STACK_HPP
#include <stdexcept>
#include <iostream>

// Generic stack using a singly linked list (LIFO).
    template <typename T>
class stack{
    private:
    // One node in the linked list.
    struct node{
    T info;          // value stored in node
    struct node* link; // pointer to next node
    };

    node* topNode=nullptr; // points to current top element
    public:

    // Check whether stack is empty.
    bool is_empty(){
        if(topNode==nullptr){
            return true;
        }
        return false;
    }

    // Count elements by walking through all nodes.
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

    // Add one value on top of the stack.
    void push(T value){
        node* newNode=new node; // create node for new value
        newNode->info=value;
        newNode->link=topNode; // link new node to old top
        topNode=newNode;       // update top to new node
        return;
    }
    
    // Remove and return the top value.
    T pop(){
        if(topNode==nullptr){
            throw std::underflow_error("stack is empty");
        }
        T temp=topNode->info;      // value to return
        node* tempNode=topNode;    // node to delete
        topNode=topNode->link;     // move top downward
        delete tempNode;           // free removed node
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

    // Read top value without removing it.
    T top(){
        if(topNode==nullptr){
            std::cout<<"stack is empty";
        throw std::underflow_error("stack is empty");
        }
        T temp=topNode->info; // read top without removing
        return temp;
    }

    // Destructor: delete all nodes to free memory.
    ~stack() {
        while(topNode != nullptr) {
            node* temp = topNode;
            topNode = topNode->link;
            delete temp; // delete each node one by one
        }
    }
};

#endif