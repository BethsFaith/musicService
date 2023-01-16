#ifndef USERFRAGMENT_H
#define USERFRAGMENT_H

#include <QMenu>
#include <QVBoxLayout>
#include <QPointer>

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../buttons/playlistpb.h"

namespace Ui
{
    class UserFragment;
}

class UserFragment: public BaseFragment
{
    Q_OBJECT

public:
    explicit UserFragment(QWidget *parent = nullptr);

    ~UserFragment();

    void setUser(Poco::SharedPtr <BaseModel> model) override;

    void setData(Poco::SharedPtr <DBWorker> model) override;

    void update() override;

private:
    Ui::UserFragment *ui;
    Poco::SharedPtr <User> m_mainUser;
    Poco::SharedPtr <BaseModel> m_ghostUser;
};

#endif // USERFRAGMENT_H
