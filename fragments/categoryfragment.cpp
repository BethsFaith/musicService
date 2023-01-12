#include "categoryfragment.h"
#include <QVBoxLayout>

CategoryFragment::CategoryFragment(QWidget *parent) :
                                                      BaseFragment(parent),
                                                      ui(new Ui::CategoryFragment)
{
  ui->setupUi(this);
}

CategoryFragment::~CategoryFragment()
{
  delete ui;
}

void CategoryFragment::on_pushButton_clicked()
{
  std::cout << "CLICKED" << std::endl;
  CategoryPB* button = qobject_cast<CategoryPB*>(sender());
  int id{};
  if( button != NULL )
  {
    try{
      id = m_category->getDB()->getPlaylistId(button->getName(), button->getCreatorName());

      Poco::SharedPtr<Playlist> playlist = Poco::makeShared<Playlist>(id, m_category->getDB());

      if (m_user.isNull())
        navigateWithData(screens::PLAYLIST_TAG, playlist);
      else
        navigateWithDataAndUser(screens::PLAYLIST_TAG, playlist, m_user);
    }
    catch(Poco::Exception &ex)
    {
      std::cout << ex.message() << std::endl;
    }
  }
}

void CategoryFragment::setData(Poco::SharedPtr<DBWorker> model)
{
  auto m = model;
  m_category = m.unsafeCast<Category>();
}

void CategoryFragment::setUser(Poco::SharedPtr<BaseModel> model)
{
  m_user = model;
}

void CategoryFragment::update()
{
  if (!m_category.isNull())
  {
    ui->l_name->setText(m_category->getName().c_str());
    QPixmap picture(m_category->getCoverArt().c_str());
    ui->l_Cover->resize(picture.height(), picture.width());
    ui->l_Cover->setPixmap(picture);

    ui->scrollArea->setVisible(true);
    QFrame *frame = new QFrame();
    QVBoxLayout *l = new QVBoxLayout(frame);
    l->setDirection(QVBoxLayout::Direction::LeftToRight);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(frame);

    try {
      auto playlists = m_category->getPlaylists();
      for (int i{}; i < playlists.size(); ++i)
      {
        m_playlists.push_back(new CategoryPB());
        m_playlists[i]->setName(playlists[i].getName());
        m_playlists[i]->setCreator(playlists[i].getUserNickname());
        QPixmap pixmap(QString{playlists[i].getCoverArtRef().c_str()});
        QIcon ButtonIcon(pixmap);
        m_playlists[i]->getPB()->setIcon(ButtonIcon);
        m_playlists[i]->getPB()->setIconSize(pixmap.rect().size());
        connect(m_playlists.at(i), &CategoryPB::clicked, this, &CategoryFragment::on_pushButton_clicked);

        l->addWidget(m_playlists[i]);
      }
    }  catch (Poco::Exception &ex) {
      std::cout << ex.message();
    }
  }
}
