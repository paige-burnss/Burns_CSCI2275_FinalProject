#include "LinkedList.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

        LinkedList::LinkedList(){
            head = nullptr;
        };

        void LinkedList::insert(int month, int day, int year, std::string post){
            LLNode *node = new LLNode(month, day, year, post);
            if(head == nullptr){
                head = node;
                return;
            }
            if(head->year <= year && head->month <= month && head->day < day){
                node->next = head;
                head->prev = node;
                head = node;
                return;
            }
            LLNode *temp = head;
            while(temp->next != nullptr && temp->year >= year && temp->month >= month && temp->day > day){
                temp = temp->next;
            }
            temp->prev->next = node;
            node->prev = temp->prev;
            node->next = temp;
            temp->prev = node;
        };

        void LinkedList::remove(int month, int day, int year){
            if(head == nullptr){
                std::cout << "This user had no current posts. No post can be removed." << std::endl;
                return;
            }
            LLNode *post = findNode(month, day, year);
            if(post == nullptr){
                return;
            }
            if(post == head){
                head = post->next;
                post->next->prev = nullptr;
                post->next = nullptr;
                return;
            }
            post->next->prev = post->prev;
            post->prev->next = post->next;
            post->next = nullptr;
            post->prev = nullptr;
        };

        void LinkedList::edit(int month, int day, int year, std::string newPost){
            LLNode *post = findNode(month, day, year);
            if(post == nullptr){
                return;
            }
            else{
                post->post = newPost;
            }
        };

        void LinkedList::printLinkedList(){
            LLNode *temp = head;
            while(temp != nullptr){
                std::cout << "Date Posted: " << temp->month << "/" << temp->day << "/" << temp->year << std::endl;
                std::cout << temp->post << std::endl;
            }
        };

        LLNode* LinkedList::findNode(int month, int day, int year){
            LLNode *temp = head;
            while(temp != nullptr && temp->year != year && temp->month != month && temp->day != day){
                temp = temp->next;
            }
            if(temp == nullptr){
                std::cout << "There is no post that was published on this date by this user." << std::endl;
                return temp;
            }
            return temp;
        };
