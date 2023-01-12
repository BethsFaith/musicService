#ifndef CATEGORYBP_H
#define CATEGORYBP_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class CategoryBP;
}

class CategoryPB : public QWidget
{
  Q_OBJECT

public:
   explicit CategoryPB(QWidget *parent = nullptr);
  ~CategoryPB();

   QPushButton* getPB();
   std::string getName();
   std::string getCreatorName();
   void setName(const std::string &name);
   void setCreator(const std::string &name);

signals:
  void clicked();
public slots:
  void onClicked();
private slots:
  void on_pushButton_clicked();

private:
  Ui::CategoryBP *ui;
  std::string m_name;
  std::string m_creatorName;
};

#endif // CATEGORYBP_H
