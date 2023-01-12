#ifndef PERFORMERTOOLSFRAGMENT_H
#define PERFORMERTOOLSFRAGMENT_H

#include "../base/basefragment.h"

namespace Ui {
class PerformerToolsFragment;
}

class PerformerToolsFragment : public BaseFragment
{
  Q_OBJECT

public:
 explicit PerformerToolsFragment(QWidget *parent = nullptr);
  ~PerformerToolsFragment();

private:
  Ui::PerformerToolsFragment *ui;
};

#endif // PERFORMERTOOLSFRAGMENT_H
