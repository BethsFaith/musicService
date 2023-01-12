#ifndef PLAYLISTPB_H
#define PLAYLISTPB_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class playlistPB;
}

class playlistPB : public QWidget
{
  Q_OBJECT

  public:
  explicit playlistPB(QWidget *parent = nullptr);
  ~playlistPB();

  QPushButton* getPB();
  std::string getName();
  void setName(const std::string &name);
private:
  Ui::playlistPB *ui;
  std::string m_name;
};

#endif // PLAYLISTPB_H
