#ifndef CATEGORYMODEL_H
#define CATEGORYMODEL_H

#include "../base/basemodel.h"
#include "../MusicBaseData/Objects/headers/Category.h"

class CategoryModel : public BaseModel
{
public:
  CategoryModel(Poco::SharedPtr<Category> category);

  Poco::SharedPtr<Category> getCategory();
private:
  Poco::SharedPtr<Category> m_category;
};

#endif // CATEGORYMODEL_H
