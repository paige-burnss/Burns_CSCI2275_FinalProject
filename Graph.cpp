#include "Graph.h"
#include "LinkedList.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;
    
    void Graph::constructCityList(std::string filename){
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

        std::string username1;
        std::string word;
        int weight;

        while(getline(file2, line)){
            stringstream lineStream(line);
            getline(lineStream, username1, ',');

            for(int i=0; i<users.size();i++) {
                getline(lineStream, word, ',');
                weight = stoi(word);

                if(weight != -1 && weight != 0){
                    createConnection(username1, users[i].username);
                }
            }
        }
    };

    bool Graph::checkUserNameUnique(std::string username){
        for(int i=0; i < users.size(); i++){
            if(users[i].username == username){
                return false;
            }
        }
        return true;
    }

    bool Graph::checkCityReal(std::string city){
        for(int i = 0; i < cities.size(); i++){
            if(cities[i].name == city){
                return true;
            }
        }
        return false;
    }

    bool Graph::checkSchoolReal(std::string school){
        for(int i = 0; i < schools.size(); i++){
            if(schools[i].name == school){
                return true;
            }
        }
        return false;
    };

    bool Graph::checkSportInclusion(std::string sport){
        for(int i = 0; i < sports.size(); i++){
            if(sports[i].name == sport){
                return true;
            }
        }
        return false;
    };

    bool Graph::checkUsernameReal(std::string username){
        for(int i = 0; i < users.size(); i++){
            if(users[i].username == username){
                return true;
            }
        }
        return false;
    };

    void Graph::uncheck() {
        for (int i = 0; i < users.size(); i++) {
            users[i].checked = false;
        }
    };

    void Graph::addUser(std::string username1, std::string first, std::string last, int age1, std::string city1, std::string school1, bool stillAttending, std::string sport1, std::string sport2, std::string sport3){
            user person;
            person.username = username1;
            person.firstName = first;
            person.lastName = last;
            person.age =  age1;
            person.city = city1;
            person.school = school1;
            person.sports[0] = sport1;
            person.sports[1]= sport2; 
            person.sports[2] =sport3;
            users.push_back(person);
            city *temp = findCity2(city1);
            temp->currentResidents.push_back(person);
            
            school *temp2 = findSchool2(school1);
            if(stillAttending == true){
                temp2->currentStudents.push_back(person);
            }
            else{
                temp2->pastStudents.push_back(person);
            }

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
    };

    void Graph::printSportAthletes(std::string sport1){
        std::cout << sport1 << " Athletes: " << std::endl;
        sport *temp = findSport2(sport1);
        for(int x = 0; x < temp->athletes.size(); x++){
            std::cout << temp->athletes[x].firstName << " " << temp->athletes[x].lastName << ": " << temp->athletes[x].username << std::endl;
        }
    };

    void Graph::printCityAthletes(std::string city1, std::string sport){
        std::cout << city1 << " Athletes in " << sport << ": " << std::endl;
        city *temp = findCity2(city1);
        for(int x = 0; x < temp->currentResidents.size(); x++){
            if(temp->currentResidents[x].sports[0] == sport || temp->currentResidents[x].sports[1] == sport || temp->currentResidents[x].sports[2] == sport){
                std::cout << temp->currentResidents[x].firstName << " " << temp->currentResidents[x].lastName << ": " << temp->currentResidents[x].username << std::endl;
            }
        }
    };

    void Graph::printCurrentSchoolAlthles(std::string school1, std::string sport){
        school *temp = findSchool2(school1);
        std::cout << school1 << "(" << temp->location << ")" << " Current Athletes in " << sport << ": " << std::endl;
        for(int x = 0; x < temp->currentStudents.size(); x++){
            if(temp->currentStudents[x].sports[0] == sport || temp->currentStudents[x].sports[1] == sport || temp->currentStudents[x].sports[2] == sport){
                std::cout << temp->currentStudents[x].firstName << " " << temp->currentStudents[x].lastName << ": " << temp->currentStudents[x].username << std::endl;
            }
        }
    };
    
    void Graph::printSchoolAthleteAlumni(std::string school1, std::string sport){
        school *temp = findSchool2(school1);
        std::cout << school1 << "(" << temp->location << ")" << " Past Athletes in " << sport << ": " << std::endl;
        for(int x = 0; x < temp->pastStudents.size(); x++){
            if(temp->pastStudents[x].sports[0] == sport || temp->pastStudents[x].sports[1] == sport || temp->pastStudents[x].sports[2] == sport){
                std::cout << temp->pastStudents[x].firstName << " " << temp->pastStudents[x].lastName << ": " << temp->pastStudents[x].username << std::endl;
            }
        }
    };

    void Graph::updateCity(std::string username, std::string city1){
        user *person = findUser2(username);
        city *temp = findCity2(person->city);
        for(int i = 0; i < temp->currentResidents.size(); i++){
            if(temp->currentResidents[i].username == person->username){
                temp->currentResidents.erase(temp->currentResidents.begin() + i);
            }
        }
        person->city = city1;
        city *temp2 = findCity2(city1);
        temp2->currentResidents.push_back(*person);
    };

    void Graph::updateSchool(std::string username, std::string school1){
        user *person = findUser2(username);
        school *temp = findSchool2(person->school);
        for(int x = 0; x < temp->currentStudents.size(); x++){
            if(temp->currentStudents[x].username == person->username){
                temp->currentStudents.erase(temp->currentStudents.begin() + x);
            }
        }
        temp->currentStudents.push_back(*person);
        person->school = school1;
        school *temp2 = findSchool2(school1);
        temp2->currentStudents.push_back(*person);
    };

    void Graph::updateAge(std::string username, int age1){
        user *person = findUser2(username);
        person->age = age1;
    };

    void Graph::removeSport(std::string username, std::string sport1){
        user *person = findUser2(username);
        if(person->sports[0] != sport1 && person->sports[1] != sport1 && person->sports[2] != sport1){
            std::cout << "This user doesn't currently do the sport you want to remove from this profile." << std::endl;
            return;
        }
        if(person->sports[1] == "" && person->sports[2] == ""){
            std::cout << "This user currently only has one sport on their profile. You cannot remove a sport unless a user will still have one sport on their profile." << std::endl;
            return;
        }
        if(person->sports[0] == sport1){
            person->sports[0] = person->sports[1];
            person->sports[1] = person->sports[2];
            person->sports[2] = "";
        }
        else if (person->sports[1] == sport1){
            person->sports[1] = person->sports[2];
            person->sports[2] = "";
        }
        else{
            person->sports[2] = "";
        }
        sport *temp = findSport2(sport1);
        for(int x = 0; x < temp->athletes.size(); x++){
            if(temp->athletes[x].username == person->username){
                temp->athletes.erase(temp->athletes.begin() + x);
            }
        }
    };
    
    void Graph::addSport(std::string username, std::string sport1){
        user *person = findUser2(username);
        if(person->sports[2] != ""){
            std::cout << "This user already currently has the max of 3 sports on their profile." << std::endl;
            return;
        }
        if(person->sports[1] == ""){
            person->sports[1] = sport1;
        }
        else{
            person->sports[2] = sport1;
        }
        sport *temp = findSport2(sport1);
        temp->athletes.push_back(*person);
    };

    void Graph::searchForUser(std::string first1, std::string last1){
        vector <user> first;
        for(int i = 0; i < users.size(); i++){
            if(users[i].firstName == first1){
                first.push_back(users[i]);
            }
        }
        if(first.size() == 0){
            std::cout << "There is no user with this name." << std::endl;
            return;
        }
        vector <user> last;
        for(int i = 0; i < first.size(); i++){
            if(first[i].lastName == last1){
                last.push_back(first[i]);
            }
        }
        if(last.size() == 0){
            std::cout << "There is no user with this name." << std::endl;
            return;
        }
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
    };

    void Graph::createConnection(std::string username1, std::string username2){
        for(int i = 0; i < users.size(); i++){
            if(users[i].username == username1){
                for(int j = 0; j < users.size(); j++){
                    if(users[j].username == username2 && i != j){
                        adjacent temp;
                        temp.u = &users[j];
                        temp.weight = 1;
                        users[i].adj.push_back(temp);
                        users[i].numConnections++;
                    }
                }
            }
        }
    };

    void Graph::deleteConnection(std::string username1, std::string username2){
        user u1 = findUser(username1);
        user u2 = findUser(username2);
        for(int i = 0; i < u1.adj.size(); i++){
            if(u1.adj[i].u->username == u2.username){
                std::cout << i << std::endl;
                u1.adj.erase(u1.adj.begin() + i);
                for(int x = 0; x < u2.adj.size(); x++){
                    if(u2.adj[x].u->username == u1.username){
                        std::cout << x << std::endl;
                        u2.adj.erase(u2.adj.begin() + x);
                    }
                }
                u1.numConnections--;
                u2.numConnections--;
                return;
            }
        }
        std::cout << "These two users are not connected." << std::endl;
    };

    void Graph::getUserConnections(std::string username){
        user u1 = findUser(username);
        std::cout << "Connections: " << std::endl;
        if(u1.adj.size() == 0){
            std::cout << "This user currently has no connections" << std::endl;
            return;
        }
        for(int i = 0; i < u1.adj.size(); i++){
            std::cout << u1.adj[i].u->firstName << " " << u1.adj[i].u->lastName << " (" << u1.adj[i].u->username << ")" << std::endl;
        }
    };

    void Graph::getUserSecondaryConncection(std::string username){
        user u1 = findUser(username);
        vector <user*> secondary;
        for(int i = 0; i < u1.adj.size(); i++){
            for(int x = 0; x < u1.adj[i].u->adj.size(); x++){
                if(contains(secondary, u1.adj[i].u->adj[x].u->username) == false && contains2(u1.adj, u1.adj[i].u->adj[x].u->username) == false && u1.username != u1.adj[i].u->adj[x].u->username){
                    secondary.push_back(u1.adj[i].u->adj[x].u);
                }
            }
        }
        std::cout << "Connections: " << std::endl;
        for(int i = 0; i < secondary.size(); i++){
            std::cout << secondary[i]->firstName << " " << secondary[i]->lastName << " (" << secondary[i]->username << ")" << std::endl;
        }
    };

    void Graph::getConnectionRecommendations(std::string username){
        user u1 = findUser(username);
        vector <user*> secondary;
        for(int i = 0; i < u1.adj.size(); i++){
            for(int x = 0; x < u1.adj[i].u->adj.size(); x++){
                if(contains(secondary, u1.adj[i].u->adj[x].u->username) == false && contains2(u1.adj, u1.adj[i].u->adj[x].u->username) == false && u1.username != u1.adj[i].u->adj[x].u->username){
                    secondary.push_back(u1.adj[i].u->adj[x].u);
                }
            }
        }
        vector <user*> recs;
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
        if(recs.size() == 0){
            std::cout <<"Sorry there are no user recomendations that can be made at this time. " << std::endl;
            return;
        }
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
        int num1 = rand() % recs.size();
        int num2 = rand() % recs.size();
        while(num1 == num2){
            num2 = rand() % recs.size();
        }
        int num3 = rand() % recs.size();
        while(num3 == num2 || num3 == num1){
            num3 = rand() % recs.size();
        }
        std::cout << recs[num1]->firstName << " " << recs[num1]->lastName << " (" << recs[num1]->username << ")" << std::endl;
        std::cout << recs[num2]->firstName << " " << recs[num2]->lastName << " (" << recs[num2]->username << ")" << std::endl;
        std::cout << recs[num3]->firstName << " " << recs[num3]->lastName << " (" << recs[num3]->username << ")" << std::endl;
    };

    void Graph::addPost(std::string username, int month, int day, int year, std::string post){
        user u1 = findUser(username);
        u1.posts.insert(month, day, year, post);
    };

    bool Graph::checkPostDateUsed(std::string username, int month, int day, int year){
        user u1 = findUser(username);
        LLNode *temp = u1.posts.head;
        while(temp != nullptr){
            if(temp->month == month && temp->day == day && temp->year == year){
                return true;
            }
        }
        return false;
    };

    void Graph::deletePost(std::string username, int month, int day, int year){
        user u1 = findUser(username);
        u1.posts.remove(month, day, year);
    };

    void Graph::editPost(std::string username, int month, int day, int year, std::string newPost){
        user u1 = findUser(username);
        u1.posts.edit(month, day, year, newPost);
    };

    void Graph::getAllUserPosts(std::string username){
        user u1 = findUser(username);
        u1.posts.printLinkedList();
    };

    user Graph::findUser(std::string username){
        user temp;
        for(int i = 0; i < users.size(); i++){
            if(users[i].username == username){
                temp = users[i];
                return temp;
            }
        }
        return temp;
    };

    user *Graph::findUser2(std::string username){
        user *temp = nullptr;
        for(int i = 0; i < users.size(); i++){
            if(users[i].username == username){
                temp = &users[i];
                return temp;
            }
        }
        return temp;
    }

    city Graph::findCity(std::string name){
        city temp;
        for(int i = 0; i < cities.size(); i++){
            if(cities[i].name == name){
                temp = cities[i];
                return temp;
            }
        }
        return temp;
    };

    city *Graph::findCity2(std::string name){
        city *temp = nullptr;
        for(int i = 0; i < cities.size(); i++){
            if(cities[i].name == name){
                temp = &cities[i];
                return temp;
            }
        }
        return temp;
    }

    school Graph::findSchool(std::string name){
        school temp;
        for(int i = 0; i < schools.size(); i++){
            if(schools[i].name == name){
                temp = schools[i];
                return temp;
            }
        }
        return temp;
    };

    school *Graph::findSchool2(std::string name){
        school *temp = nullptr;
        for(int i = 0; i < schools.size(); i++){
            temp = &schools[i];
            return temp;
        }
        return temp;
    }

    sport Graph::findSport(std::string name){
        sport temp;
        for(int i = 0; i < sports.size(); i++){
            if(sports[i].name == name){
                temp = sports[i];
                return temp;
            }
        }
        return temp;
    };

    sport *Graph::findSport2(std::string name){
        sport * temp = nullptr;
        for(int i = 0; i < sports.size(); i++){
            if(sports[i].name == name){
                temp = &sports[i];
                return temp;
            }
        }
        return temp;
    }

    bool Graph::contains(vector<user*> users1, std::string username){
        for(int i = 0; i < users1.size(); i++){
            if(users1[i]->username == username){
                return true;
            }
        }
        return false;
    };

    bool Graph::contains2(vector<adjacent> users1, std::string username){
        for(int i = 0; i < users1.size(); i++){
            if(users1[i].u->username == username){
                return true;
            }
        }
        return false;
    };
