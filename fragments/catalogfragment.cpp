#include "catalogfragment.h"
#include "ui_catalogfragment.h"
#include <QVBoxLayout>
#include <QPixmap>
#include <QDir>


CatalogFragment::CatalogFragment(QWidget *parent) :
                                                    BaseFragment(parent),
                                                    ui(new Ui::CatalogFragment)
{
  ui->setupUi(this);
  ui->scrollArea->setVisible(true);
  QFrame *frame = new QFrame();
  l = new QVBoxLayout(frame);
  l->setDirection(QVBoxLayout::Direction::LeftToRight);
  ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  ui->scrollArea->setWidgetResizable(true);
  ui->scrollArea->setWidget(frame);

  m_bm = Poco::makeShared<DataBase>();
  m_slib = Poco::makeShared<SharedLibrary>(m_bm);

  auto categories = m_slib->getAllCategories();

  for (int i{}; i < categories.size(); ++i)
  {
    m_categories.push_back(new CategoryPB());
    m_categories[i]->setName(categories[i].getName());
    QPixmap pixmap(QString{categories[i].getCoverArt().c_str()});
    QIcon ButtonIcon(pixmap);
    m_categories[i]->getPB()->setIcon(ButtonIcon);
    m_categories[i]->getPB()->setIconSize(pixmap.rect().size());
    connect(m_categories.at(i), &CategoryPB::clicked, this, &CatalogFragment::on_category_clicked);

    l->addWidget(m_categories[i]);
  }

  QFrame *frame2 = new QFrame();
  l2 = new QVBoxLayout(frame2);
  l2->setDirection(QVBoxLayout::Direction::LeftToRight);
  ui->scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  ui->scrollArea_2->setWidgetResizable(true);
  ui->scrollArea_2->setWidget(frame2);

  auto genres = m_slib->getAllGenres();
  for (int i{}; i < genres.size(); ++i)
  {
    m_genres.push_back(new CategoryPB());
    m_genres[i]->setName(genres[i].name());
    QDir dir(".");
    QPixmap pixmap(QString{(genres[i].cover_art()).c_str()});
    QIcon ButtonIcon(pixmap);
    m_genres[i]->getPB()->setIcon(ButtonIcon);
    m_genres[i]->getPB()->setIconSize(pixmap.rect().size());
    connect(m_genres.at(i), &CategoryPB::clicked, this, &CatalogFragment::on_genre_clicked);

    l2->addWidget(m_genres[i]);
  }
}

CatalogFragment::~CatalogFragment()
{
  delete ui;
}

void CatalogFragment::setUser(Poco::SharedPtr<BaseModel> model)
{
  m_user = model;
}

void CatalogFragment::on_category_clicked()
{
//  std::cout << "CLICKED" << std::endl;
  CategoryPB* button = qobject_cast<CategoryPB*>(sender());
  int id{};
  if( button != NULL )
  {
    try{
//      std::cout << "!null" << std::endl;
      id = m_bm->getCategoryId(button->getName());
//      std::cout << std::to_string(id);
      Poco::SharedPtr<Category> category = Poco::makeShared<Category>(id, m_bm);
      if (m_user.isNull())
        navigateWithData(screens::CATEGORY_TAG, category);
      else
       navigateWithDataAndUser(screens::CATEGORY_TAG, category, m_user);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.displayText() << std::endl;
    }
  }
}

void CatalogFragment::on_genre_clicked()
{
  CategoryPB* button = qobject_cast<CategoryPB*>(sender());
  int id{};
  if( button != NULL )
  {
    try{
      auto genre = Poco::makeShared<Genre>(m_bm->getGenreId(button->getName()), m_bm);
      if (m_user.isNull())
        navigateWithData(screens::GENRE_TAG, genre);
      else
        navigateWithDataAndUser(screens::GENRE_TAG, genre, m_user);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.displayText() << std::endl;
    }
  }
}
