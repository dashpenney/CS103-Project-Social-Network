/* 
network.cpp

Author: Sarah French

Short description of this file: 

This file contains the implementation of all Network functions.

*/

#include <iostream>
#include "user.h"
#include "network.h"
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>
#include <cstdlib>
#include <deque>

using namespace std;

Network::Network(){

}

// read_friends will read the contents of a specifically formatted file into
// the Network object 

int Network::read_friends(const char *filename) {

   ifstream inFile(filename);
   
   if(inFile.fail()){
   
     return -1;
     
   }
   
   // first token in file contains number of users
   
   int num_users;
   
   inFile >> num_users;
      
   int us_id;
   string name;
   int year;
   int zip;
   string friend_line;
   
   
   for(int i=0; i<num_users; i++){
      
      // first token for each user is user ID
      
      inFile >> us_id;
      
      inFile.get(); // skipping past \n char
      inFile.get();
      
      // second token is name
      
      getline(inFile,name);
      
      // third token is year
      
      inFile >> year;
      
      // fourth token is zip
      
      inFile >> zip;
      
      inFile.get(); // skipping \n char
      
      // we now have enough info to declare the new user & set ID
      
      User new_user(name,zip,year);
      
      new_user.set_user_id(us_id);
      
      // parse last line to add friend ID for all numbers
      
      getline(inFile,friend_line);
      
      stringstream ss(friend_line);
      
      int buff;
      
      while(ss >> buff){
         
         new_user.add_friend(buff);
      
      }
      
      // adding new user to array
      
      network_members.push_back(new_user);
   
   }
   
   
   
   inFile.close();
     
   return 0;
   
}

// write_friends will prepare a specifically formatted file containing the
// contents of the Network object

int Network::write_friends(const char *filename){

   ofstream outFile(filename);
   
   int len = network_members.size();
   
   outFile << len << '\n';
   
   // looping through all Users in the Network's vector<User>
   
   for(int i =0; i<len; i++){

      outFile << network_members[i].user_id() << '\n';
      
      outFile << '\t' << network_members[i].username() << '\n';
      
      outFile << '\t' << network_members[i].user_birthyear() << '\n';
      
      outFile << '\t' << network_members[i].user_zipcode() << '\n';
      
      outFile << '\t';
      
      vector<int> u_friends = network_members[i].user_friends();
      
      int flen = u_friends.size();
      
      for(int j=0; j<flen; j++){
      
         outFile << u_friends[j] << " ";
      
      }
      
      outFile << '\n';
   
   }
   
   outFile.close();
      
   return 0;

}

// add_user will add a new member of the Network at the end of the User vector

void Network::add_user(string username, int yr, int zipcode){

   User added_user(username,zipcode,yr);
   
   int last = network_members.size();
   
   added_user.set_user_id(last);
   
   network_members.push_back(added_user);

}

// add_connection will add a connection between 2 existing Network members

int Network::add_connection(string name1, string name2){

   int name1id = get_id(name1);
   int name2id = get_id(name2);
   
   // checking that names provided are Network members
   
   if(name1id ==-1 || name2id==-1){
   
      return -1;
   
   }
   
   network_members[name1id].add_friend(name2id);
   
   network_members[name2id].add_friend(name1id);
   
   return 0;
   
}

// remove_connection will remove a connection between 2 existing Network members

int Network::remove_connection(string name1, string name2){

   int name1id = get_id(name1);
   int name2id = get_id(name2);
   
   // checking that names provided are Network members
   
   if(name1id ==-1 || name2id==-1){
   
      return -1;
   
   }
   
   network_members[name1id].delete_friend(name2id);
   
   network_members[name2id].delete_friend(name1id);
   
   return 0;

}

// get_id will convert a user's name into their user ID

int Network::get_id(string username){

   // initial value of user_id is -1; this will be changed if a match is found
   
   int user_id = -1;

   int len = network_members.size();
   
   // searching all network members for a match to the provided name
   
   for(int i = 0; i<len; i++){
   
      if (network_members[i].username()==username){
      
         user_id = network_members[i].user_id();
      
      }
   
   }
   
   // match ID or -1 for no match will be returned
   
   return user_id;

}

// the rest of the functions are for returning the contents of a User stored in 
// the Network vector

string Network::get_username(int id){

   return network_members[id].username();

}

int Network::get_user_zip(int id){

   return network_members[id].user_zipcode();
  
}

int Network::get_user_year(int id){

   return network_members[id].user_birthyear();
  
}

int Network::get_number_of_users(){

   return network_members.size();

}

vector<int>& Network::get_user_friends(int id){

   return network_members[id].user_friends();

}

// NEW NETWORK2 METHODS

// shortest_path
// a shortest path starting at user "from" and ending at user "to"
// returns empty vector if no path exists

vector<int> Network::shortest_path(int from,int to){

   // setting depth of starting person to 0 & marking as found
   
   network_members[from].depth=0;
   
   network_members[from].found=true;
   
   int current_user = from;

   // initializing search queue for BFS (deque)

   deque<int> search_queue;
   
   // adding starting person to queue
   
   search_queue.push_back(from);
   
   // while queue isn't empty and end person isn't found:
   
   while(search_queue.size()!=0 && network_members[to].found==false){
   
      // storing first user ID
      
      current_user= search_queue[0];
   
      // removing first user from queue
      
      search_queue.pop_front();
      
      // getting neighbors of current user

      vector<int> user_friends = get_user_friends(current_user);
      
      // looping through all neighbors
      
      for(int i=0; i<user_friends.size(); i++){
      
         // only using unfound neighbors
      
         if(network_members[user_friends[i]].found==false){
         
            // adding neighbor to back of queue
            
            search_queue.push_back(user_friends[i]);
            
            // marking neighbor as found
            
            network_members[user_friends[i]].found=true;
            
            // setting neighbor's predecessor
            
            network_members[user_friends[i]].predecessor= current_user;
            
            // setting neighbor's depth as predecessor's depth + 1
            
            int pred_id = network_members[user_friends[i]].predecessor;
            
            network_members[user_friends[i]].depth=
            network_members[pred_id].depth +1;
            
         }
      
      }
   
   }
   
   // traceback
   
   deque<int> shortest_path;
   
   vector<int> short_path;
   
   int users_in_path = network_members[to].depth+1;
   
   if(users_in_path==0){
      return short_path;
   }
   
   int u = to;

      while(u!=from){
      
         shortest_path.push_front(u);
   
         u = network_members[u].predecessor;
      
      }
      
      shortest_path.push_front(from);
      
      
      for (int i=0; i<shortest_path.size(); i++){
      
         short_path.push_back(shortest_path[i]);
      
      }
      
      // resetting all of the users
      
      for(int i =0; i<network_members.size(); i++){
      
         network_members[i].depth=-1;
         network_members[i].predecessor=-1;
         network_members[i].found=false;
      
      }
      
   
   
   return short_path;

}

// groups
// lists disjoint groups in network

vector<vector<int> > Network::groups(){

   // vector of vectors to store vectors of groups

   vector<vector<int> > vector_of_groups;
   
   // another BFS
   // this one will find all possible connections to a user who has
   // not yet been found (cycles through all possible users) and 
   // adds them to the same group
   
   for(int j=0;j<network_members.size();j++){
   
      if(network_members[j].found==false){
      
         deque<int> search_queue; 
         
         search_queue.push_front(j);
         
         vector<int> group;
         
         while(search_queue.size()!=0){
         
            // storing first user ID
         
            int current_user= search_queue[0];

            // removing first user from queue
         
            search_queue.pop_front();
            
            // getting neighbors of current user

            vector<int> user_friends = get_user_friends(current_user);
            
            // looping through all neighbors
            
            for(int i=0; i<user_friends.size(); i++){
            
               // only using unfound neighbors
            
               if(network_members[user_friends[i]].found==false){
               
                  // adding neighbor to back of search queue
                  
                  search_queue.push_back(user_friends[i]);
                  
                  // marking neighbor as found
                  
                  network_members[user_friends[i]].found=true;
                  
                  // adding neighbor to group
                  
                  group.push_back(user_friends[i]);
                  
               }
      
            }
            

         }
         
         // adding group vector to vector of groups
         
         vector_of_groups.push_back(group);
      }
   }
   
   // resetting all of the user variables
      
   for(int i =0; i<network_members.size(); i++){

      network_members[i].found=false;
      
   }
   
   
   return vector_of_groups;
}

// suggest_friends
// returns vector suggested friends with most mutual friends

 vector<int> two_dist;

vector<int> Network::suggest_friends(int who, int& score){

   // BFS again to find and grade depth of all connections to target user

   vector<int> possible_friends;
   
   // initializing BFS stuff
   
   network_members[who].depth=0;
   
   network_members[who].found=true;
   
   int current_user = who;

   deque<int> search_queue;
   
   search_queue.push_back(who);
   
   // while queue isn't empty:
   
   while(search_queue.size()!=0){
   
      // storing first user ID in queue
      
      current_user= search_queue[0];
   
      // removing first user from queue
      
      search_queue.pop_front();
      
      // getting neighbors of current user

      vector<int> user_friends = get_user_friends(current_user);
      
      // looping through all neighbors
      
      for(int i=0; i<user_friends.size(); i++){
      
         // only using unfound neighbors
      
         if(network_members[user_friends[i]].found==false){
         
            // adding neighbor to back of queue
            
            search_queue.push_back(user_friends[i]);
            
            // marking neighbor as found
            
            network_members[user_friends[i]].found=true;
            
            // setting neighbor's predecessor
            
            network_members[user_friends[i]].predecessor= current_user;
            
            // setting neighbor's depth as predecessor's depth + 1
            
            int pred_id = network_members[user_friends[i]].predecessor;
            
            network_members[user_friends[i]].depth=
            network_members[pred_id].depth +1;
            
            // if depth is 2, add user to two_dist vector
            
            if(network_members[user_friends[i]].depth==2){\
            
               two_dist.push_back(user_friends[i]);
            
            }
            
         }
      
      }
   
   }
   
   
   // determining which if any of two_dist members share most friends with target
   
   vector<int> user_friends = get_user_friends(who);
   
   int max_shared_friends = 0;
   
   for(int i=0;i<two_dist.size();i++){
   
      vector<int> two_dist_friends = get_user_friends(two_dist[i]);
   
      for(int j=0; j<user_friends.size();j++){
      
         for(int k=0; k<two_dist_friends.size();k++){
         
            if(user_friends[j]==two_dist_friends[k]){
            
               network_members[two_dist[i]].shared_friends++;
            
            }
         
         }
      
      }
      
      if(network_members[two_dist[i]].shared_friends>max_shared_friends){
      
         max_shared_friends = network_members[two_dist[i]].shared_friends;
      
      }
     
   }
   
   // score value is max_shared_friends 
   
   score = max_shared_friends;
   
   // adding all two_dist members with max score to vector for return

   for(int i=0;i<two_dist.size();i++){
   
      if(network_members[two_dist[i]].shared_friends==max_shared_friends){
      
         possible_friends.push_back(two_dist[i]);
      
      }
   
   }
   
   // resetting user variables
   
   for(int i =0; i<network_members.size(); i++){

     network_members[i].found=false;
     network_members[i].depth=-1;
     network_members[i].predecessor=-1;
      
   }
   
   
   return possible_friends;

}







