#ifndef SPLASHFRAGMENT_H
#define SPLASHFRAGMENT_H

#include <QShortcut>

#include "../base/basefragment.h"

namespace Ui {
class SplashFragment;
}

class SplashFragment : public BaseFragment
{
  Q_OBJECT

  public:
  explicit SplashFragment(QWidget *parent = nullptr);
  ~SplashFragment();

private slots:
  void slide();
private:
  Ui::SplashFragment *ui;

  QShortcut *keySpace;
};

#endif // SPLASHFRAGMENT_H
