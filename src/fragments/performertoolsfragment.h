#ifndef PERFORMERTOOLSFRAGMENT_H
#define PERFORMERTOOLSFRAGMENT_H

#include <QVBoxLayout>
#include <QPointer>

#include "../base/basefragment.h"
#include "../models/performermodel.h"
#include "../buttons/albumpb.h"

namespace Ui
{
    class PerformerToolsFragment;
}

class PerformerToolsFragment: public BaseFragment
{
    Q_OBJECT

public:
    explicit PerformerToolsFragment(QWidget *parent = nullptr);

    ~PerformerToolsFragment();

    void setUser(Poco::SharedPtr <BaseModel> model) override;

    void update() override;

private slots:
    void on_pb_createAlbum_clicked();

private:
    Ui::PerformerToolsFragment *ui;
    Poco::SharedPtr <PerformerModel> m_perf;
};

#endif // PERFORMERTOOLSFRAGMENT_H
