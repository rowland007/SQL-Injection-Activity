// SQLInjection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <locale>
#include <tuple>
#include <vector>

#include "sqlite3.h"

// DO NOT CHANGE
typedef std::tuple<std::string, std::string, std::string> user_record;
const std::string str_where = " where ";

// DO NOT CHANGE
static int callback(void* possible_vector, int argc, char** argv, char** azColName)
{
  if (possible_vector == NULL)
  { // no vector passed in, so just display the results
    for (int i = 0; i < argc; i++) 
    {
      std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
  }
  else
  {
    std::vector< user_record >* rows =
      static_cast<std::vector< user_record > *>(possible_vector);

    rows->push_back(std::make_tuple(argv[0], argv[1], argv[2]));
  }
  return 0;
}

// DO NOT CHANGE
bool initialize_database(sqlite3* db)
{
  char* error_message = NULL;
  std::string sql = "CREATE TABLE USERS(" \
    "ID INT PRIMARY KEY     NOT NULL," \
    "NAME           TEXT    NOT NULL," \
    "PASSWORD       TEXT    NOT NULL);";

  int result = sqlite3_exec(db, sql.c_str(), callback, NULL, &error_message);
  if (result != SQLITE_OK)
  {
    std::cout << "Failed to create USERS table. ERROR = " << error_message << std::endl;
    sqlite3_free(error_message);
    return false;
  }
  std::cout << "USERS table created." << std::endl;

  // insert some dummy data
  sql = "INSERT INTO USERS (ID, NAME, PASSWORD)" \
    "VALUES (1, 'Fred', 'Flinstone');" \
    "INSERT INTO USERS (ID, NAME, PASSWORD)" \
    "VALUES (2, 'Barney', 'Rubble');" \
    "INSERT INTO USERS (ID, NAME, PASSWORD)" \
    "VALUES (3, 'Wilma', 'Flinstone');" \
    "INSERT INTO USERS (ID, NAME, PASSWORD)" \
    "VALUES (4, 'Betty', 'Rubble');";

  result = sqlite3_exec(db, sql.c_str(), callback, NULL, &error_message);
  if (result != SQLITE_OK)
  {
    std::cout << "Data failed to insert to USERS table. ERROR = " << error_message << std::endl;
    sqlite3_free(error_message);
    return false;
  }

  return true;
}

bool run_query(sqlite3* db, const std::string& sql, std::vector< user_record >& records)
{
  // TODO: Fix this method to fail and display an error if there is a suspected SQL Injection
  //  NOTE: You cannot just flag 1=1 as an error, since 2=2 will work just as well. You need
  //  something more generic

  // clear any prior results
  records.clear();

  char* error_message;
  if(sqlite3_exec(db, sql.c_str(), callback, &records, &error_message) != SQLITE_OK)
  {
    std::cout << "Data failed to be queried from USERS table. ERROR = " << error_message << std::endl;
    sqlite3_free(error_message);
    return false;
  }

  return true;
}

// DO NOT CHANGE
bool run_query_injection(sqlite3* db, const std::string& sql, std::vector< user_record >& records)
{
  std::string injectedSQL(sql);
  std::string localCopy(sql);

  // we work on the local copy because of the const
  std::transform(localCopy.begin(), localCopy.end(), localCopy.begin(), ::tolower);
  if(localCopy.find_last_of(str_where) >= 0)
  { // this sql has a where clause
    if(localCopy.back() == ';')
    { // smart SQL developer terminated with a semicolon - we can fix that!
      injectedSQL.pop_back();
    }

    switch (rand() % 4)
    {
    case 1:
      injectedSQL.append(" or 2=2;");
      break;
    case 2:
      injectedSQL.append(" or 'hi'='hi';");
      break;
    case 3:
      injectedSQL.append(" or 'hack'='hack';");
      break;
    case 0:
    default:
      injectedSQL.append(" or 1=1;");
      break;
    }
  }
  
  return run_query(db, injectedSQL, records);
}


// DO NOT CHANGE
void dump_results(const std::string& sql, const std::vector< user_record >& records)
{
  std::cout << std::endl << "SQL: " << sql << " ==> " << records.size() << " records found." << std::endl;

  for (auto record : records)
  {
    std::cout << "User: " << std::get<1>(record) << " [UID=" << std::get<0>(record) << " PWD=" << std::get<2>(record) << "]" << std::endl;
  }
}

// DO NOT CHANGE
void run_queries(sqlite3* db)
{
  char* error_message = NULL;

  std::vector< user_record > records;

  // query all
  std::string sql = "SELECT * from USERS";
  if (!run_query(db, sql, records)) return;
  dump_results(sql, records);

  //  query 1
  sql = "SELECT ID, NAME, PASSWORD FROM USERS WHERE NAME='Fred'";
  if (!run_query(db, sql, records)) return;
  dump_results(sql, records);

  //  run query 1 with injection 5 times
  for (auto i = 0; i < 5; ++i)
  {
    if (!run_query_injection(db, sql, records)) continue;
    dump_results(sql, records);
  }

}

// You can change main by adding stuff to it, but all of the existing code must remain, and be in the
// in the order called, and with none of this existing code placed into conditional statements
int main()
{
  // initialize random seed:
  srand(time(nullptr));

  int return_code = 0;
  std::cout << "SQL Injection Example" << std::endl;

  // the database handle
  sqlite3* db = NULL;
  char* error_message = NULL;

  // open the database connection
  int result = sqlite3_open(":memory:", &db);

  if(result != SQLITE_OK)
  {
    std::cout << "Failed to connect to the database and terminating. ERROR=" << sqlite3_errmsg(db) << std::endl;
    return -1;
  }

  std::cout << "Connected to the database." << std::endl;

  // initialize our database
  if(!initialize_database(db))
  {
    std::cout << "Database Initialization Failed. Terminating." << std::endl;
    return_code = -1;
  }
  else
  {
    run_queries(db);
  }

  // close the connection if opened
  if(db != NULL)
  {
    sqlite3_close(db);
  }

  return return_code;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
