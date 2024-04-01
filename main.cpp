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
Entry *create(Type type, std::string key, void *value){
  Entry *newEntry=new Entry;

  newEntry->type=type;
  newEntry->key=key;
  newEntry->value=value;

  return newEntry;
}


// 데이터베이스를 초기화한다.
void init(Database &database){
  database.size=0;
  database.entries=nullptr;
}

// 데이터베이스에 엔트리를 추가한다.
void add(Database &database, Entry *entry){
  Entry *newEntries=new Entry[database.size+1];

  for(int i=0;i<database.size;++i){
    newEntries[i]=database.entries[i];
  }

  newEntries[database.size]=*entry;

  delete[]database.entries;

  database.entries=newEntries;

  ++database.size;
  
}

// 데이터베이스에서 키에 해당하는 엔트리를 찾는다.
Entry *get(Database &database, std::string &key){
  for(int i=0;i<database.size;++i){
    if(database.entries[i].key==key){
      return &database.entries[i];
      
    }
  }
  return nullptr;
}

// 데이터베이스에서 키에 해당하는 엔트리를 제거한다.
void remove(Database &database, std::string &key){
  for(int i=0;i<database.size;++i){
    if(database.entries[i].key==key){
      for(int j=i;j<database.size-1;++j){
        database.entries[j]=database.entries[j+1];
      }
      --database.size;
    }
  }
}

// 데이터베이스를 해제한다.
void destroy(Database &database){
  delete[]database.entries;
  database.size=0;
}


int main(){

  Database db;
  init(db);

    while(true){
        string menu;
        cout<<"command (list, add, get, del, exit): ";
        cin>>menu;
        if(menu=="list"){
          for(int i=0;i<db.size;++i){
            cout<<db.entries[i].key<<": ";
            switch(db.entries[i].type){
              case INT:
              cout<<*((int*)db.entries[i].value);
              break;
              case DOUBLE:
              cout<<(double)(*((double*)db.entries[i].value));
              break;
              case STRING:
              cout<<"\""<<*((string*)db.entries[i].value)<<"\"";
              break;
              
            }
            cout<<endl;
          }
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
            cin>>*value;
            add(db,create(t,key,value));
          }
          else if(t==DOUBLE){
            double *value=new double;
            cin>>*value;
            add(db,create(t,key,value));
          }
          else if(t==STRING){
            string *value=new string;
            cin>>*value;
            add(db,create(t,key,value));
          }
          else if(t==ARRAY){
            Array *array=new Array;
            string arrayType;

            cout<<"type (int, double, string, array): ";
            cin>>arrayType;
            
            cout<<"size: ";
            cin>>array->size;

            if(arrayType=="int"){
              array->type=INT;
              int *items=new int[array->size];

              for(int i=0;i<array->size;i++){
                cout<<"item["<<i<<"]: ";
                cin>>items[i];
                add(db, create(INT, key, &items[i]));
              }
              array->items=items;
              
            }
            else if(arrayType=="double"){
              array->type=DOUBLE;
              double *items=new double[array->size];

              for(int i=0;i<array->size;i++){
                cout<<"item["<<i<<"]: ";
                cin>>items[i];
                add(db, create(DOUBLE, key, &items[i]));
              }
              array->items=items;
            }
            else if(arrayType=="string"){
              array->type=STRING;
              string *items=new string[array->size];

              for(int i=0;i<array->size;i++){
                cout<<"item["<<i<<"]: ";
                cin>>items[i];
                add(db, create(STRING, key, &items[i]));
              }
              array->items=items;
            }
            else if(arrayType=="array"){
              array->type=ARRAY;
              Array **items=new Array*[array->size];

              for(int i=0;i<array->size;i++){
                string arrayType1;
                string items1;
                items[i]=new Array;

                cout<<"item["<<i<<"]: type (int, double, string): ";
                cin>>arrayType1;
                cout<<"size: ";
                cin>>items[i]->size;
                
                if(arrayType1=="int"){
                  items[i]->type=INT;
                  int *items1=new int[items[i]->size];

                  for(int j=0;j<items[i]->size;++j){
                    cout<<"item["<<j<<"]: ";
                    cin>>items1[j];
                    add(db, create(INT, key, &items1[j]));
                  }
                  items[i]->items=items1;
                }
                else if(arrayType1=="double"){
                  items[i]->type=DOUBLE;
                  double *items1=new double[items[i]->size];

                  for(int j=0;j<items[i]->size;++j){
                    cout<<"item["<<j<<"]: ";
                    cin>>items1[j];
                    add(db, create(DOUBLE, key, &items1[j]));
                  }
                  items[i]->items=items1;
                }
                else if(arrayType1=="string"){
                  items[i]->type=STRING;
                  string *items1=new string[items[i]->size];

                  for(int j=0;j<items[i]->size;++j){
                    cout<<"item["<<j<<"]: ";
                    cin>>items1[j];
                    add(db, create(STRING, key, &items1[j]));
                  }
                  items[i]->items=items1;
                }

              }
              array->items=items;
            }
          }

        }
        else if(menu=="get"){
          string key;
          cout<<"key: ";
          cin>>key;
          Entry *entry=get(db, key);
          cout<<entry->key<<": ";
          if(entry){
            switch (entry->type){
            case INT:
            cout<<*((int*)entry->value);
            break;
            case DOUBLE:
            cout<<(double)*((double*)entry->value);
            break;
            case STRING:
            cout<<"\""<<*((string*)entry->value)<<"\"";
            break;
            case ARRAY:
            break;
          }
          cout<<endl;
          }

        }
        else if(menu=="del"){
          string key;
          cout<<"key: ";
          cin>>key;
          remove(db,key);

        }
        else if(menu=="exit"){
            exit(0);
        }
        else{
            cout<<"invalid command"<<endl;
            cout<<endl;
        }


    }
}


#endif