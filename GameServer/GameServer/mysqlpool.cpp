﻿#include "mysqlpool.h"

MysqlPool* MysqlPool::mysqlpool_object = NULL;
std::mutex MysqlPool::objectlock;
std::mutex MysqlPool::poollock;

MysqlPool::MysqlPool() {}

void MysqlPool::setParameter( const char*   mysqlhost,
                              const char*   mysqluser,
                              const char*   mysqlpwd,
                              const char*   databasename,
                              unsigned int  port,
                              const char*   socket,
                              unsigned long client_flag,
                              unsigned int  max_connect ) {
    _mysqlhost    = mysqlhost;
    _mysqluser    = mysqluser;
    _mysqlpwd     = mysqlpwd;
    _databasename = databasename;
    _port         = port;
    _socket       = socket;
    _client_flag  = client_flag;
    MAX_CONNECT   = max_connect;
}

MysqlPool* MysqlPool::getMysqlPoolObject() {
    if (mysqlpool_object == NULL) {
        objectlock.lock();
        if (mysqlpool_object == NULL) {
            mysqlpool_object = new MysqlPool();
        }
        objectlock.unlock();
    }
    return mysqlpool_object;
}

MYSQL* MysqlPool::createOneConnect() {
    MYSQL* conn = NULL;
    conn = mysql_init(conn);
    if (conn != NULL) {
        if (mysql_real_connect(conn,
                               _mysqlhost,
                               _mysqluser,
                               _mysqlpwd,
                               _databasename,
                               _port,
                               _socket,
                               _client_flag)) {
            connect_count++;
            return conn;
        } else {
            std::cout << mysql_error(conn) << std::endl;
            return NULL;
        }
    } else {
        std::cerr << "init failed" << std::endl;
        return NULL;
    }
}

bool MysqlPool::isEmpty() {
    return mysqlpool.empty();
}

MYSQL* MysqlPool::poolFront() {
    return mysqlpool.front();
}

unsigned int MysqlPool::poolSize() {
    return mysqlpool.size();
}

void MysqlPool::poolPop() {
    mysqlpool.pop();
}

MYSQL* MysqlPool::getOneConnect() {
    poollock.lock();
    MYSQL *conn = NULL;
    if (!isEmpty()) {
        while (!isEmpty() && mysql_ping(poolFront())) {
            mysql_close(poolFront());
            poolPop();
            connect_count--;
        }
        if (!isEmpty()) {
            conn = poolFront();
            poolPop();
        } else {
            if (connect_count < MAX_CONNECT)
                conn = createOneConnect();
            else
                std::cerr << "the number of mysql connections is too much!" << std::endl;
        }
    } else {
        if (connect_count < MAX_CONNECT)
            conn = createOneConnect();
        else
            std::cerr << "the number of mysql connections is too much!" << std::endl;
    }
    poollock.unlock();
    return conn;
}

void MysqlPool::close(MYSQL* conn) {
    if (conn != NULL) {
        poollock.lock();
        mysqlpool.push(conn);
        poollock.unlock();
    }
}

std::map<const std::string,std::vector<const char*> >  MysqlPool::executeSql(const char* sql) {
    MYSQL* conn = getOneConnect();
    std::map<const std::string,std::vector<const char*> > results;
	std::list<std::vector<const char*>*> r_list;

    if (conn) {
        if (mysql_query(conn,sql) == 0) {
            MYSQL_RES *res = mysql_store_result(conn);
            if (res) {
                MYSQL_FIELD *field;
                while ((field = mysql_fetch_field(res))) {
                    results.insert(make_pair(field->name,std::vector<const char*>()));
					r_list.push_back(&results[field->name]);
                }
				MYSQL_ROW row;
                while ((row = mysql_fetch_row(res))) {
                    unsigned int i = 0;
					for (auto it = r_list.begin(); it != r_list.end(); ++it) {
						(*it)->push_back(row[i++]);
                    }
                }
                mysql_free_result(res);
            } else {
                if (mysql_field_count(conn) != 0)
                    std::cerr << mysql_error(conn) << std::endl;
            }
        } else {
            std::cerr << mysql_error(conn) <<std::endl;
        }
        close(conn);
    } else {
        std::cerr << mysql_error(conn) << std::endl;
    }
    return results;
}



MysqlPool::~MysqlPool() {
    while (poolSize() != 0) {
        mysql_close(poolFront());
        poolPop();
        connect_count--;
    }
}