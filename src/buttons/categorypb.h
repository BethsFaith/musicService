#ifndef PICTUREBP_H
#define PICTUREBP_H

#include <QWidget>
#include <QPushButton>

#include "../base/basepicturepb.h"
#include "../../MusicBaseData/Objects/headers/Category.h"

class CategoryPB: public BasePicturePB
{
    Q_OBJECT

public:
    explicit CategoryPB(Category &category, BaseFragment *fragment, Poco::SharedPtr <BaseModel> m_user = nullptr,
                        QWidget *parent = nullptr);

    explicit CategoryPB(Category &category, Poco::SharedPtr <BaseModel> m_user = nullptr, QWidget *parent = nullptr);

    ~CategoryPB();

    const Category &category();

public
    slots:
            void onClicked();

private:
    Category m_category;
    Poco::SharedPtr <BaseModel> m_user;
    BaseFragment *m_fragment;
};

#endif // PICTUREBP_H
