#include <QApplication>
#include "common/mainwindow.h"

int main(int argc, char *argv[]) {
    try {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    } catch (Poco::Exception &ex) {
        std::cerr << ex.displayText();
    } catch (std::exception &ex) {
        std::cerr << ex.what();
    }
}
