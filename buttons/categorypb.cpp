#include "categorypb.h"
#include "ui_categorypb.h"

CategoryPB::CategoryPB(QWidget *parent) :
                                          QWidget(parent),
                                          ui(new Ui::CategoryBP)
{
  ui->setupUi(this);
  connect(ui->pushButton, &QPushButton::clicked, this, &CategoryPB::onClicked);
}

CategoryPB::~CategoryPB()
{
  delete ui;
}

QPushButton *CategoryPB::getPB()
{
  return ui->pushButton;
}

std::string CategoryPB::getName()
{
  return m_name;
}

std::string CategoryPB::getCreatorName()
{
  return m_creatorName;
}

void CategoryPB::setName(const std::string &name)
{
  m_name = name;
  ui->l_name->setText(QString(name.c_str()));
}

void CategoryPB::setCreator(const std::string &name)
{
  m_creatorName = name;
}

void CategoryPB::onClicked()
{
  emit clicked();
}

void CategoryPB::on_pushButton_clicked()
{
   emit clicked();
}

