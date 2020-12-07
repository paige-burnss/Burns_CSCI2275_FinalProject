#ifndef LinkedList_H
#define LinkedList_H
#include <iostream>

struct LLNode{
    int year;
    int month;
    int day;
    std::string post;
    LLNode *next;
    LLNode *prev;

    LLNode(){
        month = 0;
        day = 0;
        year = 0;
        post = "";
        next = nullptr;
        prev = nullptr;
    }

    LLNode(int m, int d, int y, std::string p){
        month = m;
        day = d;
        year = y;
        post = p;
        next = nullptr;
        prev = nullptr;
    }
};

class LinkedList{
    public:
        LinkedList();
        LLNode *head;
        void insert(int month, int day, int year, std::string post);
        void remove(int month, int day, int year);
        void edit(int month, int day, int year, std::string newPost);
        void printLinkedList();
    protected:
    private:
        LLNode* findNode(int month, int day, int year);
};

#endif 
