#ifndef DATABASE_H
#define DATABASE_H
#include<iostream>
#include <string>
using namespace std;

enum Type { INT, DOUBLE, STRING, ARRAY };

struct Array {
  int size;
  Type type;
  void *items;
};

struct Entry {
  Type type;
  std::string key;
  void *value;
};

struct Database {
  Entry *entries;
  int size;
};

// 엔트리를 생성한다.
Entry *create(Type type, std::string key, void *value);

// 데이터베이스를 초기화한다.
void init(Database &database){
  database.size=0;
  database.entries=nullptr;
}

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry);

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key);

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key);

// 데이터베이스를 해제한다.
void destroy(Database &database);


int main(){

  Database db;
  init(db);

    while(true){
        string menu;
        cout<<"command (list, add, get, del, exit): ";
        cin>>menu;
        if(menu=="list"){

        }
        else if(menu=="add"){
          string key;
          string type;
          Type t;

          cout<<"key: ";
          cin>>key;

          cout<<"type (int, double, string, array): ";
          cin>>type;

          if(type=="int"){
            t=INT;
          }
          else if(type=="double"){
            t=DOUBLE;
          }
          else if(type=="string"){
            t=STRING;
          }
          else if(type=="array"){
            t=ARRAY;
          }
          else{
            cout<<"invalid command";
          }
          cout<<"value: ";
          if(t==INT){
            int *value=new int;
          }
          else if(t==DOUBLE){
            double *value=new double;
          }
          else if(t==STRING){
            string *value=new string;
          }
          else if(t==ARRAY){
            
          }

        }
        else if(menu=="get"){

        }
        else if(menu=="del"){

        }
        else if(menu=="exit"){
            exit(0);
        }
        else{
            cout<<"invalid command";
        }


    }
}
#endif