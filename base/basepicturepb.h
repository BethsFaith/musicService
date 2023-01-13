#ifndef BASEPICTUREPB_H
#define BASEPICTUREPB_H

#include <QWidget>

#include "../base/basefragment.h"
#include "../models/usermodel.h"

namespace Ui
{
    class BasePicturePB;
}

class BasePicturePB: public QWidget
{
    Q_OBJECT

public:
    explicit BasePicturePB(QWidget *parent = nullptr);

    virtual ~BasePicturePB();

    void setName(const QString &name);

    void setPicture(const QString &fileName);

protected:
    signals:
            void clicked();
private
    slots:
            void on_pushButton_clicked();

private:
    Ui::BasePicturePB *ui;
};

#endif // BASEPICTUREPB_H
