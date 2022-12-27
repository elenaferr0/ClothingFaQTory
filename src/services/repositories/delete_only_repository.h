

#ifndef DELETE_ONLY_REPOSITORY_H
#define DELETE_ONLY_REPOSITORY_H

#include <string>
#include <QSqlQuery>
#include "../../core/errors/error.h"
#include "../../core/db/querybuilder.h"
#include "repository.h"
#include <optional>

using std::optional;
using std::string;
using Core::Error;
using Core::Db::Expr;
using Core::Db::QueryBuilder;
using Services::Repository;

namespace Services {
    class DeleteOnlyRepository : public virtual Repository {
        private:
            DeleteOnlyRepository(const string& table);

        protected:
            static DeleteOnlyRepository* instance;

            DeleteOnlyRepository(DeleteOnlyRepository&) = delete;

            void operator=(const DeleteOnlyRepository&) = delete;

        public:

            optional<Error> deleteById(int id);

            static DeleteOnlyRepository* getInstance(const string&);
    };


}
#endif //DELETE_ONLY_REPOSITORY_H
