#include <iostream>
#include <stdexcept>
#include <string>

#include <db_cxx.h>

void print_db(Db& db)
{
  Dbc *dbcp;
  Dbt key;
  Dbt data;
  db.cursor(NULL, &dbcp, 0);
  while (dbcp->get(&key, &data, DB_NEXT) == 0)
  {
    ::std::cout << "  "
                << static_cast<const char*>(key.get_data()) << " ==> "
                << static_cast<const char*>(data.get_data()) << ::std::endl;
  }
  dbcp->close();
}

int main(int argc, char** argv)
{
  try {
    Db db(nullptr, 0);
    db.open(NULL, "berkeleydb_test.db", NULL, DB_BTREE, DB_CREATE, 0664);

    ::std::cout << "=== before append ===" << ::std::endl;
    print_db(db);
    ::std::cout << "=== before append ===" << ::std::endl;

    for (size_t i = 0; i < 10; ++i) {
      ::std::string str_key = "Key " + ::std::to_string(i);
      ::std::string str_value = "Value " + ::std::to_string(i);
      Dbt key(&str_key[0], static_cast<u_int32_t>(str_key.size()) + 1);
      Dbt data(&str_value[0], static_cast<u_int32_t>(str_value.size()) + 1);
      int ret = db.put(0, &key, &data, DB_NOOVERWRITE);
      if (ret == DB_KEYEXIST) {
        ::std::cout << "Key \"" << str_key << "\" already exists." << ::std::endl;
      }
      else if (0 != ret) {
        ::std::cout << "db.put() returnd " << ret << "." << ::std::endl;
      }
    }

    ::std::cout << "=== after append ===" << ::std::endl;
    print_db(db);
    ::std::cout << "=== after append ===" << ::std::endl;

    db.close(0);
    ::std::cout << "All operations completed." << ::std::endl;
  }
  catch (DbException &dbe) {
    ::std::cout << "DbException: " << dbe.what() << ::std::endl;
    return 1;
  }
  catch (::std::exception &e) {
    ::std::cout << "::std::exception: " << e.what() << ::std::endl;
    return 1;
  }
  catch (...) {
    ::std::cout << "Unknoen exception." << ::std::endl;
    return 1;
  }

  return 0;
}

