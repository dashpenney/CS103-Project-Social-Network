/* 
user.h

Author: Sarah French

Short description of this file: 

This file contains the header for the user class.

*/

#ifndef USER_H
#define USER_H
#include <string>
#include <vector>

using std::string;
using std::vector;

class User {
 public:
 
 // constructor
 User(string name,int zip,int year); //cpp
 
 // add_friend
 void add_friend(int friend_id); //cpp
 
 // delete_friend
 void delete_friend(int defriend_id); //cpp
 
 // accessor methods
 
 string username(); //cpp
 
 int user_id(); //cpp
 
 int user_birthyear(); //cpp
 
 int user_zipcode(); //cpp
 
 vector<int>& user_friends(); //cpp
 
 // mutator method
 
 void set_user_id(int id);
 
 // NEW NETWORK 2 VARIABLES (public for ease of access)
 
 int depth;
 int predecessor;
 bool found;
 int shared_friends;

 private:
 
 int user_id_value;
 string full_name;
 int birth_year;
 int zip_code;
 vector<int> friends;

};


#endif
