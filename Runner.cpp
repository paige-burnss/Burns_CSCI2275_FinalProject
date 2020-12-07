#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.h"

using namespace std; 

int main(int argc, const char * argv[]) {
    
    Graph g;

    std::string cityFilename = argv[1];
    g.constructCityList(cityFilename);
    std::string schoolFilename = argv[2];
    g.constructSchoolList(schoolFilename);
    std::string sportsFilename = argv[3];
    g.constructSportList(sportsFilename);
    std::string usersFilename = argv[4];
    std::string connectFilename = argv[5];
    g.generateGraph( usersFilename, connectFilename);


    string dmenu =  "======Main Menu======\n"
                    "1. Add a new user\n"
                    "2. Find athletes of a certain sport\n"
                    "3. Find athletes of a certain sport who live in a certain city\n"
                    "4. Find athletes of a certain sport who go to a certain school currently\n"
                    "5. Find athletes of a certain sport who went to a certain school in the past\n"
                    "6. Update athlete's profile - city\n"
                    "7. Update athlete's profile - school\n"
                    "8. Update athlete's profile - age\n"
                    "9. Update athlete's profile - add a sport\n"
                    "10. Update athlete's profile - remove a sport\n"
                    "11. Search for user with name\n"
                    "12. See the number of connections a user has\n"
                    "13. Create connection between two users\n"
                    "14. Delete connection between two users\n"
                    "15. Get users connections\n"
                    "16. Get users secondary connections\n"
                    "17. Get recommendations for a user\n"
                    "18. Add a new post to an athlete's profile\n"
                    "18. Delete a post from an athlete's profile\n"
                    "20. Edit a post on an athlete's profile\n"
                    "21. Display all the posts on an athlete's profile\n"
                    "22. Quit\n";

    int choice = 0;
    bool done = false;

    do {
        cout << dmenu;
        cin >> choice;
        
        cin.clear();
        cin.ignore();
        
        switch (choice) {
            
            case 1:{
                cout<<"Enter a username: ";
                string username;
                getline(cin, username);
                if(g.checkUserNameUnique(username) == false){
                    do{
                        cout << "That username is already taken. Please enter a different username: ";
                        getline(cin, username);
                    }
                    while(g.checkUserNameUnique(username) == false);
                }

                cout << "Enter your first name: ";
                string firstname;
                getline(cin, firstname);

                cout << "Enter your last name: ";
                string lastname;
                getline(cin, lastname);

                cout << "Enter your age: ";
                string age1;
                getline(cin, age1);
                int age = stoi(age1);

                cout << "Enter the city you currently live in: ";
                string city;
                getline(cin, city);
                if(g.checkCityReal(city) == false){
                    do{
                        cout << "That is not a city in Colorado. Please enter a valid city: ";
                        getline(cin, city);
                    }
                    while(g.checkCityReal(city) == false);
                }

                cout << "Enter the school you currently attend(or the last school you attened): ";
                string school;
                getline(cin, school);
                if(g.checkSchoolReal(school) == false){
                    do{
                        cout << "That is not a school in Colorado. Please enter a valid school: ";
                        getline(cin, school);
                    }
                    while(g.checkSchoolReal(school) == false);
                }
                cout << "Are you still attending this school? (YES of NO): ";
                string attending;
                getline(cin, attending);
                bool isAttending;
                if(attending == "NO"){
                    isAttending = false;
                }
                else{
                    isAttending = true;
                }

                cout << "Enter your primary sport: ";
                string sport1;
                string sport2;
                string sport3;
                string answer;
                getline(cin, sport1);
                if(g.checkSportInclusion(sport1) == false){
                    do{
                        cout << "That sport is not included in our program, and therefore we won't be able to find connections for you. Please enter a differnt sport that is included in this program: ";
                        getline(cin, sport1);
                    }
                    while(g.checkSportInclusion(sport1) == false);
                }
                cout << "Do you do any other sports? (YES or NO): ";
                getline(cin, answer);
                if(answer == "NO"){
                    sport2 = "";
                    sport3 = "";
                }
                else{
                    cout << "Enter your second sport: ";
                    getline(cin, sport2);
                    if(g.checkSportInclusion(sport2) == false){
                        do{
                            cout << "That sport is not included in our program, and therefore we won't be able to find connections for you." << endl;
                            cout << "Do you still have a second sport to insert? (YES of NO): ";
                            getline(cin, answer);
                            if(answer == "NO"){
                                sport2 = "";
                                sport3 = "";
                                break;
                            }
                            else{
                                cout << "Enter your second sport: ";
                                getline(cin, sport2);
                            }
                        }
                        while(g.checkSportInclusion(sport2) == false);
                    }
                    cout << "Do you do any other sports? (YES or NO): ";
                    getline(cin, answer);
                    if(answer == "NO"){
                        sport3 = "";
                    }
                    else{
                        cout << "Enter your third sport: ";
                        getline(cin, sport3);
                        if(g.checkSportInclusion(sport3) == false){
                            do{
                                cout << "That sport is not included in our program, and therefore we won't be able to find connections for you." << endl;
                                cout << "Do you still have a second sport to insert? (YES of NO): ";
                                getline(cin, answer);
                                if(answer == "NO"){
                                    sport3 = "";
                                    break;
                                }
                                else{
                                    cout << "Enter your third sport: ";
                                    getline(cin, sport3);
                                }
                            }
                            while(g.checkSportInclusion(sport3) == false);
                        }
                        cout << "The max amount of sports you can enter is 3 sports." << endl;
                    }
                }

                g.addUser(username, firstname, lastname, age, city, school, isAttending, sport1, sport2, sport3);
                break;
            }
            
            case 2: {
                cout<<"Enter a sport: ";
                string sport;
                getline(cin, sport);
                if(g.checkSportInclusion(sport) == false){
                    do{
                        cout << "That sport is not included in our program, and therefore we won't be able to find athletes for this sport. Please enter a different sport: ";
                        getline(cin, sport);
                    }
                    while(g.checkSportInclusion(sport) == false);
                }
                g.printSportAthletes(sport);
                break;
            } 

            case 3: {
                cout << "Enter the city you want to search in: ";
                string city;
                getline(cin, city);
                if(g.checkCityReal(city) == false){
                    do{
                        cout << "That is not a city in Colorado. Please enter a valid city: ";
                        getline(cin, city);
                    }
                    while(g.checkCityReal(city) == false);
                }
                
                cout<<"Enter a sport: ";
                string sport;
                getline(cin, sport);
                if(g.checkSportInclusion(sport) == false){
                    do{
                        cout << "That sport is not included in our program, and therefore we won't be able to find athletes for this sport. Please enter a different sport: ";
                        getline(cin, sport);
                    }
                    while(g.checkSportInclusion(sport) == false);
                }
                g.printCityAthletes(city, sport);
                break;
            }
            
            case 4: {
                cout << "Enter the school you want to search in: ";
                string school;
                getline(cin, school);
                if(g.checkSchoolReal(school) == false){
                    do{
                        cout << "That is not a school in Colorado. Please enter a valid school: ";
                        getline(cin, school);
                    }
                    while(g.checkCityReal(school) == false);
                }
                
                cout<<"Enter a sport: ";
                string sport;
                getline(cin, sport);
                if(g.checkSportInclusion(sport) == false){
                    do{
                        cout << "That sport is not included in our program, and therefore we won't be able to find athletes for this sport. Please enter a different sport: ";
                        getline(cin, sport);
                    }
                    while(g.checkSportInclusion(sport) == false);
                }
                g.printCurrentSchoolAlthles(school, sport);
                break;
            }

            case 5: {
                cout << "Enter the school you want to search in: ";
                string school;
                getline(cin, school);
                if(g.checkSchoolReal(school) == false){
                    do{
                        cout << "That is not a school in Colorado. Please enter a valid school: ";
                        getline(cin, school);
                    }
                    while(g.checkCityReal(school) == false);
                }
                
                cout<<"Enter a sport: ";
                string sport;
                getline(cin, sport);
                if(g.checkSportInclusion(sport) == false){
                    do{
                        cout << "That sport is not included in our program, and therefore we won't be able to find athletes for this sport. Please enter a different sport: ";
                        getline(cin, sport);
                    }
                    while(g.checkSportInclusion(sport) == false);
                }
                g.printSchoolAthleteAlumni(school, sport);
                break;
            }

            case 6: {
                cout << "Enter the username you want to edit: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }
                
                cout << "Enter the city you moved to: ";
                string city;
                getline(cin, city);
                if(g.checkCityReal(city) == false){
                    do{
                        cout << "That is not a city in Colorado. Please enter a valid city: ";
                        getline(cin, city);
                    }
                    while(g.checkCityReal(city) == false);
                }
                g.updateCity(username, city);
                break;
            }

            case 7: {
                cout << "Enter the username you want to edit: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }
                
                cout << "Enter the school you moved to: ";
                string school;
                getline(cin, school);
                if(g.checkSchoolReal(school) == false){
                    do{
                        cout << "That is not a school in Colorado. Please enter a valid school: ";
                        getline(cin, school);
                    }
                    while(g.checkSchoolReal(school) == false);
                }
                g.updateSchool(username, school);
                break;
            }

            case 8: {
                cout << "Enter the username you want to edit: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }
                
                cout << "Enter this user's new age: ";
                string age1;
                getline(cin, age1);
                int age = stoi(age1);
                g.updateAge(username, age);
                break;
            }

            case 9: {
                cout << "Enter the username you want to edit: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }
                
                cout << "Enter the sport do you want to add to this profile: ";
                string sport;
                getline(cin, sport);
                if(g.checkSportInclusion(sport) == false){
                    do{
                        cout << "That sport is not included in our program, and therefore we won't be able to find athletes for this sport. Please enter a different sport: ";
                        getline(cin, sport);
                    }
                    while(g.checkSportInclusion(sport) == false);
                }
                
                g.addSport(username, sport);
                break;
            }

            case 10: {
                cout << "Enter the username you want to edit: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }
                
                cout << "Enter the sport do you want to remove from this profile: ";
                string sport;
                getline(cin, sport);
                if(g.checkSportInclusion(sport) == false){
                    do{
                        cout << "That sport is not included in our program, and therefore we won't be able to find athletes for this sport. Please enter a different sport: ";
                        getline(cin, sport);
                    }
                    while(g.checkSportInclusion(sport) == false);
                }
                
                g.removeSport(username, sport);
                break;
            }

            case 11: {
                cout << "Enter the users first name: ";
                string first;
                getline(cin, first);

                cout << "Enter the users last name: ";
                string last;
                getline(cin, last);

                g.searchForUser(first, last);
                break;
            }

            case 12:{
                cout << "Enter the username you would like to get the number of connections for: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }
                
                g.printNumConnections(username);
                break;
            }

            case 13: {
                cout << "Enter the first username of the pair you want to connect: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }

                cout << "Enter the second username of the pair you want to connect: ";
                string username2;
                getline(cin, username2);
                if(g.checkUsernameReal(username2) == false || username == username2){
                    do{
                        if(g.checkUsernameReal(username2)==false){
                            cout << "That is not a username currently in our database. Please enter a valid username: ";
                            getline(cin, username2);
                        }
                        if(username == username2){
                            cout << "That is the same username you entered above. Please enter a different username: ";
                            getline(cin, username2);
                        }
                    }
                    while(g.checkUsernameReal(username2) == false || username == username2);
                }

                g.createConnection(username, username2);
                g.createConnection(username2, username);
                break;
            }

            case 14: {
                cout << "Enter the first username of the pair you want to remove a connection between: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }

                cout << "Enter the second username of the pair you want to remove a connection between: ";
                string username2;
                getline(cin, username2);
                if(g.checkUsernameReal(username2) == false || username == username2){
                    do{
                        if(g.checkUsernameReal(username2)==false){
                            cout << "That is not a username currently in our database. Please enter a valid username: ";
                            getline(cin, username2);
                        }
                        if(username == username2){
                            cout << "That is the same username you entered above. Please enter a different username: ";
                            getline(cin, username2);
                        }
                    }
                    while(g.checkUsernameReal(username2) == false || username == username2);
                }

                g.deleteConnection(username, username2);
                break;
            }

            case 15: {
                cout << "Enter the username you would like to see the connections of: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }

                g.getUserConnections(username);
                break;
            }

            case 16: {
                cout << "Enter the username you would like to see the secondary connections of: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }

                g.getUserSecondaryConncection(username);
                break;
            }

            case 17: {
                cout << "Enter the username you would like to see the recommendations for: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }

                g.getConnectionRecommendations(username);
                break;
            }

            case 18: {
                cout << "Enter the username you would like to add a post to: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }

                cout << "Enter the current month: ";
                string m;
                getline(cin, m);
                int month = stoi(m);

                cout << "Enter the current day: ";
                string d;
                getline(cin, d);
                int day = stoi(d);

                cout << "Enter the current year: ";
                string y;
                getline(cin, y);
                int year = stoi(y); 

                string answer;
                if(g.checkPostDateUsed(username, month, day, year) == true){
                    do{
                        cout << "This user has already posted on this date. Please only post once a day." << endl;
                        cout << "Would you like to publish a post on a different date? (YES or NO): ";
                        getline(cin, answer);
                        if(answer == "NO"){
                            cout << "Sorry, you cannot post on the same day twice.";
                            break;
                        }
                        else{
                            cout << "Enter the current month: ";
                            getline(cin, m);
                            month = stoi(m);

                            cout << "Enter the current day: ";
                            getline(cin, d);
                            day = stoi(d);

                            cout << "Enter the current year: ";
                            getline(cin, y);
                            year = stoi(y); 
                        }
                    }
                    while(g.checkPostDateUsed(username, month, day, year) == true);
                }
                if(answer == "NO"){
                    break;
                }

                cout <<"Enter the new post you would like to publish to this user's profile: ";
                string post;
                getline(cin, post);             

                g.addPost(username, month, day, year, post);
                break;
            }

            case 19: {
                cout << "Enter the username you would like to delete a post for: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }

                cout << "Enter the month the post was published: ";
                string m;
                getline(cin, m);
                int month = stoi(m);

                cout << "Enter the day the post was published ";
                string d;
                getline(cin, d);
                int day = stoi(d);

                cout << "Enter the year the post was published: ";
                string y;
                getline(cin, y);
                int year = stoi(y); 

                if(g.checkPostDateUsed(username, month, day, year) == false){
                    do{
                        cout << "This user hasn't posted on this date. Please enter a valid date." << endl;
                    
                        cout << "Enter the current month: ";
                        getline(cin, m);
                        month = stoi(m);

                        cout << "Enter the current day: ";
                        getline(cin, d);
                        day = stoi(d);

                        cout << "Enter the current year: ";
                        getline(cin, y);
                        year = stoi(y); 
                    }
                    while(g.checkPostDateUsed(username, month, day, year) == false);
                }

                g.deletePost(username, month, day, year);
                break;
            }

            case 20: {
                cout << "Enter the username you would like to edit of post for: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }

                cout << "Enter the month the post was published: ";
                string m;
                getline(cin, m);
                int month = stoi(m);

                cout << "Enter the day the post was published ";
                string d;
                getline(cin, d);
                int day = stoi(d);

                cout << "Enter the year the post was published: ";
                string y;
                getline(cin, y);
                int year = stoi(y); 

                if(g.checkPostDateUsed(username, month, day, year) == false){
                    do{
                        cout << "This user hasn't posted on this date. Please enter a valid date." << endl;
                    
                        cout << "Enter the current month: ";
                        getline(cin, m);
                        month = stoi(m);

                        cout << "Enter the current day: ";
                        getline(cin, d);
                        day = stoi(d);

                        cout << "Enter the current year: ";
                        getline(cin, y);
                        year = stoi(y); 
                    }
                    while(g.checkPostDateUsed(username, month, day, year) == false);
                }

                cout <<"Enter the new post you would like to publish to this user's profile: ";
                string post;
                getline(cin, post);

                g.editPost(username, month, day, year, post);
                break;
            }

            case 21: {
                cout << "Enter the username you would like to see all the posts of: ";
                string username;
                getline(cin, username);
                if(g.checkUsernameReal(username) == false){
                    do{
                        cout << "That is not a username currently in our database. Please enter a valid username: ";
                        getline(cin, username);
                    }
                    while(g.checkUsernameReal(username) == false);
                }

                g.getAllUserPosts(username);
                break;
            }

            case 22: default: {
                done = true;
                break;
            }
        }
        
    } 
    while(!done);
    
    cout << "Goodbye!" << endl;
    return 0;
}
