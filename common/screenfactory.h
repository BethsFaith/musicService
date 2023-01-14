#ifndef SCREENFACTORY_H
#define SCREENFACTORY_H

#include "../base/basescreensfactory.h"
#include "../fragments/loginfragment.h"
#include "../fragments/registrfragment.h"
#include "../fragments/startfragment.h"
#include "../fragments/splashfragment.h"
#include "../fragments/performerstartfragment.h"
#include "../fragments/userstartfragment.h"
#include "../fragments/catalogfragment.h"
#include "../fragments/categoryfragment.h"
#include "../fragments/searchfragment.h"
#include "../fragments/playlistfragment.h"
#include "../fragments/albumfragment.h"
#include "../fragments/performerfragment.h"
#include "../fragments/userfragment.h"
#include "../fragments/userfavourites.h"
#include "../fragments/userplaylists.h"
#include "../fragments/userlibraryfragment.h"
#include "../fragments/createplaylistfragment.h"
#include "../fragments/genrefragment.h"
#include "../fragments/performertoolsfragment.h"
#include "../fragments/createalbumfragment.h"

class ScreensFactory: public BaseScreensFactory
{
public:
    ScreensFactory(QString start_tag = screens::SPLASH_TAG);

    virtual ~ScreensFactory() = default;

    BaseFragment *create(QString tag) override;

    QString createStart() override;

private:
    QString m_startTag;
};

#endif // SCREENFACTORY_H
