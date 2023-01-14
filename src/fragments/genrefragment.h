#ifndef GENREFRAGMENT_H
#define GENREFRAGMENT_H


#include <QVBoxLayout>
#include <QFileDialog>
#include <QPointer>

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../../MusicBaseData/Objects/headers/Genre.h"
#include "../buttons/songpb.h"
#include "../actions/addsongtoplaylist.h"

namespace Ui
{
    class GenreFragment;
}

class GenreFragment: public BaseFragment
{
    Q_OBJECT

public:
    explicit GenreFragment(QWidget *parent = nullptr);

    ~GenreFragment();

    void setData(Poco::SharedPtr <DBWorker> model) override;

    void setUser(Poco::SharedPtr <BaseModel> model) override;

    void update() override;

private
    slots:
            void on_pb_changeCover_clicked();

    void on_pb_changeName_clicked();

private:
    Ui::GenreFragment *ui;
    Poco::SharedPtr <BaseModel> m_user;
    Poco::SharedPtr <Genre> m_genre;

    std::vector<SongPB *> m_songs;
};

#endif // GENREFRAGMENT_H
