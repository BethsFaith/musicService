#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <QObject>
#include <QLinkedList>
#include <QStackedWidget>
#include "../base/basescreensfactory.h"
#include "../MusicBaseData/General/headers/DBWorker.h"

class Navigator: public QObject
{
    Q_OBJECT
private:
    QStackedWidget *currentContainer;
    BaseScreensFactory *screensFactory;
    QLinkedList<BaseFragment *> stack;

    BaseFragment *createAndConnect(QString tag);

    void connectFragment(BaseFragment *fragment);

    void disconnectFragment(BaseFragment *fragment);

public:
    Navigator(
            QStackedWidget *container,
            BaseScreensFactory *screensFactory
    );

    BaseFragment *getStartScreen();

public
    slots:

            void navigateTo(QString
    tag);

    void back();


    void replace(QString tag);

    void
    newRootScreen(QString tag, Poco::SharedPtr <DBWorker> data = nullptr, Poco::SharedPtr <BaseModel> user = nullptr);

    void navigateWithData(QString tag, Poco::SharedPtr <DBWorker> model);

    void backWithData(Poco::SharedPtr <DBWorker> model);

    void navigateWithDataAndUser(QString tag, Poco::SharedPtr <DBWorker> model, Poco::SharedPtr <BaseModel> user);

    void backWithDataAndUser(Poco::SharedPtr <DBWorker> model, Poco::SharedPtr <BaseModel> user);

    void navigateWithUser(QString tag, Poco::SharedPtr <BaseModel> user);

    void backWithUser(QString tag, Poco::SharedPtr <BaseModel> user);
};

#endif // NAVIGATOR_H
