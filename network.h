/* 
network.cpp

Author: Sarah French

Short description of this file: 

This file contains the header for the Network class.

*/


#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <vector>
#include "user.h"

class Network {
 public:
  Network();
  int read_friends(const char *filename);
  int write_friends(const char *filename);
  void add_user(std::string username, int yr, int zipcode);
  int add_connection(std::string name1, std::string name2);
  int remove_connection(std::string name1, std::string name2);
  int get_id(std::string username);
  
    
  //new network2 methods
  std::vector<int> shortest_path(int from, int to);
  std::vector<std::vector<int> > groups();
  std::vector<int> suggest_friends(int who, int& score);
  
  //additional methods
  std::string get_username(int id);
  int get_user_zip(int id);
  int get_user_year(int id);
  std::vector<int>& get_user_friends(int id);
  int get_number_of_users();


 private:
 
 std::vector<User> network_members;

  
};


#endif
