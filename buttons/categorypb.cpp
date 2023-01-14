#include "categorypb.h"

CategoryPB::CategoryPB(Category &category, BaseFragment *fragment, Poco::SharedPtr <BaseModel> user, QWidget *parent) :
        BasePicturePB(parent), m_category(category), m_fragment{fragment} {
    connect(this, &BasePicturePB::clicked, this, &CategoryPB::onClicked);
    setName(m_category.getName().c_str());
    setPicture(m_category.getCoverArt().c_str());
}

CategoryPB::CategoryPB(Category &category, Poco::SharedPtr <BaseModel> user, QWidget *parent) : BasePicturePB(parent),
                                                                                                m_category(category),
                                                                                                m_user{user} {
    connect(this, &BasePicturePB::clicked, this, &CategoryPB::onClicked);
    setName(m_category.getName().c_str());
    setPicture(m_category.getCoverArt().c_str());
}

CategoryPB::~CategoryPB() {
}

void CategoryPB::onClicked() {
    if (m_user.isNull())
        m_fragment->navigateWithData(screens::CATEGORY_TAG, Poco::makeShared<Category>(m_category));
    else
        m_fragment->navigateWithDataAndUser(screens::CATEGORY_TAG, Poco::makeShared<Category>(m_category), m_user);
}

const Category &CategoryPB::category() {
    return m_category;
}

