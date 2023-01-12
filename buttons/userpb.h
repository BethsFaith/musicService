#ifndef USERPB_H
#define USERPB_H

#include <QWidget>

namespace Ui {
class userPB;
}

class userPB : public QWidget
{
  Q_OBJECT

      public:
               explicit userPB(QWidget *parent = nullptr);
  ~userPB();

private:
  Ui::userPB *ui;
};

#endif // USERPB_H
