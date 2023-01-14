#include "createalbumfragment.h"
#include "ui_createalbumfragment.h"

CreateAlbumFragment::CreateAlbumFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::CreateAlbumFragment) {
    ui->setupUi(this);
}

CreateAlbumFragment::~CreateAlbumFragment() {
    delete ui;
}

void CreateAlbumFragment::setUser(Poco::SharedPtr <BaseModel> model) {
    m_perf = model.cast<PerformerModel>();
}

void CreateAlbumFragment::on_pb_create_clicked() {
    std::string name = ui->TE_Name->toPlainText().toStdString();
    if (name.empty()) {
        ui->l_error->setText(QString{"Не оставляйте поля пустыми"});
        return;
    }

    m_perf->getPerformer()->addAlbum(name, file);
    Poco::SharedPtr <Album> album = Poco::makeShared<Album>(name, m_perf->getPerformer()->getName(),
                                                            m_perf->getPerformer()->dataBase());
    navigateWithDataAndUser(screens::ALBUM_TAG, album, m_perf);
}


void CreateAlbumFragment::on_pb_picture_clicked() {
    try {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "/home",
                                                        tr("Images (*.png *.xpm *.jpg)"));
        if (!fileName.isEmpty()) {
            file = fileName.toStdString();
            QPixmap picture(fileName);
            QSize PicSize(200, 200);
            picture = picture.scaled(PicSize, Qt::KeepAspectRatio);
            ui->l_coverArt->resize(picture.height(), picture.width());
            ui->l_coverArt->setPixmap(picture);
        }
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.displayText();
    }
}

