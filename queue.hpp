#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <iostream>
#include <stdexcept>

/**
 * QUEUE - First In First Out (FIFO) Data Structure
 * Template class implementing queue using linked list
 * Generic type T allows any data type: int, char, double, string, etc.
 * Elements added at rear (R) and removed from front (F)
 * Time Complexity: equeue() O(1), dequeue() O(1), size() O(n)
 */
template <typename T>
class queue{

    private:
    struct node{
    T info;
    struct node* link;
    };
    node* F=nullptr;  // Front pointer - points to first element (to be removed)
    node* R=nullptr;  // Rear pointer - points to last element (newly added)

    public:

    // Check if queue is empty - O(1) time complexity
    bool is_empty(){
        if(F==nullptr && R==nullptr){
            return true;
        }
       return false;
    }

    // Count total elements in queue - O(n) time complexity
    // Traverses entire linked list from front to rear
    int size(){
        int s=0;
        node* tempNode=F;
        while(tempNode!=nullptr){
            s++;  // Count each node
            tempNode=tempNode->link;  // Move to next node
        }
        tempNode=nullptr;  // Avoid dangling pointer
        return s;
    }

    // Add element to rear of queue - O(1) time complexity
    // New elements always added at the end, following FIFO principle
    void equeue(T x){
        node* next=new node;           // Create new node in memory
        next->info=x;                  // Store the value
        next->link=nullptr;            // New node is at rear, no next element
        
        if(R==nullptr){
            // If queue is empty, new node is both front and rear
            R=next;
        }
        else{
            // Link previous rear to new node
            R->link=next;
            R=next;                    // Update rear pointer to new node
        }

        if(F==nullptr){
            // If queue is empty, new node is also the front
            F=R;
        }
        return;
    }

    // Remove and return element from front - O(1) time complexity
    // Elements removed in FIFO order (first added, first removed)
    T dequeue(){
        if(F==nullptr){
            // Throw exception if attempting to dequeue from empty queue
            throw std::underflow_error("queue is empty");
        }

        T y=F->info;                   // Save data from front node
        node* tempNode;
        
        if(F==R){
            // If there's only one element, queue becomes empty after removal
            tempNode=F;
            F=nullptr;                 // Clear front
            R=nullptr;                 // Clear rear
        }
        else{
            // Move front pointer to next node
            tempNode=F;
            F=F->link;                 // Update front to next element
        }
        
        delete tempNode;               // Free memory of removed node
        return y;                      // Return the saved data

    }


    /**
     * DESTRUCTOR - Automatically called when queue object is destroyed
     * Frees all allocated memory to prevent memory leaks
     * Traverses linked list from front and deletes each node one by one
     */
    ~queue() {
        while(F != nullptr) {
            node* temp = F;
            F = F->link;               // Move to next node before deletion
            delete temp;               // Free current node's memory
        }
        R=nullptr;                     // Reset rear pointer for safety
    }

};




#endif