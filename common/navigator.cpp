#include "navigator.h"

using namespace screens;

Navigator::Navigator(
    QStackedWidget *container,
    BaseScreensFactory *screensFactory
    )
{
  this->screensFactory = screensFactory;
  this->currentContainer = container;
  BaseFragment* startFragment = getStartScreen();
  this->stack.append(startFragment);

  currentContainer->addWidget(stack.last());
  currentContainer->setCurrentIndex(0);
}

BaseFragment* Navigator::getStartScreen() {
  return createAndConnect(this->screensFactory->createStart());
}


void Navigator::navigateTo(QString tag) {
  qDebug("Navigator navigateTo");
  BaseFragment *newFragment = this->screensFactory->create(tag);
  stack.last()->onPause();
  disconnectFragment(stack.last());
  connectFragment(newFragment);
  stack.append(newFragment);
  currentContainer->addWidget(newFragment);
  currentContainer->setCurrentWidget(newFragment);
}

void Navigator::back() {
  qDebug("Navigator back");
  currentContainer->removeWidget(stack.last());
  delete stack.last();
  stack.removeLast();
  connectFragment(stack.last());
  stack.last()->onResume();
  currentContainer->setCurrentWidget(stack.last());
}

void Navigator::replace(QString tag) {
  qDebug("Navigator replace");
  BaseFragment *newFragment = this->screensFactory->create(tag);
  currentContainer->removeWidget(stack.last());
  delete stack.last();
  stack.removeLast();
  connectFragment(newFragment);
  currentContainer->addWidget(newFragment);
}

void Navigator::newRootScreen(QString tag, Poco::SharedPtr<DBWorker> data, Poco::SharedPtr<BaseModel> user) {
  qDebug("Navigator newRootScreen");
  qDebug(tag.toStdString().c_str());
  BaseFragment *newFragment = this->screensFactory->create(tag);
  disconnectFragment(stack.last());
  stack.clear();
  connectFragment(newFragment);
  for(int i = currentContainer->count(); i >= 0; i--)
  {
    QWidget* widget = currentContainer->widget(i);
    currentContainer->removeWidget(widget);
    widget->deleteLater();
  }
  currentContainer->addWidget(newFragment);
  std::cout << data << " :data " << user << " :user" << std::endl;
  if (!data.isNull())
    newFragment->setData(data);
  if (!user.isNull())
    newFragment->setUser(user);
  newFragment->update();
  stack.append(newFragment);
}

//void Navigator::newRootScreenWithUser(QString tag, Poco::SharedPtr<BaseModel> user)
//{
//  qDebug("Navigator newRootScreen");
//  BaseFragment *newFragment = this->screensFactory->create(tag);
//  disconnectFragment(stack.last());
//  stack.clear();
//  connectFragment(newFragment);
//  for(int i = currentContainer->count(); i >= 0; i--)
//  {
//    QWidget* widget = currentContainer->widget(i);
//    currentContainer->removeWidget(widget);
//    widget->deleteLater();
//  }
//  currentContainer->addWidget(newFragment);
//  newFragment->setUser(user);
//  newFragment->update();
//  stack.append(newFragment);
//}

//void Navigator::newRootScreenWithData(QString tag, Poco::SharedPtr<DBWorker> data)
//{
//  qDebug("Navigator newRootScreen");
//  BaseFragment *newFragment = this->screensFactory->create(tag);
//  disconnectFragment(stack.last());
//  stack.clear();
//  connectFragment(newFragment);
//  for(int i = currentContainer->count(); i >= 0; i--)
//  {
//    QWidget* widget = currentContainer->widget(i);
//    currentContainer->removeWidget(widget);
//    widget->deleteLater();
//  }
//  currentContainer->addWidget(newFragment);
//  newFragment->setData(data);
//  newFragment->update();
//  stack.append(newFragment);
//}

//void Navigator::newRootScreenWithDataAndUser(QString tag, Poco::SharedPtr<DBWorker> data, Poco::SharedPtr<BaseModel> user)
//{
//  qDebug("Navigator newRootScreen");
//  BaseFragment *newFragment = this->screensFactory->create(tag);
//  disconnectFragment(stack.last());
//  stack.clear();
//  connectFragment(newFragment);
//  for(int i = currentContainer->count(); i >= 0; i--)
//  {
//    QWidget* widget = currentContainer->widget(i);
//    currentContainer->removeWidget(widget);
//    widget->deleteLater();
//  }
//  currentContainer->addWidget(newFragment);
//  newFragment->setData(data);
//  newFragment->setUser(user);
//  newFragment->update();
//  stack.append(newFragment);
//}

void Navigator::backWithData(Poco::SharedPtr<DBWorker> model) {
  back();
  stack.last()->setData(model);
  stack.last()->update();
}

void Navigator::navigateWithDataAndUser(QString tag, Poco::SharedPtr<DBWorker> model, Poco::SharedPtr<BaseModel> user)
{
  navigateTo(tag);
  stack.last()->setData(model);
  stack.last()->setUser(user);
  stack.last()->update();
}

void Navigator::navigateWithData(QString tag, Poco::SharedPtr<DBWorker> model) {
  navigateTo(tag);
  stack.last()->setData(model);
  stack.last()->update();
}

void Navigator::backWithDataAndUser(Poco::SharedPtr<DBWorker> model, Poco::SharedPtr<BaseModel> user)
{
  back();
  stack.last()->setData(model);
  stack.last()->setUser(user);
  stack.last()->update();
}

void Navigator::navigateWithUser(QString tag, Poco::SharedPtr<BaseModel> user)
{
  navigateTo(tag);
  stack.last()->setUser(user);
  stack.last()->update();
}

void Navigator::backWithUser(QString tag, Poco::SharedPtr<BaseModel> user)
{
  std::cout << "backU" << std::endl;
  back();
  stack.last()->setUser(user);
  stack.last()->update();
}


void Navigator::connectFragment(BaseFragment *fragment) {
  connect(fragment, &BaseFragment::back, this, &Navigator::back);
  connect(fragment, &BaseFragment::replace, this, &Navigator::replace);
  connect(fragment, &BaseFragment::navigateTo, this, &Navigator::navigateTo);
  connect(fragment, &BaseFragment::newRootScreen, this, &Navigator::newRootScreen);
//  connect(fragment, &BaseFragment::newRootScreenWithUser, this, &Navigator::newRootScreenWithUser);
  connect(fragment, &BaseFragment::navigateWithData, this, &Navigator::navigateWithData);
  connect(fragment, &BaseFragment::navigateWithUser, this, &Navigator::navigateWithUser);
  connect(fragment, &BaseFragment::navigateWithDataAndUser, this, &Navigator::navigateWithDataAndUser);
  connect(fragment, &BaseFragment::backWithData, this, &Navigator::backWithData);
}

void Navigator::disconnectFragment(BaseFragment *fragment) {
  disconnect(fragment, &BaseFragment::back, this, &Navigator::back);
  disconnect(fragment, &BaseFragment::replace, this, &Navigator::replace);
  disconnect(fragment, &BaseFragment::navigateTo, this, &Navigator::navigateTo);
  disconnect(fragment, &BaseFragment::newRootScreen, this, &Navigator::newRootScreen);
//  disconnect(fragment, &BaseFragment::newRootScreenWithUser, this, &Navigator::newRootScreenWithUser);
  disconnect(fragment, &BaseFragment::navigateWithData, this, &Navigator::navigateWithData);
  disconnect(fragment, &BaseFragment::navigateWithUser, this, &Navigator::navigateWithUser);
  disconnect(fragment, &BaseFragment::navigateWithDataAndUser, this, &Navigator::navigateWithDataAndUser);
}

BaseFragment* Navigator::createAndConnect(QString tag) {
  BaseFragment *fragment = this->screensFactory->create(tag);
  connectFragment(fragment);
  return fragment;
}


//void Navigator::backWhithData(Poco::SharedPtr<BaseModel> model) {
//  back();
//  stack.last()->setData(model);
//}

//void Navigator::navigateWhithDataAndUser(QString tag, Poco::SharedPtr<BaseModel> model, Poco::SharedPtr<BaseModel> user)
//{
//  navigateTo(tag);
//  stack.last()->setData(model);
//  stack.last()->setUser(user);
//}

//void Navigator::navigateWhithData(QString tag, Poco::SharedPtr<BaseModel>  model) {
//  navigateTo(tag);
//  stack.last()->setData(model);
//}

//void Navigator::backWhithDataAndUser(Poco::SharedPtr<BaseModel> model, Poco::SharedPtr<BaseModel> user)
//{
//  back();
//  stack.last()->setData(model);
//  stack.last()->setUser(user);
//}

//void Navigator::connectFragment(BaseFragment *fragment) {
//  connect(fragment, &BaseFragment::back, this, &Navigator::back);
//  connect(fragment, &BaseFragment::replace, this, &Navigator::replace);
//  connect(fragment, &BaseFragment::navigateTo, this, &Navigator::navigateTo);
//  connect(fragment, &BaseFragment::newRootScreen, this, &Navigator::newRootScreen);
//  connect(fragment, &BaseFragment::navigateWhithData, this, &Navigator::navigateWhithData);
//  connect(fragment, &BaseFragment::navigateWhthUser, this, &Navigator::navigateWhithDataAndUser);
//  connect(fragment, &BaseFragment::backWithData, this, &Navigator::backWhithData);
//}

//void Navigator::disconnectFragment(BaseFragment *fragment) {
//  disconnect(fragment, &BaseFragment::back, this, &Navigator::back);
//  disconnect(fragment, &BaseFragment::replace, this, &Navigator::replace);
//  disconnect(fragment, &BaseFragment::navigateTo, this, &Navigator::navigateTo);
//  disconnect(fragment, &BaseFragment::newRootScreen, this, &Navigator::newRootScreen);
//  disconnect(fragment, &BaseFragment::navigateWhithData, this, &Navigator::navigateWhithData);
//  disconnect(fragment, &BaseFragment::navigateWhthUser, this, &Navigator::navigateWhithDataAndUser);
//  disconnect(fragment, &BaseFragment::backWithData, this, &Navigator::backWhithData);
//}

//BaseFragment* Navigator::createAndConnect(QString tag) {
//  BaseFragment *fragment = this->screensFactory->create(tag);
//  connectFragment(fragment);
//  return fragment;
//}
