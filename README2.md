Part 2 README:

Project Summary: 
This program is a simplified version of a social media app designed to connect high school athletes with other high school athletes, mainly by giving users access to lists of users who do similar sports to them, as well as people who go to the same school and live in the same city. This program has a lot of functions that go towards the functionality of a social media app, such as adding a new user, connecting with other users, and posting to a certain users account. The main Runner.cpp file outputs an extensive menu to choose from in order to use each method for program.

How to Run: 
    Download all the files in the github repository, excluding the 2 ReadMe files. This includes the several .txt files.
    Use the following two commands to run in the Terminal:
        g++ -std=c++11 Graph.cpp LinkedList.cpp FinalAssignmentRunner.cpp -o FinalAssignmentRunner
        ./FinalAssignmentRunner coloradoCities.txt coloradoHighSchools.txt sportsList.txt usersProfiles.txt usersConnections.txt
    The above .txt files will construct a list of all cities in Colorado, all high schools in Colorado, a decent sized list of popular sports, and a pre constructed graph of fake users and their connections, respectively.
    Below I have listed the functionality of each menu item. Note: most menu items require you to insert the username of a user, so have the usersProfiles.txt file handy.
    
    Add a new user
        Creates a new users profile
        
    Find athletes of a certain sport
        Prints out a list of all users who participate in the sport you input
        
    Find athletes of a certain sport who live in a certain city
        Prints out a list of all users who participate in the sport you input and who live in the city you input
        
    Find athletes of a certain sport who go to a certain school currently
        Prints out a list of all users who participate in the sport you input and who currently attend the school you input
        
    Find athletes of a certain sport who went to a certain school in the past
        Prints out a list of all users who participate in the sport you input and who attended the school you input in the past
    
    Update athlete's profile - city
        Allows a user to update the city they live in (they will be taken off of the “current residents” vector in the city they left)
        
    Update athlete's profile - school
        Allows a user to update the school they go to (they will then be placed in the “past students” vector in the school they left)
        
    Update athlete's profile - age
        Allows a user to update their age on their profile
        
    Update athlete's profile - add a sport
        Adds a sports to a user’s profile (only allowed to do this if there are not already 3 sports on a users profile)
        
    Update athlete's profile - remove a sport
        Removes a sport from a user’s profile (only allowed to do that if there will still be one sport on the profile after removed)
        
    See the number of connections a user has
        Prints out the number of connections (sort of like followers or friends) a user has
        
    Search for user with name
        Prints out a user’s profile from a name you input
        
    Create connection between two users
        Adds a connection between two users you input
        
    Delete connection between two users
        Removes a connection between two users you input
        
    Get users connections
        Prints out the connections of a user you input
        
    Get users secondary connections
        Prints out the connections that a user’s friends have but that the user themselves don’t have
        
    Get recommendations for a user
        Prints out a max of 3 potential users that a certain profile should connect with
        
    Add a new post to an athlete's profile
        Publishes a new post to the user’s profile that you input
        
    Delete a post from an athlete's profile
        Deletes a post from a user’s profile when given the day it was posted on.
        
    Edit a post on an athlete's profile
        Allows you to edit posts of the user you input.
        
    Display all the posts on an athlete's profile
        Prints out all the posts of the user you input from most recent to least recent posts
        
    Quit
        End the program


Dependencies: 
    There are no third-party libraries or other dependencies that need to be installed for this program. Everything you need is in this github repository. 

System Requirements: 
    This program was built on a Mac, however it was built in VS Code, which runs on multiple different operating systems, so it should be compatible with all operating systems.

Team Members: 
    I worked individually on this project.

Open Issues/Bugs: 
    The methods that incorporate the linked list for the post do not save the posts to profiles yet, but I believe this has to do with my incorporation of the Linked List class in my Runner and Graph classes.
