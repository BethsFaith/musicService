#ifndef GENREPB_H
#define GENREPB_H

#include "../base/basepicturepb.h"
#include "../../MusicBaseData/Objects/headers/Genre.h"

class GenrePB: public BasePicturePB
{
public:
    GenrePB(Genre &genre, BaseFragment *fragment, Poco::SharedPtr <BaseModel> user = nullptr,
            QWidget *parent = nullptr);

    ~GenrePB() = default;

    const Genre &genre() const;

public slots:
    void onClicked();

private:
    Genre m_genre;
    Poco::SharedPtr <BaseModel> m_user;
    BaseFragment *m_fragment;
};

#endif // GENREPB_H
