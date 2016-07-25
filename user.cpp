/* 
user.cpp

Author: Sarah French

Short description of this file: 

This file contains implementation of all User methods.

*/

#include <iostream>
#include "user.h"
#include <vector>
#include <string>

using namespace std;

// constructor requires user's name, zipcode, & year of birth

User::User(string name,int zip,int year){

   full_name=name;
   zip_code=zip;
   birth_year=year;
   depth=-1;
   predecessor=-1;
   found=false;
   shared_friends=0;

}

// add_friend will add the user ID of a new friend to the end of the
// user's friends vector

void User::add_friend(int friend_id){

   friends.push_back(friend_id);

}

//delete_friend will remove a friend's user ID from the friends vector

void User::delete_friend(int defriend_id){

   int flen = friends.size();
   
   if(flen>0){
   
      for(int i=0;i<flen;i++){
      
         if(friends[i]==defriend_id){
         
            friends.erase(friends.begin()+i);
            
         }
      
      }
   
   }
   
}

// return functions to externally access private variables

string User::username(){

   return full_name;

}

int User::user_id(){
   
   return user_id_value;

}

int User::user_birthyear(){
   
   return birth_year;

}

int User::user_zipcode(){
   
   return zip_code;

}

vector<int>& User::user_friends(){

   return friends;

}

// mutator function to set user's ID

void User::set_user_id(int id){

   user_id_value = id;

}





