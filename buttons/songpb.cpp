#include "songpb.h"
#include "ui_songpb.h"
#include "../actions/addsongtoplaylist.h"

SongPB::SongPB(Poco::SharedPtr<Song> _song, QWidget *parent) :
                                  QWidget(parent),
                                  ui(new Ui::SongPB),
                                  song{_song}
{
  ui->setupUi(this);
  menu = Poco::makeShared<QMenu>(this);
  ui->pb_add->setMenu(menu);
  ui->pb_perf->setText(song->getPerformerName().c_str());
}

SongPB::~SongPB()
{
  delete ui;
}

QPushButton* SongPB::getNameB()
{
  return ui->pb_name;
}

QPushButton *SongPB::getPerfB()
{
  return ui->pb_perf;
}

QPushButton* SongPB::getLikeB()
{
  return ui->pb_like;
}

void SongPB::on_pb_perf_clicked()
{
  emit clickedPerfomance();
}

void SongPB::on_pb_name_clicked()
{
  emit clickedName();
}

void SongPB::on_pb_like_clicked()
{
  emit clickedLike();
}


void SongPB::on_pb_add_clicked()
{
  ui->pb_add->showMenu();
}

const Poco::SharedPtr<Song> &SongPB::getSong() const
{
  return song;
}

void SongPB::setSong(const Poco::SharedPtr<Song> &newSong)
{
  song = newSong;
}

const std::string &SongPB::getPerformer() const
{
  return performer;
}

void SongPB::setPerformer(const std::string &newPerfomance)
{
  performer = newPerfomance;
  ui->pb_perf->setText(newPerfomance.c_str());
}

const std::string &SongPB::getName() const
{
  return name;
}

void SongPB::setName(const std::string &newName)
{
  name = newName;
  ui->pb_name->setText(newName.c_str());
}

Poco::SharedPtr<QMenu> SongPB::getMenu()
{
  return menu;
}

void SongPB::setActionToMenu(QAction *action)
{
   menu->addAction(action);
}

void SongPB::removeAction(QAction *action)
{
  menu->removeAction(action);
}

void SongPB::clearMenu()
{
  menu->clear();
}

