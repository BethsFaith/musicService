#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <QObject>
#include <QLinkedList>
#include <QStackedWidget>
#include "../base/basescreensfactory.h"
#include "../MusicBaseData/General/headers/DBWorker.h"

class Navigator: public QObject {
  Q_OBJECT
private:
  QStackedWidget *currentContainer;
  BaseScreensFactory *screensFactory;
  QLinkedList<BaseFragment*> stack;

  /**
     * @brief createAndConnect
     * @param tag тэг создаваемого фрагмента.
     *
     * Создание фрагмента по тегу и его
     * прикрепление к навигатору.
     *
     * @return фрагмент присоединенный к слотам навигатора.
     */
  BaseFragment* createAndConnect(QString tag);

  /**
     * @brief connectFragment
     * @param fragment фрагмент который переходит
     *        в активное состояние.
     *
     * Прикрепление текущего фрагмента
     * к слотам навигатора для быстрого
     * и удобного перехода между экранами.
     *
     */
  void connectFragment(BaseFragment *fragment);

  /**
     * @brief disconnectFragment
     * @param fragment
     *
     * Отключение сигналов от фрагмента.
     */
  void disconnectFragment(BaseFragment *fragment);
public:
  Navigator(
      QStackedWidget *container,
      BaseScreensFactory *screensFactory
      );
  BaseFragment* getStartScreen();

public slots:
  /**
     * @brief navigateTo
     * @param tag имя следующего экрана.
     *
     * Переход к следующему экрану.
     */
  void navigateTo(QString tag);

  /**
     * @brief back
     *
     * Переход назад по цепочке.
     */
  void back();

  /**
     * @brief replace
     * @param tag имя экрана на который
     *        произойдет замена.
     *
     * Замена текущего экрана с сохранением
     * предыдущей цепочки.
     */
  void replace(QString tag);

  /**
     * @brief newRootScreen
     * @param tag имя экрана на который
     *        произойдет замена.
     *
     * Замена текущего экрана на новый и сброс
     * всей цепочки экранов.
     */
  void newRootScreen(QString tag, Poco::SharedPtr<DBWorker> data = nullptr, Poco::SharedPtr<BaseModel> user = nullptr);

//  void newRootScreenWithUser(QString tag, Poco::SharedPtr<BaseModel> user);
//  void newRootScreenWithData(QString tag, Poco::SharedPtr<DBWorker> data);
//  void newRootScreenWithDataAndUser(QString tag, Poco::SharedPtr<DBWorker> data, Poco::SharedPtr<BaseModel> user);
  /**
     * @brief navigateWhithData
     * @param model
     *
     * Тот же navigateTo но с данными.
     */
//  void navigateWhithData(QString tag, Poco::SharedPtr<BaseModel> model);
     void navigateWithData(QString tag, Poco::SharedPtr<DBWorker> model);
  /**
     * @brief navigateWhithData
     * @param model
     *
     * Тот же back но с данными.
     */
//  void backWhithData(Poco::SharedPtr<BaseModel>  model);
  void backWithData(Poco::SharedPtr<DBWorker>  model);

//  void navigateWhithDataAndUser(QString tag, Poco::SharedPtr<BaseModel> model, Poco::SharedPtr<BaseModel> user);
//  void backWhithDataAndUser(Poco::SharedPtr<BaseModel>  model, Poco::SharedPtr<BaseModel> user);
  void navigateWithDataAndUser(QString tag, Poco::SharedPtr<DBWorker> model, Poco::SharedPtr<BaseModel> user);
  void backWithDataAndUser(Poco::SharedPtr<DBWorker>  model, Poco::SharedPtr<BaseModel> user);

  void navigateWithUser(QString tag, Poco::SharedPtr<BaseModel> user);
  void backWithUser(QString tag, Poco::SharedPtr<BaseModel> user);
};

#endif // NAVIGATOR_H
