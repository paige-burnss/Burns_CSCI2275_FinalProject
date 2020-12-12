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
            //inserts a new post into a user's linked list of posts at a certain date
            LLNode *node = new LLNode(month, day, year, post);
                //creates a new post node with the month, year, date, and post a user wants to make
            if(head == nullptr){
                head = node;
                return;
            }
                //check if a user's post list is emtpy, and if so, adds the new post to the head of the linked list
            if(head->year <= year && head->month <= month){
                if((head->month == month && head->day < day) || head->month < month){
                    node->next = head;
                    head->prev = node;
                    head = node;
                    return;
                }
            }
                //checks if the post is more recent then the current head of the posts linked list. if so, new post is added to the head of the list
            LLNode *temp = head;
            while(temp->next != nullptr && temp->year >= year){
                temp = temp->next;
            }
            while(temp->next != nullptr && temp->month >= month){
                temp = temp->next;
            }
            while(temp->next != nullptr && temp->day > day){
                temp = temp->next;
            }
                //traverses throught the linked list until end of the list is reached or until the iterator reaches a post that is after the date of the specified post
            if(temp->next == nullptr && temp->year >= year){
                if(temp->year > year){
                    temp->next = node;
                    node->prev = temp;
                    return;
                }
                if((temp->month == month && temp->day > day)|| temp->month > month) {
                    temp->next = node;
                    node->prev = temp;
                    return;
                }
            }
                //checks if end of the list is reached, and if so node is inserted before or after last node in list
            temp->prev->next = node;
            node->prev = temp->prev;
            node->next = temp;
            temp->prev = node;
                //node is inserted into the linked list in its specified position determined by the previous traversal
        };

        void LinkedList::remove(int month, int day, int year){
                //removes a post from a user's profile from a specific date
            if(head == nullptr){
                std::cout << "This user had no current posts. No post can be removed." << std::endl;
                return;
            }
                //checks if user has any posts
            LLNode *post = findNode(month, day, year);
                //finds the node with the specified date
            if(post == nullptr){
                return;
            }
                //checks if the found post is null, which means no post was published on this date for this user
            if(post == head){
                head = post->next;
                post->next->prev = nullptr;
                post->next = nullptr;
                return;
            }
                //checks if the specified post is the head of the list and reassigns the head of the list accordingly
            post->next->prev = post->prev;
            post->prev->next = post->next;
            post->next = nullptr;
            post->prev = nullptr;
                //if no special characters, next and prev pointers are rearranged around the specified post to delete any connections to that post node
        };

        void LinkedList::edit(int month, int day, int year, std::string newPost){
                //edits a current post on a user's profile
            LLNode *post = findNode(month, day, year);
                //finds the node with the specified date
            if(post == nullptr){
                return;
            }
                //checks if the found post is null, which means no pust was published on this date for this user
            else{
                post->post = newPost;
            }
                //if post is real, the post is updated to the new post
        };

        void LinkedList::printLinkedList(){
                //prints out all posts of a user
            LLNode *temp = head;
                //new pointer created for traversing the list
            while(temp != nullptr){
                std::cout << "Date Posted: " << temp->month << "/" << temp->day << "/" << temp->year << std::endl;
                std::cout << temp->post << std::endl;
                temp = temp->next;
            }
                //while traversing the list, each post date and content is printed out
        };

        LLNode* LinkedList::findNode(int month, int day, int year){
                //finds the node of a post on a certain date
            LLNode *temp = head;
                //create a pointer to traverse through the linked list
            while(temp != nullptr && temp->year != year){
                temp = temp->next;
            }
            while(temp != nullptr && temp->month != month){
                temp = temp->next;
            }
            while(temp != nullptr && temp->day != day){
                temp = temp->next;
            }
                //traverses as long as the year, month, and date of posts in list aren't equal to the specified date
            if(temp == nullptr){
                std::cout << "There is no post that was published on this date by this user." << std::endl;
                return temp;
            }
                //if the pointer node is nullptr, that means that the whole list was traversed without finding the specified date, so that post doesn't exist
            return temp;
                //if the pointer was found, it is returned
        };
