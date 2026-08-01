#ifndef STACK_HPP
#define STACK_HPP
#include <stdexcept>
#include <iostream>

/**
 * STACK - Last In First Out (LIFO) Data Structure
 * Template class implementing stack using linked list
 * Generic type T allows any data type: int, char, double, string, etc.
 * Time Complexity: push() O(1), pop() O(1), top() O(1), size() O(n)
 */
template <typename T>
class stack{
    private:
    struct node{
    T info;
    struct node* link;
    };

    node* topNode=nullptr;  // Points to the top of stack (most recently added)
    public:

    // Check if stack is empty - O(1) time complexity
    bool is_empty(){
        if(topNode==nullptr){
            return true;
        }
        return false;
    }

    // Count total elements in stack - O(n) time complexity
    // Traverses entire linked list to count nodes
    int size(){
        int s=0;
        node* tempNode=topNode;
        while(tempNode!=nullptr){
            s++;  // Count each node
            tempNode=tempNode->link;  // Move to next node
        }
        tempNode=nullptr;  // Avoid dangling pointer
        return s;
    }

    // Add element to top of stack - O(1) time complexity
    void push(T value){
        node* newNode=new node;        // Create new node in memory
        newNode->info=value;           // Store the value
        newNode->link=topNode;         // New node points to current top
        topNode=newNode;               // Update top to new node
        return;
    }
    
    // Remove and return element from top - O(1) time complexity
    T pop(){
        if(topNode==nullptr){
            // Throw exception if attempting to pop from empty stack
            throw std::underflow_error("stack is empty");
        }
        T temp=topNode->info;          // Save data from top node
        node* tempNode=topNode;
        topNode=topNode->link;         // Move top pointer to next node
        delete tempNode;               // Free memory of removed node
        return temp;                   // Return the saved data
        
    }

    // Display all elements in stack from top to bottom
    void display(){
        node* tempNode=topNode;
        if(topNode==nullptr){
            std::cout<<"stack is empty"<<std::endl;
            return;
        }
        while(tempNode!=nullptr){
            std::cout<<tempNode->info<<std::endl;
            tempNode=tempNode->link;   // Move to next node
        }
        return;
    }

    // Get element at top without removing it - O(1) time complexity
    T top(){
        if(topNode==nullptr){
            std::cout<<"stack is empty";
            throw std::underflow_error("stack is empty");
        }
        T temp=topNode->info;          // Get top element data
        return temp;
    }

    /**
     * DESTRUCTOR - Automatically called when stack object is destroyed
     * Frees all allocated memory to prevent memory leaks
     * Traverses entire linked list and deletes each node one by one
     */
    ~stack() {
        while(topNode != nullptr) {
            node* temp = topNode;
            topNode = topNode->link;   // Move to next node before deletion
            delete temp;               // Free current node's memory
        }
    }
};

#endif