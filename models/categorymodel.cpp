#include "categorymodel.h"

CategoryModel::CategoryModel(Poco::SharedPtr<Category> category)
{
  m_category = category;
}

Poco::SharedPtr<Category> CategoryModel::getCategory()
{
  return m_category;
}
