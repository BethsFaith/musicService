#include "catalogfragment.h"
#include "ui_catalogfragment.h"
#include <QVBoxLayout>
#include <QPixmap>
#include <QDir>


CatalogFragment::CatalogFragment(QWidget *parent) :
        BaseFragment(parent),
        ui(new Ui::CatalogFragment) {
    ui->setupUi(this);
    ui->scrollArea->setVisible(true);
}

CatalogFragment::~CatalogFragment() {
    delete ui;
}

void CatalogFragment::setUser(Poco::SharedPtr <BaseModel> model) {
    m_user = model;
}

void CatalogFragment::setData(Poco::SharedPtr <DBWorker> model) {
    m_bm = model.cast<DataBase>();
    m_slib = Poco::makeShared<SharedLibrary>(m_bm);
}

void CatalogFragment::update() {
    if (m_bm.isNull()) {
        if (m_user.isNull()) {
            m_bm = Poco::makeShared<DataBase>();
            m_slib = Poco::makeShared<SharedLibrary>(m_bm);
        }
        else {
            auto user = m_user.cast<UserModel>();
            auto perf = m_user.cast<PerformerModel>();
            if (!user.isNull())
                m_bm = user->m_userBase->getDataBase();
            else
                m_bm = perf->getPerformer()->dataBase();
            m_slib = Poco::makeShared<SharedLibrary>(m_bm);
        }
    }

    try {
        QFrame *frame = new QFrame();
        l = new QVBoxLayout(frame);
        l->setDirection(QVBoxLayout::Direction::LeftToRight);
        ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->scrollArea->setWidgetResizable(true);
        ui->scrollArea->setWidget(frame);
        std::cout << m_slib << " m_slib" << std::endl;
        auto categories = m_slib->getAllCategories();
        for (int i{}; i < categories.size(); ++i)
            std::cout << categories[i].getName() << std::endl;
        for (int i{}; i < categories.size(); ++i) {
            QPointer <CategoryPB> categoryPB = new CategoryPB(categories[i], this, m_user);
            l->addWidget(categoryPB);
        }

        QFrame *frame2 = new QFrame();
        l2 = new QVBoxLayout(frame2);
        l2->setDirection(QVBoxLayout::Direction::LeftToRight);
        ui->scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        ui->scrollArea_2->setWidgetResizable(true);
        ui->scrollArea_2->setWidget(frame2);

        auto genres = m_slib->getAllGenres();
        for (int i{}; i < genres.size(); ++i) {
            QPointer <GenrePB> gPB = new GenrePB(genres[i], this, m_user);
            l2->addWidget(gPB);
        }
    }
    catch (Poco::Exception &ex) {
        std::cerr << ex.displayText();
    }
    catch (std::exception &ex) {
        std::cerr << ex.what();
    }
}
