#ifndef CATALOGFRAGMENT_H
#define CATALOGFRAGMENT_H

#include <QPointer>

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../models/performermodel.h"
#include "../MusicBaseData/Objects/headers/SharedLibrary.h"
#include "../buttons/categorypb.h"
#include "../buttons/genrepb.h"
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui
{
    class CatalogFragment;
}

class CatalogFragment: public BaseFragment
{
    Q_OBJECT

public:
    explicit CatalogFragment(QWidget *parent = nullptr);

    ~CatalogFragment();

    void setUser(Poco::SharedPtr <BaseModel> model) override;

    void setData(Poco::SharedPtr <DBWorker> model) override;

    void update() override;

private:
    Ui::CatalogFragment *ui;
    Poco::SharedPtr <DataBase> m_bm;
    Poco::SharedPtr <SharedLibrary> m_slib;
    std::vector<CategoryPB *> m_categories;
    std::vector<GenrePB *> m_genres;
    Poco::SharedPtr <BaseModel> m_user;
    QVBoxLayout *l;
    QVBoxLayout *l2;
};

#endif // CATALOGFRAGMENT_H
