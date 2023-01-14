#ifndef PERFORMERSTARTFRAGMENT_H
#define PERFORMERSTARTFRAGMENT_H

#include <QStackedWidget>
#include <QPointer>

#include "../base/basefragment.h"
#include "../models/performermodel.h"

#include "../models/databasemodel.h"
#include "../common/screenfactory.h"
#include "../common/navigator.h"

namespace Ui
{
    class PerformerStartFragment;
}

class PerformerStartFragment: public BaseFragment
{
    Q_OBJECT

public:
    explicit PerformerStartFragment(QWidget *parent = nullptr);

    ~PerformerStartFragment();

    void setUser(Poco::SharedPtr <BaseModel> model) override;

private
    slots:
            void on_pb_exit_clicked();

    void on_pb_myCatalog_clicked();

    void on_pb_seacrh_clicked();

    void on_pb_catalog_clicked();

private:
    Ui::PerformerStartFragment *ui;
    Poco::SharedPtr <PerformerModel> m_perf;

    QStackedWidget *container;
    BaseScreensFactory *factory;
    Navigator *navigator;
};

#endif // PERFORMERSTARTFRAGMENT_H
