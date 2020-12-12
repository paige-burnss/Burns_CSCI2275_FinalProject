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
        location = "";
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
    LinkedList *posts;
    
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
        posts = new LinkedList();
        posts->head = nullptr;
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
        posts = new LinkedList();
        posts->head = nullptr;
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
    //makes list of cities that a user can be from to create a profile
        void constructSchoolList(std::string filename);
    //makes a list of high schools that a user can be attending / have attended to create a profile
        void constructSportList(std::string filename);
    //makes a list of sports that a user must participate in to have a profile
        void generateGraph(std::string filename, std::string filename2);
    //generates an intital graph before people using the program can start inputting new users
        bool checkUserNameUnique(std::string username);
    //checks if a username is unique before creating a profile (all usernames must be unique)
        bool checkCityReal(std::string city);
    //check if a city entered in a profile is one of the cities included in the vector of cities from the graph
        bool checkSchoolReal(std::string school);
    //check if a school enterd in a profile is one of the schools insluded in the vector of the schools from the graph
        bool checkSportInclusion(std::string sport);
    //checks if an sport that is being inputted into this program in the runner is included in the sports list 
       //if false, the runner states that they cannot use the social media program with that sport because it is relatively uncommon and they won't be able to make connections
        bool checkUsernameReal(std::string username);
    //checks if the username inputted in the runner is a valid username that is a part of the graph
        void addUser(std::string username1, std::string first, std::string last, int age1, std::string city, std::string school, bool stillAttending, std::string sport1, std::string sport2, std::string sport3);
    //adds a new user vertice to the graph     
        void printSportAthletes(std::string sport);
    //prints out all of the users that currently have the inputted sport on their profile 
        void printCityAthletes(std::string city, std::string sport);
    //prints out all of the users that currently live in a certain city and have the inputted sport on their profile 
        void printCurrentSchoolAlthles(std::string school, std::string sport);
    //prints out all of the users that currenlty go to a certain school and have the inputted sport on their profile
        void printSchoolAthleteAlumni(std::string school, std::string sport);
    //prints out all of the users that used to go to a certain school (now alumni of the school) and have the inputted sport on their profile
        void updateCity(std::string username, std::string city1);
    //updates the city that is currently stored in a user's profile
        void updateSchool(std::string username, std::string school);
    //updates the school that is currently stored in a user's profile
        void updateAge(std::string username, int age1);
    //updates the age that is currently stored in a user's profile
        void removeSport(std::string username, std::string sport);
    //removes a sport from a user's profile (only if a user has a sport left on their profile after this sport is removed)
        void addSport(std::string username, std::string sport);
    //adds another sport to a user's profile (but only if they don't have a max of 3 sports on their profile already)
        void searchForUser(std::string first, std::string last);
    //searches for a user using the first and last name of a user
       //can return multiple different users if they all have the same name
        void printNumConnections(std::string username);
    //finds the number of connections a user has (kind of like followers)
        void createConnection(std::string username1, std::string username2);
    //creates a connection between one user and another 
        void deleteConnection(std::string username1, std::string username2);
    //deletes a connection between two specified users (kind of like unfollowing) 
        void getUserConnections(std::string username);
    //gets all the connections of a certain user
        void getUserSecondaryConncection(std::string username);
    //returns a list of users that are connected to the specified user's connections (kind of like friends of friends)
        void getConnectionRecommendations(std::string username);
    //returns a max of 3 connection recomendation for a specified user
        void addPost(std::string username, int month, int day, int year, std::string post);
    //adds a new post to a user's profile 
        bool checkPostDateUsed(std::string username, int month, int day, int year);
    //checks if the date of a post that is desired to be posted has already been used(users only allowed to make one post per day) 
        void deletePost(std::string username, int month, int day, int year);
    //deletes a post from a user's profile 
        void editPost(std::string username, int month, int day, int year, std::string newPost);
    //edits a post on a user's profile 
        void getAllUserPosts(std::string username);
    //prints out all of a user's posts on their profile 

    protected:
    private:
        user findUser(std::string username);
    //finds a user in the graph from an inputted username and returns the actual user(not a pointer) 
        user *findUser2(std::string username);
    //finds a user in the graph from an inputted username but returns a pointer(not actual user) 
        city * findCity2(std::string name);
    //finds a city in the graph from an inputted city name but returns a pointer(not actual user) 
        school *findSchool2(std::string name);
    //finds a school in the graph from an inputted school name but returns a pointer(not actual user)  
        sport *findSport2(std::string name);
    //finds a sport in the graph from an inputted sport name but returns a pointer(not actual user) 
        bool contains(std::vector<user*> users1, std::string username);
    //checks if a specified username is included in a vector full of user pointers (used in user recomendation and secondary user connection functions)
        bool contains2(std::vector<adjacent> users1, std::string username);
    //checks if a specified username is included in a vector full of adjacent items (used in user recomendation and secondary user connection functions)
};

#endif // GRAPH_H
