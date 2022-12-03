#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <list>
#include <optional>
#include <string>
#include "src/core/orm/querybuilder.h"

using std::list;
using std::optional;
using std::string;
using std::to_string;
using Core::Orm::QueryBuilder;

namespace Core::Orm {
    template<class T>
    class Repository {
    private:
        string table;
        QueryBuilder queryBuilder;
    public:
        Repository(string table);

        T save(T entity) = 0;

        list <T> saveAll(list <T> entities) = 0;

        optional <T> findById(int id);

        list <T> findAllById(list<int>& ids);

        list <T> findAll();

        long count();

        void deleteById(int id);

        void deleteT(T entity) = 0;

        void deleteAllById(list<int>& id);

        void deleteAll();
    };

    template<class T>
    Repository<T>::Repository(string table): table(table) {};

    template<class T>
    optional <T> Repository<T>::findById(int id) {
        string query = queryBuilder.select()
                .from(table)
                .where(Expr("id").equals({":id"}))
                .bindParameter(":id", to_string(id))
                .build();
    }

    template<class T>
    list <T> Repository<T>::findAllById(list<int>& ids) {
        string query = queryBuilder.select()
                .from(table)
                .where(Expr("id").in(ids))
                .build();
    }

    template<class T>
    list <T> Repository<T>::findAll() {
        string query = queryBuilder
                .select()
                .from(table)
                .build();
    }

    template<class T>
    long Repository<T>::count(string field) {
        string query = queryBuilder
                .count(field)
                .from(table)
                .build();
    }

    template<class T>
    void Repository<T>::deleteById(int id) {
        string query = queryBuilder
                .deleteT()
                .where(Expr("id").eq(to_string(id)))
                .build();
    }

    template<class T>
    void Repository<T>::deleteAllById(list<int>& ids) {
        string query = queryBuilder
                .deleteT()
                .from(table)
                .where(Expr("id").in(ids))
                .build();
    }

    template<class T>
    void Repository<T>::deleteAll() {
        string query = queryBuilder
                .deleteT()
                .from(table)
                .build();
    }
}

#endif // REPOSITORY_H
