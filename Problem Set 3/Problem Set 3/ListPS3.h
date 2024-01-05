#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

#include <stdexcept>

template<typename T>
class List
{
private:
    // auxiliary definition to simplify node usage
    using Node = DoublyLinkedList<T>;

    Node* fRoot;	// the first element in the list
    size_t fCount;	// number of elements in the list

public:
    // auxiliary definition to simplify iterator usage
    using Iterator = DoublyLinkedListIterator<T>;

    ~List()                                                                 // destructor - frees all nodes
    {
        while (fRoot != nullptr)
        {
            if (fRoot != &fRoot->getPrevious())                       
            {
                Node* lTemp = const_cast<Node*>(&fRoot->getPrevious()); 

                lTemp->isolate();                                       
                delete lTemp;                                           
            }

            else
            {
                delete fRoot;                                          
                break;                                                  
            }
        }
    }

    void remove(const T& aElement)	                                        // remove first match from list
    {
        Node* lNode = fRoot;                                            

        while (lNode != nullptr)                                      
        {
            if (**lNode == aElement)                                  
            {
                break;                                                  
            }

            if (lNode != &fRoot->getPrevious())                       
            {
                lNode = const_cast<Node*>(&lNode->getNext());           
            }

            else
            {
                lNode = nullptr;                                        
            }
        }
       
        if (lNode != nullptr)                                        
        {
            if (fCount != 1)                                        
            {
                if (lNode == fRoot)
                {
                    fRoot = const_cast<Node*>(&fRoot->getNext());     
                }
            }

            else
            {
                fRoot = nullptr;                                        
            }

            lNode->isolate();                                        
            delete lNode;                                              
            fCount--;                                                
        }
    }

    List() : fRoot(nullptr), fCount(0) {}                                     // default constructor

    bool empty() const { return fCount == 0; }	                              // Is list empty?
    size_t size() const { return fCount; }                		              // list size

    void push_front(const T& aElement)                                        // adds aElement at front
    {                                      
        if (empty())
        {
            fRoot = new Node(aElement);
        }

        else
        {
            Node* lNode = new Node(aElement);
            fRoot->push_front(*lNode);
            fRoot = lNode;
        }

        ++fCount;
    }

    Iterator begin() const                                                    // return a forward iterator
    {                                                  
        return Iterator(fRoot).begin();
    }

    Iterator end() const                                                      // return a forward end iterator
    {                                                    
        return Iterator(fRoot).end();
    }

    Iterator rbegin() const                                                   // return a backwards iterator
    {
        return Iterator(fRoot).rbegin();
    }                   

    Iterator rend() const                                                     // return a backwards end iterator
    {
        return Iterator(fRoot).rend();
    }                     

    void push_back(const T& aElement)                                         // adds aElement at back
    {
        if (empty())
        {
            fRoot = new Node(aElement);
        }

        else
        {
            Node* lastNode = const_cast<Node*>(&fRoot->getPrevious());

            lastNode->push_back(*new Node(aElement));
        }

        ++fCount;
    }

    const T& operator[](size_t aIndex) const                                  // list indexer
    {
        if (aIndex > size() - 1) 
        throw std::out_of_range("Index out of bounds");

        Iterator lIterator = Iterator(fRoot).begin();
        for (size_t i = 0; i < aIndex; i++) ++lIterator;
        return *lIterator;
    }	

    List(const List& aOtherList);              // copy constructor
    List& operator=(const List& aOtherList); // assignment operator

    // move features 
    List(List&& aOtherList);                   // move constructor
    List& operator=(List&& aOtherList);        // move assignment operator
    void push_front(T&& aElement);             // adds aElement at front
    void push_back(T&& aElement);              // adds aElement at back
};