#ifndef ALBUMPB_H
#define ALBUMPB_H

#include "../base/basepicturepb.h"
#include "../../MusicBaseData/Objects/headers/Album.h"

class AlbumPB: public BasePicturePB
{
public:
    AlbumPB(Album &album, BaseFragment *fragment, Poco::SharedPtr <BaseModel> user = nullptr,
            QWidget *parent = nullptr);

    ~AlbumPB() = default;

    const Album &album() const;

public
slots:
    void onClicked();

private:
    Album m_album;
    Poco::SharedPtr <BaseModel> m_user;
    BaseFragment *m_fragment;
};

#endif // ALBUMPB_H
