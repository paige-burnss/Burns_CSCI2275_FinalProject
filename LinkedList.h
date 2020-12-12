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
    //inserts a new post into a user's linked list of posts at a certain date
        void remove(int month, int day, int year);
     //removes a post from a user's profile from a specific date
        void edit(int month, int day, int year, std::string newPost);
     //edits a current post on a user's profile
        void printLinkedList();
     //prints out all posts of a user
    protected:
    private:
        LLNode* findNode(int month, int day, int year);
     //finds the node of a post on a certain date
};

#endif 
