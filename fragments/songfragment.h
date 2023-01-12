#ifndef SONGFRAGMENT_H
#define SONGFRAGMENT_H

#include "../base/basefragment.h"

namespace Ui {
class SongFragment;
}

class SongFragment : public BaseFragment
{
  Q_OBJECT

      public:
               explicit SongFragment(QWidget *parent = nullptr);
  ~SongFragment();

private:
  Ui::SongFragment *ui;
};

#endif // SONGFRAGMENT_H
