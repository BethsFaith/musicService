#ifndef CREATEALBUMFRAGMENT_H
#define CREATEALBUMFRAGMENT_H

#include <QFileDialog>
#include <QPointer>

#include "../base/basefragment.h"
#include "../models/performermodel.h"
#include "../../MusicBaseData/Objects/headers/Album.h"

namespace Ui
{
    class CreateAlbumFragment;
}

class CreateAlbumFragment: public BaseFragment
{
    Q_OBJECT

public:
    explicit CreateAlbumFragment(QWidget *parent = nullptr);

    ~CreateAlbumFragment();

    void setUser(Poco::SharedPtr <BaseModel> model) override;

private
slots:
    void on_pb_create_clicked();

    void on_pb_picture_clicked();

private:
    Ui::CreateAlbumFragment *ui;
    Poco::SharedPtr <PerformerModel> m_perf;
    std::string file;
};

#endif // CREATEALBUMFRAGMENT_H
