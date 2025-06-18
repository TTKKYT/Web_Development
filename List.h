#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
    bool empty() const {
        return (first == nullptr);
    }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
    int size() const {
        return size_;
    }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
    T & front() {
        return first->datum;
    }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
    T & back() {
        return last->datum;
    }

  //EFFECTS:  inserts datum into the front of the list
    void push_front(const T &datum) {
        // add and change the new one
        Node* new_node = new Node;
        new_node->prev = nullptr;
        new_node->next = first;
        new_node->datum = datum;
        
        // change the old one
        if (last == nullptr) {
            last = new_node;
        }
        else {
            first->prev = new_node;
        }
        
        first = new_node;
        
        size_++;
    }

  //EFFECTS:  inserts datum into the back of the list
    void push_back(const T &datum) {
        Node* new_node =  new Node;
        new_node->prev = last;
        new_node->next = nullptr;
        new_node->datum = datum;
        
        if (last == nullptr) {
            first = new_node;
        }
        else {
            last->next = new_node;
        }
        
        last = new_node;
        
        size_++;
    }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
    void pop_front() {
        Node* new_first_node = first->next;
        delete first;
        first = new_first_node;
        if (first == nullptr) {
            last = nullptr;
        }
        else {
            first->prev = nullptr;
        }
        
        size_--;
    }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
    void pop_back() {
        Node* new_last_node = last->prev;
        delete last;
        last = new_last_node;
        if (last == nullptr) {
            first = nullptr;
        }
        else {
            last->next = nullptr;
        }
        
        size_--;
    }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
    void clear() {
        while(size() != 0) {
            pop_back();
        }
    }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists
    
    // constructor
    List() {
        first = nullptr;
        last = nullptr;
        size_ = 0;
    }
    
    // copy constructor
    List(const List <T> &other) {
        first = nullptr;
        last = nullptr;
        size_ = 0;
        copy_all(other);
    }
    
    // assignment overloaded operator
    List& operator=(List& other) {
        clear();
        copy_all(other);
        return *this;
    }
    
    // destructor
    ~List() {
        clear();
    }

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
    void copy_all(const List<T> &other) {
        for (Iterator it = other.begin(); it != nullptr; ++it) {
            push_back(*it);
        }
    }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
    
    int size_;

public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
        assert(node_ptr);
        node_ptr = node_ptr->prev;
        return *this;
    }
      // operator++
      Iterator& operator++() {
          assert(node_ptr);
          node_ptr = node_ptr->next;
          return *this;
      }
      
      // operator ==
      bool operator==(const Iterator& it) const {
          return node_ptr == it.node_ptr;
      }
      
      // operator !=
      bool operator!=(const Iterator& it) const {
          return node_ptr != it.node_ptr;
      }
      
      // operator*
      T& operator*() {
          return node_ptr->datum;
      }
      
      // default constructor
      Iterator() {
          node_ptr = nullptr;
      }
      
      // copy constructor
      Iterator(const Iterator& it) {
          node_ptr = it.node_ptr;
      }
      
      // assignment overloaded contructor
      Iterator& operator=(const Iterator& it) {
          node_ptr = it.node_ptr;
          return *this;
      }
      
      // destructor
      ~Iterator() {}
      

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
      friend class List;

    // construct an Iterator at a specific position
      Iterator(Node *p) {
          node_ptr = p;
      }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
    Iterator end() const {
        return Iterator(last->next);
    }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
    void erase(Iterator i) {
        if (i.node_ptr->prev != nullptr) {
            i.node_ptr->prev->next = i.node_ptr->next;
        }
        else {
            first = i.node_ptr->next;
        }
        if (i.node_ptr->next != nullptr) {
            i.node_ptr->next->prev = i.node_ptr->prev;
        }
        else {
            last = i.node_ptr->prev;
        }
       
        delete i.node_ptr;
        size_--;
    }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
    void insert(Iterator i, const T &datum) {
        Node* new_node = new Node;
        new_node->datum = datum;
        
        if (i.node_ptr != nullptr) {
            if (i.node_ptr->prev != nullptr) {
                i.node_ptr->prev->next = new_node;
            }
            else {
                first = new_node;
            }
            new_node->prev = i.node_ptr->prev;
            i.node_ptr->prev = new_node;
            new_node->next = i.node_ptr;
        }
        else {
            if (first == nullptr) {
                first = new_node;
                new_node->prev = nullptr;
            }
            else {
                last->next = new_node;
                new_node->prev = last;
            }
            
            last = new_node;
            new_node->next = nullptr;
        }
        size_++;
    }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
