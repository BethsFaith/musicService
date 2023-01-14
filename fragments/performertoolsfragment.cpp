#include "performertoolsfragment.h"
#include "ui_performertoolsfragment.h"

PerformerToolsFragment::PerformerToolsFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::PerformerToolsFragment) {
    ui->setupUi(this);

}

PerformerToolsFragment::~PerformerToolsFragment() {
    delete ui;
}

void PerformerToolsFragment::setUser(Poco::SharedPtr <BaseModel> model) {
    m_perf = model.cast<PerformerModel>();
}

void PerformerToolsFragment::update() {
    ui->l_name->setText(m_perf->getPerformer()->getName().c_str());

    QFrame *frame = new QFrame();
    QVBoxLayout *l = new QVBoxLayout(frame);
    l->setDirection(QVBoxLayout::Direction::LeftToRight);
    ui->SA_Albums->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->SA_Albums->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->SA_Albums->setWidgetResizable(true);
    ui->SA_Albums->setWidget(frame);

    QFrame *frame2 = new QFrame();
    QVBoxLayout *l2 = new QVBoxLayout(frame2);
    l2->setDirection(QVBoxLayout::Direction::LeftToRight);
    ui->SA_notPublicalbums->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->SA_notPublicalbums->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->SA_notPublicalbums->setWidgetResizable(true);
    ui->SA_notPublicalbums->setWidget(frame2);

    try {
        auto albums = m_perf->getPerformer()->getAlbums();
        for (int i{}; i < albums.size(); ++i) {
            std::cout << albums[i].getName() << std::endl;
            QPointer <AlbumPB> alPB = new AlbumPB(albums[i], this, m_perf);
            if (albums[i].isPublic())
                l->addWidget(alPB);
            else
                l2->addWidget(alPB);
        }
    } catch (Poco::Exception &ex) {
        std::cerr << ex.message();
    }
}

void PerformerToolsFragment::on_pb_createAlbum_clicked() {
    navigateWithUser(screens::CREATE_ALBUM_TAG, m_perf);
}

