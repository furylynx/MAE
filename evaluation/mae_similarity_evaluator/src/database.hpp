//
// Created on 2017-12-01
//

#ifndef MAE_SIMILARITY_EVALUATOR_DATABASE_HPP
#define MAE_SIMILARITY_EVALUATOR_DATABASE_HPP

//custom includes
#include "file.hpp"

//global includes
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

#include <sqlite3.h>

static int create_tables_callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i = 0; i<argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}


void exec(sqlite3* db, std::string sql_statement)
{
    // Execute SQL statement
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql_statement.c_str(), create_tables_callback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        std::stringstream sstr;
        sstr << "SQL error: " << std::string(zErrMsg);

        sqlite3_free(zErrMsg);

        throw std::runtime_error (sstr.str());
    }
    else
    {
        fprintf(stdout, "Table created successfully\n");
    }

}

sqlite3* open_database(std::string database_file)
{
    //Open database
    sqlite3 *db;
    int rc = sqlite3_open(database_file.c_str(), &db);

    if(rc)
    {
        std::stringstream sstr;
        sstr << "Can't open database: " << sqlite3_errmsg(db);
        throw std::runtime_error (sstr.str());
    }
    else
    {
        std::cout << "Opened database successfully" << std::endl;
    }

    return db;
}

void create_tables_if_not_exist(sqlite3* db)
{
    //Create SQL statement
    std::string sql_create_table_data = read_file("sqlite_data.sql");
    std::string sql_create_table_sequences = read_file("sqlite_sequences.sql");
    std::string sql_create_table_comparators = read_file("sqlite_comparators.sql");

    exec(db, sql_create_table_data);
    exec(db, sql_create_table_sequences);
    exec(db, sql_create_table_comparators);
}

int select_comparator_id(sqlite3* db, std::string comparator_name)
{
    std::stringstream sstr_sel;
    sstr_sel << "SELECT id FROM comparators WHERE name LIKE ?;";

    sqlite3_stmt *sel_statement;

    int result = -1;

    if ( sqlite3_prepare(db, sstr_sel.str().c_str(), -1, &sel_statement, 0 ) == SQLITE_OK )
    {
        sqlite3_bind_text(sel_statement, 1, comparator_name.c_str(), -1, SQLITE_STATIC);

        int ctotal = sqlite3_column_count(sel_statement);
        int res = SQLITE_OK;

        while ( res != SQLITE_DONE && res != SQLITE_ERROR )
        {
            res = sqlite3_step(sel_statement);

            if ( res == SQLITE_ROW )
            {
                for ( int i = 0; i < ctotal; i++ )
                {
                    result = sqlite3_column_int(sel_statement, i);
                }
            }
        }
    }
    else
    {
        throw std::runtime_error("Could not prepare statement.");
    }

    sqlite3_finalize(sel_statement);

    return result;
}

std::unordered_map<std::string, int> prepare_comparators(sqlite3* db, std::vector<std::string> comparator_names, std::vector<std::string> comparator_descriptions)
{
    if (comparator_names.size() != comparator_descriptions.size())
    {
        throw std::invalid_argument("Size of names is not equal to the size of descriptions.");
    }

    std::unordered_map<std::string, int> result;

    for (std::size_t i = 0; i < comparator_names.size(); i++)
    {
        std::stringstream sstr;
        sstr << "INSERT INTO comparators(name,description) SELECT ?,? WHERE NOT EXISTS(SELECT 1 FROM comparators WHERE name = ?);";

        sqlite3_stmt *statement;
        sqlite3_prepare_v2(db, sstr.str().c_str(), strlen(sstr.str().c_str()), &statement, NULL);

        int rc = sqlite3_step(statement);

        if(sqlite3_prepare_v2(db, sstr.str().c_str(), strlen(sstr.str().c_str()), &statement, NULL)==SQLITE_OK)
        {
            sqlite3_bind_text(statement, 1, comparator_names.at(i).c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 2, comparator_descriptions.at(i).c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 3, comparator_names.at(i).c_str(), -1, SQLITE_STATIC);

            sqlite3_step(statement);
            sqlite3_finalize(statement);
        }
        else
        {
            std::stringstream sstr;
            sstr << "Error: " << sqlite3_errmsg(db);
            throw std::runtime_error (sstr.str());
        }

        result[comparator_names.at(i)] = select_comparator_id(db, comparator_names.at(i));
    }

    return result;
}

int select_sequence_id(sqlite3* db, std::string path)
{
    std::stringstream sstr_sel;
    sstr_sel << "SELECT id FROM sequences WHERE path LIKE ?;";

    sqlite3_stmt *sel_statement;

    int result = -1;

    if ( sqlite3_prepare(db, sstr_sel.str().c_str(), -1, &sel_statement, 0 ) == SQLITE_OK )
    {
        sqlite3_bind_text(sel_statement, 1, path.c_str(), -1, SQLITE_STATIC);

        int ctotal = sqlite3_column_count(sel_statement);
        int res = SQLITE_OK;

        while ( res != SQLITE_DONE && res != SQLITE_ERROR )
        {
            res = sqlite3_step(sel_statement);

            if ( res == SQLITE_ROW )
            {
                for ( int i = 0; i < ctotal; i++ )
                {
                    result = sqlite3_column_int(sel_statement, i);
                }
            }
        }
    }
    else
    {
        throw std::runtime_error("Could not prepare statement.");
    }

    sqlite3_finalize(sel_statement);

    return result;
}

int insert_sequence(sqlite3* db, std::string path, std::string filename, std::string directory, std::string name,std::string score, int defined)
{

    std::stringstream sstr;
    sstr << "INSERT INTO sequences(path,filename,directory,name,score,defined) SELECT ?,?,?,?,?,? WHERE NOT EXISTS(SELECT 1 FROM sequences WHERE path = ?);";

    sqlite3_stmt *statement;
    sqlite3_prepare_v2(db, sstr.str().c_str(), strlen(sstr.str().c_str()), &statement, NULL);

    int rc = sqlite3_step(statement);

    if(sqlite3_prepare_v2(db, sstr.str().c_str(), strlen(sstr.str().c_str()), &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_text(statement, 1, path.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 2, filename.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 3, directory.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(statement, 4, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_blob(statement, 5, score.data(), score.size(), SQLITE_TRANSIENT);
        sqlite3_bind_int(statement, 6, defined);
        sqlite3_bind_text(statement, 7, path.c_str(), -1, SQLITE_STATIC);

        sqlite3_step(statement);
        sqlite3_finalize(statement);
    }
    else
    {
        std::stringstream sstr;
        sstr << "Error: " << sqlite3_errmsg(db);
        throw std::runtime_error (sstr.str());
    }

    return select_sequence_id(db, path);
}

void insert_data(sqlite3* db, int comparator_id, int is_compare_target_sequence, int compare_sequence_id, int actual_sequence_id, double similarity)
{

    std::stringstream sstr;
    sstr << "INSERT INTO data(comparator_id,is_compare_target_sequence,compare_sequence_id,actual_sequence_id,similarity) SELECT ?,?,?,?,? WHERE NOT EXISTS(SELECT 1 FROM sequences WHERE comparator_id = ? AND compare_sequence_id = ? AND actual_sequence_id = ?);";

    sqlite3_stmt *statement;
    sqlite3_prepare_v2(db, sstr.str().c_str(), strlen(sstr.str().c_str()), &statement, NULL);

    int rc = sqlite3_step(statement);

    if(sqlite3_prepare_v2(db, sstr.str().c_str(), strlen(sstr.str().c_str()), &statement, NULL)==SQLITE_OK)
    {
        sqlite3_bind_int(statement, 1, comparator_id);
        sqlite3_bind_int(statement, 2, is_compare_target_sequence);
        sqlite3_bind_int(statement, 3, compare_sequence_id);
        sqlite3_bind_int(statement, 4, actual_sequence_id);
        sqlite3_bind_double(statement, 5, similarity);
        sqlite3_bind_int(statement, 6, comparator_id);
        sqlite3_bind_int(statement, 7, compare_sequence_id);
        sqlite3_bind_int(statement, 8, actual_sequence_id);

        sqlite3_step(statement);
        sqlite3_finalize(statement);
    }
    else
    {
        std::stringstream sstr;
        sstr << "Error: " << sqlite3_errmsg(db);
        throw std::runtime_error (sstr.str());
    }
}


#endif //MAE_SIMILARITY_EVALUATOR_DATABASE_HPP
