#include "categoryfragment.h"
#include <QVBoxLayout>

CategoryFragment::CategoryFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::CategoryFragment) {
    ui->setupUi(this);
}

CategoryFragment::~CategoryFragment() {
    delete ui;
}

void CategoryFragment::setData(Poco::SharedPtr <DBWorker> model) {
    auto m = model;
    m_category = m.cast<Category>();
}

void CategoryFragment::setUser(Poco::SharedPtr <BaseModel> model) {
    m_user = model;
}

void CategoryFragment::update() {
    if (!m_category.isNull()) {
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
            for (int i{}; i < playlists.size(); ++i) {
                QPointer <PlaylistPB> plPB = new PlaylistPB(playlists[i], this, m_user);
                l->addWidget(plPB);
            }
        } catch (Poco::Exception &ex) {
            std::cerr << ex.message();
        }
    }
}
