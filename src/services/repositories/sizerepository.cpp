#include "sizerepository.h"
using Models::Size;
using Services::SizeRepository;

Either<Error, Size> SizeRepository::save(Size entity){
  // check if that size already exist
  QSqlDatabase::database().transaction();

  string sql = queryBuilder.select("id")
      .from(table)
      .where(Expr("id").equals({":id"}))
      .build();
  QSqlQuery query;
  query.prepare(QString::fromStdString(sql));
  query.addBindValue(QVariant::fromValue<int>(entity.getId()));
  query.exec();
  qInfo() << query.lastQuery();

  Either<Error, Size> existsOrError = entityMapper.size(query);

  if(existsOrError.isLeft()){
    QSqlDatabase::database().rollback();
    return existsOrError;
  }

  Size size = existsOrError.right().value();
  if(size.getId() == -1){ // does not exist => should create a new Size
    size.setName(entity.getName());
    size.setExtraPercentageOfMaterial(entity.getExtraPercentageOfMaterial());

    // TODO: insert size

  } else { // exists => should update all the fields

  }

  QSqlDatabase::database().commit();
}
