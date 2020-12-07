#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>
#include "LinkedList.h"

struct user;

struct city{
    std::string name;
    std::vector <user> currentResidents;
    
    city(){
        name = "";
    }
};

struct school{
    std::string name;
    std::string location;
    std::vector <user> currentStudents;
    std::vector <user> pastStudents;
    
    school(){
        name = "";
    }
};

struct sport{
    std::string name;
    std::vector <user> athletes;

    sport(){
        name = "";
    }
};

struct adjacent{
    user * u;
    int weight;
};

struct user{
    std::string username;
    std::string firstName;
    std::string lastName;
    int age;
    std::string city;
    std::string school;
    std::string sports [3];
    bool checked;
    int numConnections;
    std::vector <adjacent> adj;
    LinkedList posts;
    
    user(){
        username = "";
        firstName = "";
        lastName = "";
        age = 0;
        city = "";
        school = "";
        for(int i = 0; i < 3; i++){
            sports [i] = "";
        }
        checked = false;
        numConnections = 0;
        posts.head = nullptr;
    }

    user(std::string username1, std::string first, std::string last, int age1, std::string city1, std::string school1, std::string sport1, std::string sport2, std::string sport3){
        username = username1;
        firstName = first;
        lastName = last;
        age = age1;
        city = city1;
        school = school1;
        sports[0] = sport1;
        sports[1] = sport2;
        sports[2] = sport3;
        checked = false;
        numConnections = 0;
        posts.head = nullptr;
    }
};

class Graph
{
    public:
        Graph(){};  
        ~Graph(){}; 
        std::vector <school> schools;
        std::vector <city> cities;
        std::vector <sport> sports;
        std::vector <user> users;
        void constructCityList(std::string filename);
        void constructSchoolList(std::string filename);
        void constructSportList(std::string filename);
        void generateGraph(std::string filename, std::string filename2);
        bool checkUserNameUnique(std::string username);
        bool checkCityReal(std::string city);
        bool checkSchoolReal(std::string school);
        bool checkSportInclusion(std::string sport);
        bool checkUsernameReal(std::string username);
        void uncheck();
        void addUser(std::string username1, std::string first, std::string last, int age1, std::string city, std::string school, bool stillAttending, std::string sport1, std::string sport2, std::string sport3);
        void printSportAthletes(std::string sport);
        void printCityAthletes(std::string city, std::string sport);
        void printCurrentSchoolAlthles(std::string school, std::string sport);
        void printSchoolAthleteAlumni(std::string school, std::string sport);
        void updateCity(std::string username, std::string city1);
        void updateSchool(std::string username, std::string school);
        void updateAge(std::string username, int age1);
        void removeSport(std::string username, std::string sport);
        void addSport(std::string username, std::string sport);
        void searchForUser(std::string first, std::string last);
        void createConnection(std::string username1, std::string username2);
        void deleteConnection(std::string username1, std::string username2);
        void getUserConnections(std::string username);
        void getUserSecondaryConncection(std::string username);
        void getConnectionRecommendations(std::string username);
        void addPost(std::string username, int month, int day, int year, std::string post);
        bool checkPostDateUsed(std::string username, int month, int day, int year);
        void deletePost(std::string username, int month, int day, int year);
        void editPost(std::string username, int month, int day, int year, std::string newPost);
        void getAllUserPosts(std::string username);

    protected:
    private:
        user findUser(std::string username);
        user *findUser2(std::string username);
        city findCity(std::string name);
        school findSchool(std::string name);
        sport findSport(std::string name);
        bool contains(std::vector<user*> users1, std::string username);
        bool contains2(std::vector<adjacent> users1, std::string username);
};

#endif // GRAPH_H
