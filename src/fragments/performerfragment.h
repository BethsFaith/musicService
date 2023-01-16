#ifndef PERFORMERFRAGMENT_H
#define PERFORMERFRAGMENT_H

#include <QPointer>
#include <QVBoxLayout>

#include "../base/basefragment.h"
#include "../models/usermodel.h"
#include "../../MusicBaseData/Persons/headers/Performer.h"
#include "../models/performermodel.h"
#include "../buttons/albumpb.h"
#include "../buttons/songpb.h"
#include "../actions/addsongtoplaylist.h"

namespace Ui
{
    class PerformerFragment;
}

class PerformerFragment: public BaseFragment
{
    Q_OBJECT

public:
    explicit PerformerFragment(QWidget *parent = nullptr);

    ~PerformerFragment();

    void setUser(Poco::SharedPtr <BaseModel> model) override;

    void setData(Poco::SharedPtr <DBWorker> model) override;

    void update() override;

private:
    Ui::PerformerFragment *ui;

    Poco::SharedPtr <Performer> m_performer;
    Poco::SharedPtr <BaseModel> m_user;
};

#endif // PERFORMERFRAGMENT_H
