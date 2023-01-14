#ifndef CATEGORYFRAGMENT_H
#define CATEGORYFRAGMENT_H

#include <QPointer>

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../../MusicBaseData/Objects/headers/Category.h"
#include "ui_categoryfragment.h"
#include "../models/performermodel.h"
#include "../buttons/playlistpb.h"

namespace Ui
{
    class CategoryFragment;
}

class CategoryFragment: public BaseFragment
{
    Q_OBJECT

public:
    explicit CategoryFragment(QWidget *parent = nullptr);

    ~CategoryFragment();

    void setData(Poco::SharedPtr <DBWorker> model) override;

    void setUser(Poco::SharedPtr <BaseModel> model) override;

    void update() override;

private:
    Ui::CategoryFragment *ui;
    Poco::SharedPtr <Category> m_category;
    Poco::SharedPtr <BaseModel> m_user;

    std::vector<PlaylistPB *> m_playlists;
};

#endif // CATEGORYFRAGMENT_H
