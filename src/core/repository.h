#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <list>
#include <optional>
#include <string>

using std::list;
using std::optional;
using std::string;

template <class T, class ID = int>
class Repository
{
  private:
    string table;
  public:
    Repository(string table);
    T save(T entity) = 0;
    list<T> saveAll(list<T> entities) = 0;
    optional<T> findById(ID id);
    list<T> findAllById(list<ID> ids);
    list<T> findAll();
    long count();
    void deleteById(ID id);
    void deleteEntity(T entity);
    void deleteAllById(ID id);
    void deleteAll();
};

template <class T, class ID>
Repository<T, ID>::Repository(string table): table(table){};

template <class T, class ID>
T Repository<T, ID>::save(T entity){

}

#endif // REPOSITORY_H
