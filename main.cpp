#ifndef DATABASE_H
#define DATABASE_H
#include<iostream>
#include <string>
using namespace std;

enum Type { INT, DOUBLE, STRING, ARRAY };

struct Array {
  int size;
  int size2;
  Type type;
  void *items;
  Type element;
  Type element2;
};

struct Entry {
  int size;
  int size2;
  Type type;
  std::string key;
  void *value;
  Type element;
  Type element2;
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

Entry *arraycreate(Type type, std::string key, void *value, Type element,int size){
  Entry *newEntry=new Entry;

  newEntry->type=type;
  newEntry->key=key;
  newEntry->value=value;
  newEntry->element=element;
  newEntry->size=size;

  return newEntry;
}

Entry *doublearraycreate(Type type, std::string key, void *value, Type element,Type element2,int size,int size2){
  Entry *newEntry=new Entry;

  newEntry->type=type;
  newEntry->key=key;
  newEntry->value=value;
  newEntry->element=element;
  newEntry->element2=element2;
  newEntry->size=size;
  newEntry->size2=size2;


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
          for(int i=0;i<db.size;i++){
            cout<<db.entries[i].key<<": ";
            switch(db.entries[i].type){

              case INT:
              cout<<*((int*)db.entries[i].value);
              cout<<endl;
              break;

              case DOUBLE:
              cout<<*((double*)db.entries[i].value);
              cout<<endl;
              break;

              case STRING:
              cout<<"\""<<*((string*)db.entries[i].value)<<"\"";
              cout<<endl;
              break;

              case ARRAY:{
              
              cout<<"[";
              
              for (int j = 0; j < db.entries[i].size; j++) {
                   switch (db.entries[i].element) {
                    case INT:{
                      cout << *((int*)db.entries[i].value+j);
                      break;
                    }
                    case DOUBLE:{
                      cout << *((double*)db.entries[i].value+ j);
                      break;
                    }
                    case STRING:{
                      cout << *((string*)db.entries[i].value+ j);
                      break;
                    }
                    case ARRAY:{
                      cout<<"[";
                      for(int k=0;k<db.entries[i].size2;k++){
                        
                        switch (db.entries[i].element2){
                          case INT:{
                            cout << *((int*)db.entries[i].value+k);
                            break;
                          }
                          case DOUBLE:{
                           cout << *((double*)db.entries[i].value+ k);
                            break;
                          }
                          case STRING:{
                            cout << *((string*)db.entries[i].value+ k);
                            break;
                         }
                        }
                        if (k != db.entries[i].size2-1) {
                          cout << ", ";
                        }
                      }
                      if(j!=db.entries[i].size-1){
                      i+=db.entries[i].size2;
                      }
                      else{
                        i+=db.entries[i].size2-1;
                      }
                      cout<<"]";
                      break;
                    }
                    }
                if (j != db.entries[i].size-1) {
                 cout << ", ";
               }
               }
               if(db.entries[i].element!=ARRAY){
               i+=db.entries[i].size-1;
               }
               cout<<"]"; 
               break;
          }
          
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
            array->type=ARRAY;
            string arrayType;

            cout<<"type (int, double, string, array): ";
            cin>>arrayType;
            
            cout<<"size: ";
            cin>>array->size;

            if(arrayType=="int"){
              array->element=INT;
              int *items=new int[array->size];

              for(int i=0;i<array->size;i++){
                cout<<"item["<<i<<"]: ";
                cin>>items[i];
                add(db, arraycreate(ARRAY, key, &items[i],INT,array->size));
              }
              array->items=items;
              
            }
            else if(arrayType=="double"){
              array->element=DOUBLE;
              double *items=new double[array->size];

              for(int i=0;i<array->size;i++){
                cout<<"item["<<i<<"]: ";
                cin>>items[i];
                add(db, arraycreate(ARRAY, key, &items[i],DOUBLE,array->size));
              }
              array->items=items;
              
            }
            else if(arrayType=="string"){
              array->element=STRING;
              string *items=new string[array->size];

              for(int i=0;i<array->size;i++){
                cout<<"item["<<i<<"]: ";
                cin>>items[i];
                add(db, arraycreate(ARRAY, key, &items[i],STRING,array->size));
              }
              array->items=items;
              
            }
            else if(arrayType=="array"){
              array->element;

              for(int i=0;i<array->size;i++){
                string arrayType1;
                string items1;
                int size2;
                

                cout<<"item["<<i<<"]: type (int, double, string): ";
                cin>>arrayType1;
                cout<<"size: ";
                cin>>size2;
                
                if(arrayType1=="int"){
                  array->element2=INT;
                  int *items1=new int[size2];

                  for(int j=0;j<size2;j++){
                    cout<<"item["<<j<<"]: ";
                    cin>>items1[j];
                    add(db, doublearraycreate(ARRAY, key, &items1[j],ARRAY,INT,array->size,size2));
                  }
                  
                }
                else if(arrayType1=="double"){
                  
                  array->element2=DOUBLE;
                  double *items1=new double[size2];

                  for(int j=0;j<size2;j++){
                    cout<<"item["<<j<<"]: ";
                    cin>>items1[j];
                    add(db, doublearraycreate(ARRAY, key, &items1[j],ARRAY,DOUBLE,array->size,size2));
                  }
                }
                else if(arrayType1=="string"){
                  
                  array->element2=STRING;
                  string *items1=new string[size2];

                  for(int j=0;j<size2;j++){
                    cout<<"item["<<j<<"]: ";
                    cin>>items1[j];
                    add(db, doublearraycreate(ARRAY, key, &items1[j],ARRAY,STRING,array->size,size2));
                  }
                }

              }
            
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