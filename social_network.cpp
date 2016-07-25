/* 
social_network.cpp

Author: Sarah French

Short description of this file: 

This file contains a Network object and accepts user commands to interact with 
that object. Command line requires filename of properly formatted Network read 
file. 

Acceptable Commands: 

> 1 First Name 1900 90007 
adds a new User w/ specified name, birth year, zip code to the Network

> 2 First Name Second Name 
adds a connection between the 2 users named

> 3 First Name Second Name 
removes a connection between the 2 users named

> 4 
prints all Network member info in table

> 5 First Name
prints all the named user's connections' info in a table

> 6 filename.txt
outputs all Network information into a file

NEW NETWORK 2 OPTIONS

> 7 First Name Second Name
prints distance between users & shortest path of relational connections

> 8
prints disjoint user sets within network

> 9 First Name
suggests friends for user with score based on number of common friends
possible friends will be 2nd degree connections with at least 1 common friend
ties in mutual friends will result in multiple friend suggestions 

*/

#include "network.h"
#include "user.h"
#include <cstring>
#include <iomanip>
#include <fstream>
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
   // creating Network object called social_network
   
   Network social_network;

   // reading in data from file provided in command line to the Network
   
   const char *filename = argv[1];
   
   int check = social_network.read_friends(filename);
   
   if(check==-1){
   
      cout << "Invalid file name." << endl;
      return 0;
   
   }
   
   // user can input commands until an invalid command is entered
   // valid commands are integers from 1 to 6
   
   int option=1;
   
   while (option>0 && option<10){
   
      cin >> option;
      
      // COMMAND 1
      // this command will add a new user to the Network with the specified
      // input parameters (name, year of birth, zip code)
      
      if (option==1){
      
         // note: names are provided as first and last name separated by
         // a space, requiring concatenation after reading from cin
         
         string name1, name2;
         int year;
         int zip;
      
         cin >> name1 >> name2;  
         cin >>year; 
         cin >> zip;
         
         string name = name1 + " " + name2;
         
         social_network.add_user(name, year, zip);
      
      }
      
      // COMMAND 2
      // this command will add a connection between 2 users, identified
      // by their names; an user name not in Network will result in error message
      
      else if (option==2){
      
         string name1a, name1b;
         string name2a, name2b;
         
         cin >> name1a >> name1b >> name2a >> name2b;
         
         string name1 = name1a +" " + name1b;
         string name2 = name2a +" " + name2b;
         
         int success = social_network.add_connection(name1, name2);
         
         if(success == -1){
         
            cout << "Error: connection could not be made." << endl;
         
         }
      
      }
      
      // COMMAND 3
      // this command will remove a connection between 2 users, identified
      // by thier names; a problem with removing the connection will result
      // in an error message
      
      else if (option==3){
      
         string name3a, name3b;
         string name4a, name4b;
         
         cin >> name3a >> name3b >> name4a >> name4b;
         
         string name3 = name3a + " " + name3b;
         
         string name4 = name4a + " " + name4b;
         
         int desuccess= social_network.remove_connection(name3, name4);
         
         if (desuccess ==-1){
         
            cout << "Error: connection could not be deleted." << endl;
         
         }
      
      }
      
      //COMMAND 4
      // this command will output the contents of the Network in a neatly
      // formatted table
      
      else if (option==4){
      
         // printing table header
         
         cout << setw(5) << "ID";
         cout << setw(20) << "Name";
         cout << setw(5) << "Year";
         cout << setw(10) << "Zip";
         
         cout << endl;
         
         for (int i =0; i<=40; i++){
         
            cout <<"=";
         
         } 
         
         cout << endl;
         
         // looping through each user ID in database and extracting/printing
         // user info
                  
         int user_num = social_network.get_number_of_users();
         
         for (int i =0; i<user_num; i++){
         
            int id = i;
         
            cout << setw(5) << id << ".";
            
            string name = social_network.get_username(i);
            
            cout << setw(20) << name;
            
            int yr = social_network.get_user_year(i);
            
            cout << setw(5) << yr;
            
            int zp = social_network.get_user_zip(i);
            
            cout << setw(10) << zp;
            
            cout << endl;
         
         }
         
         
      }
      
      // COMMAND 5
      // this command will print a neatly formatted table of a valid user's
      // connections in the Network; invalid user will result in error message
      
      else if(option==5){
      
         string user, name;
         
         cin >> user >> name;
         
         string usn = user+" "+name;
         
         int userid = social_network.get_id(usn);
         
         if(userid!=-1){
            
            // printing table header
            
            cout << setw(5) << "ID";
            cout << setw(20) << "Name";
            cout << setw(5) << "Year";
            cout << setw(10) << "Zip";
            
            cout << endl;
            
            for (int i =0; i<=40; i++){
            
               cout <<"=";
            
            } 
            
            cout << endl;
            
            // extracting user's friends vector
            
            vector<int> u_friends = social_network.get_user_friends(userid);
            
            // looping through each user ID in user's friend vector, extracting
            // info, and printing
            
            int flen = u_friends.size();
            
            for (int i=0; i<flen; i++){
            
               int friend_id = u_friends[i];
               
               cout << setw(5) << friend_id << ".";
               
               string friend_name = social_network.get_username(friend_id);
               
               cout << setw(20) << friend_name;
               
               int yr = social_network.get_user_year(friend_id);
               
               cout << setw(5) << yr;
               
               int zp = social_network.get_user_zip(friend_id);
               
               cout << setw(10) << zp;
               
               cout << endl;
            
            }
            
        }
        
        // user name not matching any in Network results in error message
        
        else{
        
        cout << "User does not exist." << endl;
        
        }
         
      }
      
      // COMMAND 6
      // this command will write the contents of the Network into a file,
      // the name of which is input
      
      else if(option==6){
      
          
         char file[80];
         cin >> file;
         
         const char *file_name = file;
         
         int check2 = social_network.write_friends(file_name);
         
         if(check2==-1){
         
            cout << "Failed to write to filename provided." << endl;
         
         }
      
      }
      
      // COMMAND 7
      // prints distance between users & shortest path of relational 
      // connections

      else if(option==7){
      
         string name1a, name1b;
         string name2a, name2b;
         
         cin >> name1a >> name1b >> name2a >> name2b;
         
         string name1 = name1a +" " + name1b;
         string name2 = name2a +" " + name2b;
         
         int from = social_network.get_id(name1);
         int to = social_network.get_id(name2);
         
         // vector friend_path will store function return
         
         vector<int> friend_path = social_network.shortest_path(from,to);
         
         // friend paths of length 0 indicate no path between two users
         
         if(friend_path.size()==0){
         
            cout << "None" << endl;
         
         }
         
         // printing friend path
         
         else{
            
            for (int i=0; i<friend_path.size()-1; i++){
            
            cout << social_network.get_username(friend_path[i]) << " -> ";
            
            }
            
            cout << name2 << endl;
         
         }
      
      }
      
      // COMMAND 8
      // prints disjoint user groups within network
      
      else if(option==8){
      
         // vector of vectors to store function output
      
         vector<vector<int> > groups = social_network.groups();
         
         // looping through all groups, then all members of group for printing
         
         for(int i=0; i<groups.size(); i++){
         
            cout << "Set " << i+1 << "=> ";
            
            for(int j=0; j<groups[i].size()-1; j++){
            
               cout << social_network.get_username(groups[i][j]) << ", ";
            
            }
            
            cout << social_network.get_username(groups[i].back()) << endl;
         
         }
         
      }
      
      // COMMAND 9
      // prints recommended friends
      
      else if(option==9){
      
         // same name input procedure as used previously
      
         string name1, name2;
      
         cin >> name1 >> name2;  

         string name = name1 + " " + name2;
         
         int who = social_network.get_id(name);
      
         int score;
         
         // calling function
      
         vector<int> rec_friends = social_network.suggest_friends(who, score);
         
         cout << "The suggested friends is/are: " << endl;
         
         // looping through function output to print
         
         for(int i=0; i<rec_friends.size(); i++){
         
            cout << social_network.get_username(rec_friends[i]) << "    ";
            cout << "Score: " << score << endl;
         
         }

      }
   
  }
   
  return 0;
}
