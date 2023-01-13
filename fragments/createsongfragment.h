#ifndef CREATESONGFRAGMENT_H
#define CREATESONGFRAGMENT_H

#include <QFrame>

namespace Ui
{
    class CreateSongFragment;
}

class CreateSongFragment: public QFrame
{
    Q_OBJECT

public:
    explicit CreateSongFragment(QWidget *parent = nullptr);

    ~CreateSongFragment();

private:
    Ui::CreateSongFragment *ui;
};

#endif // CREATESONGFRAGMENT_H
