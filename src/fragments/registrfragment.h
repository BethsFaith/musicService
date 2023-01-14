#ifndef REGISTRFRAGMENT_H
#define REGISTRFRAGMENT_H

#include <QPointer>

#include "../base/basefragment.h"
#include "../models/databasemodel.h"
#include "../models/usermodel.h"
#include "../models/performermodel.h"

namespace Ui
{
    class RegistrFragment;
}

class RegistrFragment: public BaseFragment
{
    Q_OBJECT

public:
    explicit RegistrFragment(QWidget *parent = nullptr);

    ~RegistrFragment();

    void setData(Poco::SharedPtr <DBWorker> model) override;

private
    slots:
            void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::RegistrFragment *ui;
    Poco::SharedPtr <DataBase> m_bm;
};

#endif // REGISTRFRAGMENT_H
