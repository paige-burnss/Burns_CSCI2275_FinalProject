#include "Graph.h"
#include "LinkedList.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;
   
    void Graph::constructCityList(std::string filename){
       //creates a vector of all the cities stored in the coloradoCities.txt file to be referenced later
        ifstream inFile(filename);

        string name = "";
        city temp;
        std::string line;
        
        while(getline(inFile, line)){
            stringstream ss(line);
            getline(ss, name);
            temp.name = name;
            cities.push_back(temp);
        }
    };

    void Graph::constructSchoolList(std::string filename){
       //creates a vector of all the schools stored in the coloradoHighSchools.txt file to be referenced later
        ifstream inFile(filename);

        string name = "";
        string loc = "";
        school temp;
        std::string line;

        while(std::getline(inFile, line)){
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, loc);
            temp.name = name;
            temp.location = loc;
            schools.push_back(temp);
        }
    };

    void Graph::constructSportList(std::string filename){
       //creates a vector of a number of popular sports stored in the sportsNames.txt file to be referenced later
        ifstream inFile(filename);

        string name = "";
        sport temp;
        std::string line;
        
        while(getline(inFile, line)){
            stringstream ss(line);
            getline(ss, name);
            temp.name = name;
            sports.push_back(temp);
        }
    };

    void Graph::generateGraph(std::string filename, std::string filename2) {
       //builds an initial graph with 21 different users and mulitple connections to be build on later in the program
        ifstream file(filename);
        ifstream file2(filename2);

        std::string first;
        std::string last;
        std::string username;
        string a1;
        int age;
        std::string city;
        std::string school;
        std::string sport1;
        std::string sport2;
        std::string sport3;
        std::string line;

        while(getline(file, line)){
            stringstream ss(line);
            getline(ss, first, ',');
            getline(ss, last, ',');
            getline(ss, username, ',');
            getline(ss, a1, ',');
            age = stoi(a1);
            getline(ss, city, ',');
            getline(ss, school, ',');
            getline(ss, sport1, ',');
            getline(ss, sport2, ',');
            if(sport2 == "null"){
                sport2 = "";
            }
            getline(ss, sport3, ',');
            if(sport3 == "null"){
                sport3 = "";
            }
            addUser(username, first, last, age, city, school, true, sport1, sport2, sport3);
        }
       //adds all the user vertices into the graph

        std::string username1;
        std::string word;
        int weight;

        while(getline(file2, line)){
            stringstream lineStream(line);
            getline(lineStream, username1, ',');

            for(int i=0; i<users.size();i++) {
                getline(lineStream, word, ',');
                weight = stoi(word);

                if(weight != 2 && weight != 0){
                    createConnection(username1, users[i].username);
                }
            }
        }
       //adds all the user connections into the graph
    };

    bool Graph::checkUserNameUnique(std::string username){
       //when a new user is being added, this function checks if a username has already been used because all usernames must be unique for this program 
       for(int i=0; i < users.size(); i++){
            if(users[i].username == username){
                return false;
            }
        }
       //for loop to run through all of the user vertices in the graph
        return true;
    }

    bool Graph::checkCityReal(std::string city){
       //checks if a city that is being inputted into this program in the runner is a valid city in colorado or not 
       for(int i = 0; i < cities.size(); i++){
            if(cities[i].name == city){
                return true;
            }
        }
        return false;
    }

    bool Graph::checkSchoolReal(std::string school){
       //checks if a school that is being inputted into this program in the runner is a valid high school in colorado or not  
       for(int i = 0; i < schools.size(); i++){
            if(schools[i].name == school){
                return true;
            }
        }
        return false;
    };

    bool Graph::checkSportInclusion(std::string sport){
       //checks if an sport that is being inputted into this program in the runner is included in the sports list 
       //if false, the runner states that they cannot use the social media program with that sport because it is relatively uncommon and they won't be able to make connections
        for(int i = 0; i < sports.size(); i++){
            if(sports[i].name == sport){
                return true;
            }
        }
        return false;
    };

    bool Graph::checkUsernameReal(std::string username){
       //checks if the username inputted in the runner is a valid username that is a part of the graph
        for(int i = 0; i < users.size(); i++){
            if(users[i].username == username){
                return true;
            }
        }
        return false;
    };

    void Graph::addUser(std::string username1, std::string first, std::string last, int age1, std::string city1, std::string school1, bool stillAttending, std::string sport1, std::string sport2, std::string sport3){
       //adds a new user vertice to the graph     
       user person (username1, first, last, age1, city1, school1, sport1, sport2, sport3);
       //creates a new user object
            users.push_back(person);
       //adds that user to the graph's user vertices vector
            city *temp = findCity2(city1);
            temp->currentResidents.push_back(person);
       //finds the city the user currently lives in and adds them to the current Residents vector for that city
            
            school *temp2 = findSchool2(school1);
            if(stillAttending == true){
                temp2->currentStudents.push_back(person);
            }
            else{
                temp2->pastStudents.push_back(person);
            }
       //finds the school the user currently or last attended and adds them to either the current students or past students vector for that specific school

            sport *spo1 = findSport2(sport1);
            spo1->athletes.push_back(person);
            if(sport2 != ""){
                sport *spo2 = findSport2(sport2);
                spo2->athletes.push_back(person);
                if(sport3 != ""){
                    sport *spo3 = findSport2(sport3);
                    spo3->athletes.push_back(person);
                }
            }
       //finds each sport the user inputted as participating in and adds the user to each sports atheltes vector
    };

    void Graph::printSportAthletes(std::string sport1){
       //prints out all of the users that currently have the inputted sport on their profile 
       std::cout << sport1 << " Athletes: " << std::endl;
        sport *temp = findSport2(sport1);
       //finds the sport out of the sport vector constructed from the sports list created at the beginning of the program
        for(int x = 0; x < temp->athletes.size(); x++){
            std::cout << temp->athletes[x].firstName << " " << temp->athletes[x].lastName << ": " << temp->athletes[x].username << std::endl;
        }
       //using the specific sports' atheletes vector, the for loop loops through the vector and prints out each current user's name and username
    };

    void Graph::printCityAthletes(std::string city1, std::string sport){
       //prints out all of the users that currently live in a certain city and have the inputted sport on their profile 
       std::cout << city1 << " Athletes in " << sport << ": " << std::endl;
        city *temp = findCity2(city1);
       //finds the city out of the city vector constructed from the coloradoCities list created at the beginning of the program
        for(int x = 0; x < temp->currentResidents.size(); x++){
            if(temp->currentResidents[x].sports[0] == sport || temp->currentResidents[x].sports[1] == sport || temp->currentResidents[x].sports[2] == sport){
                std::cout << temp->currentResidents[x].firstName << " " << temp->currentResidents[x].lastName << ": " << temp->currentResidents[x].username << std::endl;
            }
        }
       //using the specific cities' current residents vector, and checking if each user in that vector does the specified sport inputted into the program, 
       //the for loop loops through the vector and prints out each current resident of that city and current athlete of that sport's name and username
    };

    void Graph::printCurrentSchoolAlthles(std::string school1, std::string sport){
       //prints out all of the users that currenlty go to a certain school and have the inputted sport on their profile
        school *temp = findSchool2(school1);
       //finds the schools out of the school vector constructed from the coloradoHigh Schools list created at the beginning of the program
        std::cout << school1 << "(" << temp->location << ")" << " Current Athletes in " << sport << ": " << std::endl;
        for(int x = 0; x < temp->currentStudents.size(); x++){
            if(temp->currentStudents[x].sports[0] == sport || temp->currentStudents[x].sports[1] == sport || temp->currentStudents[x].sports[2] == sport){
                std::cout << temp->currentStudents[x].firstName << " " << temp->currentStudents[x].lastName << ": " << temp->currentStudents[x].username << std::endl;
            }
        }
       //using the specific schools' current students vector, and checking if each user in that vector does the specified sport inputted into the program, 
       //the for loop loops through the vector and prints out each current student of that school and current athlete of that sport's name and username
    };
    
    void Graph::printSchoolAthleteAlumni(std::string school1, std::string sport){
       //prints out all of the users that used to go to a certain school (now alumni of the school) and have the inputted sport on their profile
        school *temp = findSchool2(school1);
       //finds the schools out of the school vector constructed from the coloradoHigh Schools list created at the beginning of the program
        std::cout << school1 << "(" << temp->location << ")" << " Past Athletes in " << sport << ": " << std::endl;
        for(int x = 0; x < temp->pastStudents.size(); x++){
            if(temp->pastStudents[x].sports[0] == sport || temp->pastStudents[x].sports[1] == sport || temp->pastStudents[x].sports[2] == sport){
                std::cout << temp->pastStudents[x].firstName << " " << temp->pastStudents[x].lastName << ": " << temp->pastStudents[x].username << std::endl;
            }
        }
       //using the specific schools' past students vector, and checking if each user in that vector does the specified sport inputted into the program, 
       //the for loop loops through the vector and prints out each past student of that school and current athlete of that sport's name and username
    };

    void Graph::updateCity(std::string username, std::string city1){
       //updates the city that is currently stored in a user's profile
        user *person = findUser2(username);
       //finds specific user that wants to edit their city
        city *temp = findCity2(person->city);
       //finds the city the user currently has on their profile
        for(int i = 0; i < temp->currentResidents.size(); i++){
            if(temp->currentResidents[i].username == person->username){
                temp->currentResidents.erase(temp->currentResidents.begin() + i);
            }
        }
       //using the city found above, a for loop goes through all of the users stored in that city's currentResidents list until the specified user is found and removed from the current residents vector of that city
        person->city = city1;
       //the city on the specified user's profile is updated to the new inputted city
        city *temp2 = findCity2(city1);
        temp2->currentResidents.push_back(*person);
       //the new inputted city is found in the cities vector, and the user is added to the currentResidents vector of the new inputted city
    };

    void Graph::updateSchool(std::string username, std::string school1){
       //updates the school that is currently stored in a user's profile
        user *person = findUser2(username);
       //finds speciic user that wants to edit their school
        school *temp = findSchool2(person->school);
       //finds the school the user currently has on their profile
        for(int x = 0; x < temp->currentStudents.size(); x++){
            if(temp->currentStudents[x].username == person->username){
                temp->currentStudents.erase(temp->currentStudents.begin() + x);
            }
        }
       //using the school found above, a for loop goes through all the users stored in that school's current Students lsit until the specified user is found and removed from the current Students vector of that school 
        temp->pastStudents.push_back(*person);
       //the user is added to the current school's past students vector
        person->school = school1;
       //the school on the specified user's profile is updated to the new inputted school
        school *temp2 = findSchool2(school1);
        temp2->currentStudents.push_back(*person);
       //the new inputted school is found in the schools vector, and the user is added to the current students vector of the new inputted school
    };

    void Graph::updateAge(std::string username, int age1){
       //updates the age that is currently stored in a user's profile
        user *person = findUser2(username);
       //finds specific user that wants to edit their age
        person->age = age1;
       //the age on the specified user's profile is updated to the new inputted age
    };

    void Graph::removeSport(std::string username, std::string sport1){
       //removes a sport from a user's profile (only if a user has a sport left on their profile after this sport is removed)
        user *person = findUser2(username);
       //finds specific user that wants to remove a sport from their profile
        if(person->sports[0] != sport1 && person->sports[1] != sport1 && person->sports[2] != sport1){
            std::cout << "This user doesn't currently do the sport you want to remove from this profile." << std::endl;
            return;
        }
       //checks if the person has the specified sport on their profile
        if(person->sports[1] == "" && person->sports[2] == ""){
            std::cout << "This user currently only has one sport on their profile. You cannot remove a sport unless a user will still have one sport on their profile." << std::endl;
            return;
        }
       //checks if the person would still have one sport left on their profile after they delete the specified sport
        if(person->sports[0] == sport1){
            person->sports[0] = person->sports[1];
            person->sports[1] = person->sports[2];
            person->sports[2] = "";
        }
       //if the desired sport to be removed is at the front of the sports array of the user's profile, the other two sports are moved up a position in the array and the last place in the array is left blank
        else if (person->sports[1] == sport1){
            person->sports[1] = person->sports[2];
            person->sports[2] = "";
        }
       //if the desired sport to be removed is in the second position of the sports array of the user's profile, the other sport is moved up a position in the array and the last place in the array is left blank
        else{
            person->sports[2] = "";
        }
       //if the desired sport to be removed is in the last position of the sports array of the user's profile, the last position is redefined as an empty string
        sport *temp = findSport2(sport1);
       //find the sport that was removed from the user's profile
        for(int x = 0; x < temp->athletes.size(); x++){
            if(temp->athletes[x].username == person->username){
                temp->athletes.erase(temp->athletes.begin() + x);
            }
        }
       //using the sport found above, a for loop goes through all the users stored in that sport's althetes list until the specified user is found and removed from the athletes vector of that school 
    };
    
    void Graph::addSport(std::string username, std::string sport1){
       //adds another sport to a user's profile (but only if they don't have a max of 3 sports on their profile already)
        user *person = findUser2(username);
       //finds specific user that wants to add a sport to their profile
        if(person->sports[2] != ""){
            std::cout << "This user already currently has the max of 3 sports on their profile." << std::endl;
            return;
        }
       //checks to see if this user has 3 sports on their profile
        if(person->sports[1] == ""){
            person->sports[1] = sport1;
        }
        else{
            person->sports[2] = sport1;
        }
       //inserts new specified sport in a specific position, depending on how many sports are already in a user's profile
        sport *temp = findSport2(sport1);
       //finds the specified sport that a user wants to add to their profile
        temp->athletes.push_back(*person);
       //adds user to the vector holding all of the athletes of the new specified sport
    };

    void Graph::searchForUser(std::string first1, std::string last1){
       //searches for a user using the first and last name of a user
       //can return multiple different users if they all have the same name
        vector <user> first;
       //create a new vector of users to add users with the same first name as the specified first name to
        for(int i = 0; i < users.size(); i++){
            if(users[i].firstName == first1){
                first.push_back(users[i]);
            }
        }
       //uses for loop to go through all the user vertices in the graph. if a user has the same first name as the specified first name, they are added to the first vector
        if(first.size() == 0){
            std::cout << "There is no user with this name." << std::endl;
            return;
        }
       //if the size of the first vector is 0, that means there are no users with the specified name, and the function is returned
        vector <user> last;
       //create a new vecotr of users to add users with the same last name as te specified last name to
        for(int i = 0; i < first.size(); i++){
            if(first[i].lastName == last1){
                last.push_back(first[i]);
            }
        }
       //uses for loop to go through all the users in the first vector. if a user with the same first name specified also has the same specified last name, they are added to the last vector
        if(last.size() == 0){
            std::cout << "There is no user with this name." << std::endl;
            return;
        }
       //if the size of the last vector is 0, that means there are no users with the specified name, and the function is returned
        for(int i = 0; i < last.size(); i++){
            std::cout << last[i].firstName << " " << last[i].lastName << ", " << last[i].username << ", " << last[i].age << ", " << last[i].city << ", " << last[i].school<< std::endl;
            std::cout <<last[i].sports[0];
            if(last[i].sports[1] != ""){
                std::cout << ", " << last[i].sports[1];
            }
            if(last[i].sports[2] != ""){
                std::cout << ", " << last[i].sports[2];
            }
            std::cout << "." << std::endl;
        }
       //the for loop goes through all the users in the last vector, whichis comprised of users with the same first and last name specified in the inputs, and prints out each user's profile information
    };

    void Graph::printNumConnections(std::string username){
       //finds the number of connections a user has (kind of like followers)
        user *person = findUser2(username);
       //finds the specified user of which someone would like to see their number of connections
        std::cout << "Number of Connections: " << person->numConnections << std::endl;
       //prints out the number of connections of the specified user
    };

    void Graph::createConnection(std::string username1, std::string username2){
       //creates a connection between one user and another 
       for(int i = 0; i < users.size(); i++){
          //loops through all the user vertices in the graph to find the first username
            if(users[i].username == username1){
               //checks for the usernames of all user vertices to see if they match the specified first username inputted
                for(int j = 0; j < users.size(); j++){
                   //loops through all the user vertices in the graph to find the second username 
                    if(users[j].username == username2 && i != j){
                       //check for the usernames of all user vertices to see if they match the specified second username inputted, and also checks that the first and last username are not stored in the same place (i.e. the usernames are identical and cannot create a connection between them)
                        adjacent temp;
                        temp.u = &users[j];
                        temp.weight = 1;
                       //creates an adjacent item with the second username
                        users[i].adj.push_back(temp);
                        users[i].numConnections++;
                       //pushes the new adjacent item into the adjacent vector of the first username and increases the number of connections for the first username
                    }
                }
            }
        }
    };

    void Graph::deleteConnection(std::string username1, std::string username2){
       //deletes a connection between two specified users (kind of like unfollowing) 
       user *u1 = findUser2(username1);
        user *u2 = findUser2(username2);
       //finds both specified users from the usernames specified in the input
        for(int i = 0; i < u1->adj.size(); i++){
           //for loop to go through all the adjacent items in the username1 profile
            if(u1->adj[i].u->username == u2->username){
               //checks if the username of the current adjacent item is the same as the second username
                u1->adj.erase(u1->adj.begin()+i);
               //erase the adjacent item with the second username from the adjacent vector of the first username
                for(int x = 0; x < u2->adj.size(); x++){
                   //for loop to go through all the adjacent items in the userame2 profile
                    if(u2->adj[x].u->username == u1->username){
                       //checks if the username of the current adjacent item is the same as the first username
                        u2->adj.erase(u2->adj.begin()+x);
                       //erase the adjacent item with the first username from the adjacent vector of the second username
                    }
                }
                u1->numConnections--;
                u2->numConnections--;
               //decreases the number of connections for both users
                return;
            }
        }
        std::cout << "These two users are not connected." << std::endl;
       //if the above code isn't executed, it means the users aren't connected
    };

    void Graph::getUserConnections(std::string username){
       //gets all the connections of a certain user
        user *u1 = findUser2(username);
       //finds the specified user for which someone would like to see the connections of
        std::cout << "Connections: " << std::endl;
        if(u1->adj.size() == 0){
            std::cout << "This user currently has no connections" << std::endl;
            return;
        }
       //checks if the user has an adjacent vector size of 0, meaning they have no connections
        for(int i = 0; i < u1->adj.size(); i++){
            std::cout << u1->adj[i].u->firstName << " " << u1->adj[i].u->lastName << " (" << u1->adj[i].u->username << ")" << std::endl;
        }
       //for loop going through each adjacent vector item and printing out each first and last name and username of the connecitons
    };

    void Graph::getUserSecondaryConncection(std::string username){
       //returns a list of users that are connected to the specified user's connections (kind of like friends of friends)
        user u1 = findUser(username);
       //finds the specified user for which someone would like to see the secondary connections of
        vector <user*> secondary;
       //creates a new vector to hold all the secondary connections
        for(int i = 0; i < u1.adj.size(); i++){
           //loops through the adjacent items of the specified user
            for(int x = 0; x < u1.adj[i].u->adj.size(); x++){
               //loops through the adjcent items of the current adjacent item of the specifed user
                if(contains(secondary, u1.adj[i].u->adj[x].u->username) == false && contains2(u1.adj, u1.adj[i].u->adj[x].u->username) == false && u1.username != u1.adj[i].u->adj[x].u->username){
                    secondary.push_back(u1.adj[i].u->adj[x].u);
                }
               //checks if the current secondary connection is already in the secondary vector, or already a primary connection of the specified user, or the user themselves
               //if none of these are true, the user is added to the secondary vector
            }
        }
        std::cout << "Connections: " << std::endl;
        for(int i = 0; i < secondary.size(); i++){
            std::cout << secondary[i]->firstName << " " << secondary[i]->lastName << " (" << secondary[i]->username << ")" << std::endl;
        }
       //for loop ging through each secondary connection and printing out each first and last name and username of the connections
    };

    void Graph::getConnectionRecommendations(std::string username){
       //returns a max of 3 connection recomendation for a specified user
        user u1 = findUser(username);
       //fins specified user that would like connection recommendations
        vector <user*> secondary;
        for(int i = 0; i < u1.adj.size(); i++){
            for(int x = 0; x < u1.adj[i].u->adj.size(); x++){
                if(contains(secondary, u1.adj[i].u->adj[x].u->username) == false && contains2(u1.adj, u1.adj[i].u->adj[x].u->username) == false && u1.username != u1.adj[i].u->adj[x].u->username){
                    secondary.push_back(u1.adj[i].u->adj[x].u);
                }
            }
        }
       //finds secondary connections of a user (so that connection recs are users who are connected to a user's connections - already a similar interest)
        vector <user*> recs;
       //create a new vector to hold the potential user profile connection recomendations
        for(int i = 0; i < secondary.size(); i++){
            int score;
            if(u1.age == secondary[i]->age){
                score++;
            }
            if(u1.city == secondary[i]->city){
                score++;
            }
            if(u1.school == secondary[i]->school){
                score++;
            }
            if(u1.sports[0] == secondary[i]->sports[0] || u1.sports[0] == secondary[i]->sports[1] || u1.sports[0] == secondary[i]->sports[2]){
                score++;
            }
            if(u1.sports[1] == secondary[i]->sports[0] || u1.sports[1] == secondary[i]->sports[1] || u1.sports[1] == secondary[i]->sports[2]){
                score++;
            }
            if(u1.sports[2] == secondary[i]->sports[0] || u1.sports[2] == secondary[i]->sports[1] || u1.sports[2] == secondary[i]->sports[2]){
                score++;
            }
            if(score >= 2){
                recs.push_back(secondary[i]);
            }
        }
       //for loop going through all the secondary connections. checks if each secondary connection has similar profile attributes of the specified user and if they have two or more things in common, they get added to the recs vector
        if(recs.size() == 0){
            std::cout <<"Sorry there are no user recomendations that can be made at this time. " << std::endl;
            return;
        }
       //checks if the recs vector size is 0, meaning that no one had that many similarities
        if(recs.size() == 1){
            std::cout << recs[0]->firstName << " " << recs[0]->lastName << " (" << recs[0]->username << ")" << std::endl;
            return;
        }
        if(recs.size() == 2){
            std::cout << recs[0]->firstName << " " << recs[0]->lastName << " (" << recs[0]->username << ")" << std::endl;
            std::cout << recs[1]->firstName << " " << recs[1]->lastName << " (" << recs[1]->username << ")" << std::endl;
            return;
        }
        if(recs.size() == 3){
            std::cout << recs[0]->firstName << " " << recs[0]->lastName << " (" << recs[0]->username << ")" << std::endl;
            std::cout << recs[1]->firstName << " " << recs[1]->lastName << " (" << recs[1]->username << ")" << std::endl;
            std::cout << recs[2]->firstName << " " << recs[2]->lastName << " (" << recs[2]->username << ")" << std::endl;
            return;
        }
       //checks if recs size is 3 or less, meaning printing out all the contents in the vector
        int num1 = rand() % recs.size();
        int num2 = rand() % recs.size();
        while(num1 == num2){
            num2 = rand() % recs.size();
        }
        int num3 = rand() % recs.size();
        while(num3 == num2 || num3 == num1){
            num3 = rand() % recs.size();
        }
       //if recs size is greater than 3, 3 random numbers are genreated (and garunteed they aren't the same)
        std::cout << recs[num1]->firstName << " " << recs[num1]->lastName << " (" << recs[num1]->username << ")" << std::endl;
        std::cout << recs[num2]->firstName << " " << recs[num2]->lastName << " (" << recs[num2]->username << ")" << std::endl;
        std::cout << recs[num3]->firstName << " " << recs[num3]->lastName << " (" << recs[num3]->username << ")" << std::endl;
       //the 3 users at the loctions in recs of the random numbers are printed out
    };

    void Graph::addPost(std::string username, int month, int day, int year, std::string post){
       //adds a new post to a user's profile 
       user *u1 = findUser2(username);
       //finds specified user that would like to make a post
        u1->posts->insert(month, day, year, post);
       //uses Linked List class to insert a post to the user's linked list of posts
    };

    bool Graph::checkPostDateUsed(std::string username, int month, int day, int year){
       //checks if the date of a post that is desired to be posted has already been used(users only allowed to make one post per day) 
       user *u1 = findUser2(username);
       //finds specified user that would like to check if the date was already posted on
        LLNode *temp = u1->posts->head;
        while(temp != nullptr){
            if(temp->month == month && temp->day == day && temp->year == year){
                return true;
            }
            temp = temp->next;
        }
       //runs through the entire linked list of the user's posts, and if the date specified in the input matches the date of one of the posts, the funciton returns true
        return false;
    };

    void Graph::deletePost(std::string username, int month, int day, int year){
       //deletes a post from a user's profile 
       user *u1 = findUser2(username);
       //finds specified user that would like to delete a post from their profile
        u1->posts->remove(month, day, year);
       //uses Linked List class to delete a post from the user's linked list of posts
    };

    void Graph::editPost(std::string username, int month, int day, int year, std::string newPost){
       //edits a post on a user's profile 
       user *u1 = findUser2(username);
       //finds specified user that would like to edit a post from their profile
        u1->posts->edit(month, day, year, newPost);
       //uses Linked List class to edit a post from the user's linked list of posts
    };

    void Graph::getAllUserPosts(std::string username){
       //prints out all of a user's posts on their profile 
       user *u1 = findUser2(username);
       //finds specified user that would like to print out all their posts
        u1->posts->printLinkedList();
       //uses Linked List class to print out the posts from a user's linked list of posts
    };

    user Graph::findUser(std::string username){
       //finds a user in the graph from an inputted username and returns the actual user(not a pointer) 
       user temp;
       //create new user object
        for(int i = 0; i < users.size(); i++){
            if(users[i].username == username){
                temp = users[i];
                return temp;
            }
        }
       //loops through all the verticies in the graph. if the username of the current for loop user is the same as the specified username, temp is set to that user and is returned 
        return temp;
    };

    user *Graph::findUser2(std::string username){
       //finds a user in the graph from an inputted username but returns a pointer(not actual user) 
       user *temp = nullptr;
       //create new user pointer
        for(int i = 0; i < users.size(); i++){
            if(users[i].username == username){
                temp = &users[i];
                return temp;
            }
        }
       //loops through all the verticies in the graph. if the username of the current for loop user is the same as the specified username, temp is set to that user and is returned 
        return temp;
    }

    city *Graph::findCity2(std::string name){
       //finds a city in the graph from an inputted city name but returns a pointer(not actual user) 
       city *temp = nullptr;
       //create new city pointer
        for(int i = 0; i < cities.size(); i++){
            if(cities[i].name == name){
                temp = &cities[i];
                return temp;
            }
        }
       //loops through all the cities in the graph. if the name of the current for loop city is the same as the specified city name, temp is set to that city and is returned
        return temp;
    }

    school *Graph::findSchool2(std::string name){
       //finds a school in the graph from an inputted school name but returns a pointer(not actual user)  
       school *temp = nullptr;
       //creates a new school pointer
        for(int i = 0; i < schools.size(); i++){
            temp = &schools[i];
            return temp;
        }
       //loops through all the schools in the graph. if the name of the current for loop school is the same as the specified school name, temp is set to that school and is returned
        return temp;
    }

    sport *Graph::findSport2(std::string name){
       //finds a sport in the graph from an inputted sport name but returns a pointer(not actual user)  
       sport * temp = nullptr;
       //creates a new sport pointer
        for(int i = 0; i < sports.size(); i++){
            if(sports[i].name == name){
                temp = &sports[i];
                return temp;
            }
        }
       //loops through all the sports in the graph. if the name of the current for loop sport is the same as the specified sport name, temp is set to that sport and is returned
        return temp;
    }

    bool Graph::contains(vector<user*> users1, std::string username){
       //checks if a specified username is included in a vector full of user pointers (used in user recomendation and secondary user connection functions) 
       for(int i = 0; i < users1.size(); i++){
            if(users1[i]->username == username){
                return true;
            }
        }
       //loops through the entire vector inputted, and if a username matches the specified username, the function returns true
        return false;
    };

    bool Graph::contains2(vector<adjacent> users1, std::string username){
       //checks if a specified username is included in a vector full of adjacent items (used in user recomendation and secondary user connection functions)  
       for(int i = 0; i < users1.size(); i++){
            if(users1[i].u->username == username){
                return true;
            }
        }
       //loops through the entire vector inputted, and if a username matches the specified username, the function returns true
        return false;
    };
