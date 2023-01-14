#ifndef CREATEPLAYLISTFRAGMENT_H
#define CREATEPLAYLISTFRAGMENT_H

#include <QFileDialog>
#include <QPointer>

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../MusicBaseData/Objects/headers/Category.h"
#include "../models/performermodel.h"

namespace Ui
{
    class CreatePlaylistFragment;
}

class CreatePlaylistFragment: public BaseFragment
{
    Q_OBJECT

public:
    explicit CreatePlaylistFragment(QWidget *parent = nullptr);

    ~CreatePlaylistFragment();

    void setUser(Poco::SharedPtr <BaseModel> model) override;

private
    slots:
            void on_pb_create_clicked();

    void on_pb_picture_clicked();

private:
    Ui::CreatePlaylistFragment *ui;
    Poco::SharedPtr <UserModel> m_user;
    std::string file;
};

#endif // CREATEPLAYLISTFRAGMENT_H
