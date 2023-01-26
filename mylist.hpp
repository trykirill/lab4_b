#ifndef MYLIST_HPP
#define MYLIST_HPP

#include <cassert>
#include <iostream>

using namespace std;

template <class T>
class mylist {
    private:
        struct Node {
            T     value;
            Node *next;
            Node(const T & val, Node * nex) : value(val), next(nex) {}
        };
        Node * head;
        int    count;
    public:
        class Iterator {
        protected:
            Node *cur;
        public:
            Iterator(Node* curr) : cur(curr) {}
            T & operator*() {
                assert(cur != nullptr);
                return cur->value;
            }
            const T & operator*() const {
                assert(cur != nullptr);
                return cur->value;
            }
            void operator++() const {
                assert(cur != nullptr);
                cur = cur->next;
            }
            bool operator==(const Iterator & other) const {
                return (cur == other.cur);
            }
            bool operator!=(const Iterator & other) const {
                return (cur != other.cur);
            }
        };
 
    typedef Iterator iterator;
    typedef const Iterator const_iterator;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
 
    const_reference front() const {
        assert(head != nullptr);
        return head->value;
    }
    reference front() {
        assert(head != nullptr);
        return head->value;
    }
 
    iterator begin() {
        return Iterator(head);
    }
    iterator end() {
        return Iterator(nullptr);
    }
    const_iterator begin() const {
        return Iterator(head);
    }
    const_iterator end() const  {
        return Iterator(nullptr);
    }
    void remove(const iterator & it) {
        for (Node * node = head, *p = nullptr; node; p=node, node=node->next) {
            if (node->value == *it) {
                (p ? p->next : head) = node->next;
                --count;
                delete node;
                return;
            }
        }
    }
 
    mylist() : head(nullptr), count(0) {}
    ~mylist() { destroy(head); }
 
    void destroy(Node* root) {
        Node * node = root;
        while (node) {
            root = node;
            node = node->next;
            delete root;
        }
    }

    void push_front(const T & value) {
        head = new Node(value, head);
        ++count;
    }

    void erase(const T & value) {
        for (Node * node = head, *p = 0; node; p=node, node=node->next) {
           if (node->value == value) {
                (p ? p->next : head) = node->next;
                --count;
                delete node;
                return;
            }
        }
    }
    bool contains(const T & value) const {
        for (const iterator & b = begin(), & end = end(); b != end; ++b) {
            if (*b == value) return true;
        }
        return false;
    }
    bool empty() const {
        return (head == nullptr);
    }
    int size() const {
        return count;
    }
};
