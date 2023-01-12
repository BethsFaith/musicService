#ifndef SONGPB_H
#define SONGPB_H

#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <Poco/SharedPtr.h>
#include "../MusicBaseData/Objects/headers/Song.h"

namespace Ui {
class SongPB;
}

class SongPB : public QWidget
{
  Q_OBJECT

public:
  explicit SongPB(Poco::SharedPtr<Song> _song, QWidget *parent = nullptr);
  ~SongPB();

  QPushButton* getNameB();
  QPushButton *getPerfB();
  QPushButton* getLikeB();
  const std::string &getName() const;
  void setName(const std::string &newName);
  Poco::SharedPtr<QMenu> getMenu();
  void setActionToMenu(QAction* action);
  void removeAction(QAction* action);
  void clearMenu();

  const std::string &getPerformer() const;
  void setPerformer(const std::string &newPerformer);

  int id;

  const Poco::SharedPtr<Song> &getSong() const;
  void setSong(const Poco::SharedPtr<Song> &newSong);

signals:
  void clickedPerfomance();

  void clickedName();

  void clickedLike();

private slots:
  void on_pb_perf_clicked();

  void on_pb_name_clicked();

  void on_pb_like_clicked();

  void on_pb_add_clicked();

private:
  Ui::SongPB *ui;

  std::string name;
  std::string performer;
  Poco::SharedPtr<QMenu> menu;
  Poco::SharedPtr<Song> song;
};

#endif // SONGPB_H
