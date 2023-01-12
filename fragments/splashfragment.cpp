#include "splashfragment.h"
#include "ui_splashfragment.h"
#include <QPicture>
#include <QPixmap>
#include <iostream>
#include <QDebug>
#include "../models/databasemodel.h"

SplashFragment::SplashFragment(QWidget *parent) :
                                                  BaseFragment(parent),
                                                  ui(new Ui::SplashFragment)
{
  ui->setupUi(this);
  QPixmap picture("D://cat.bmp");
  ui->label->resize(picture.height(), picture.width());
  ui->label->setPixmap(picture);

  keySpace = new QShortcut(this);   // Инициализируем объект
  keySpace->setKey(Qt::Key_Space);    // Устанавливаем код клавиши
  // цепляем обработчик нажатия клавиши
  connect(keySpace, SIGNAL(activated()), this, SLOT(slide()));
}

SplashFragment::~SplashFragment()
{
  delete ui;
}

void SplashFragment::slide()
{
  Poco::SharedPtr<DataBase> db = Poco::makeShared<DataBase>();
  Poco::SharedPtr<DataBaseModel> dbm = Poco::makeShared<DataBaseModel>(db);
  navigateWithData(screens::START_TAG, db);
  qDebug() << "dfkdfldlf";
}
