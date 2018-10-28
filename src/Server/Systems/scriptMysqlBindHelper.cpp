#include "scriptMysqlBindHelper.hpp"
#include <cstring>

using namespace OpenGMP;

ScriptMysqlBindHelper::~ScriptMysqlBindHelper()
{
    ResetBinds();
}

void ScriptMysqlBindHelper::AddString(std::string &value)
{
    int moreSize = value.size() + 50;
    texts.push_back((char*)malloc(sizeof(char) * moreSize));
    lengths.push_back(new unsigned long());
    *lengths.back() = value.size();
    strcpy(texts.back(), value.c_str());
    binds.push_back(MYSQL_BIND());
    MYSQL_BIND &element = binds.back();
    element.buffer_type = MYSQL_TYPE_VARCHAR;
    element.buffer = texts.back();
    element.buffer_length = moreSize;
    element.is_null = 0;
    element.length = lengths.back();
}

void ScriptMysqlBindHelper::AddInt(int &value)
{
    binds.push_back(MYSQL_BIND());
    MYSQL_BIND &element = binds.back();
    element.buffer_type = MYSQL_TYPE_INT24;
    element.buffer = (char*)&value;
    element.buffer_length = 0;
    element.is_null = 0;
    element.length = 0;
}

void ScriptMysqlBindHelper::AddDouble(double &value)
{
    binds.push_back(MYSQL_BIND());
    MYSQL_BIND &element = binds.back();
    element.buffer_type = MYSQL_TYPE_DOUBLE;
    element.buffer = (char*)&value;
    element.buffer_length = 0;
    element.is_null = 0;
    element.length = 0;
}

void ScriptMysqlBindHelper::ResetBinds()
{
    binds.clear();
    for(char *text : texts)
        free(text);
    for(unsigned long *length : lengths)
        delete length;
    texts.clear();
    lengths.clear();
}

char ScriptMysqlBindHelper::Bind(MYSQL_STMT &stmt)
{
    return mysql_stmt_bind_param(&stmt, (MYSQL_BIND*)binds.data());
}
