#include <pybind11/pybind11.h>
#include <typeinfo>
#include <iostream>
#include<mysql.h>
using namespace std;
int qstate;
string say_hello(string username,string password){
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "password", "timetable", 3306, NULL, 0);
    if (conn) {
        string query = "SELECT password,type FROM login WHERE userid=\'"+username+"\'";
        const char* q = query.c_str();
            qstate = mysql_query(conn, q);
            if (!qstate) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                if (row == 0000000000000000) {
                    return "-5";
                }
                string s = string(row[0]);
                cout << s;
                int n = s.compare(password);
                if (n == 0)
                    return row[1];
                else
                    return "0"; 
            }
            else
                cout << "query error";
    }
    else {
        cout << "connection unsucessfull";

    }
}
string principal(string username) {
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "password", "timetable", 3306, NULL, 0);
    if (conn) {
        string query = "SELECT name,subject FROM details WHERE userid=\'" + username + "\'";
        cout << query;
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if (!qstate) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            string s;
            s.append(row[0]);
            s.append("-");
            s.append(row[1]);
            return s;
            
        }
        else
            cout << "query error";
    }
    else {
        cout << "connection unsucessfull";

    }
}
void say_hi(){
    printf("Hello diwali\n");
}

PYBIND11_MODULE(pybind11module, module)
{
    module.doc() = "Pybind11Module";
    module.def("say_hello", &say_hello);
    module.def("say_hi", &say_hi);
    module.def("principal", &principal);
}