#include <QApplication>
#include <QWebView>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWebView *view = new QWebView();
     view->load(QUrl("http://acid3.acidtests.org/"));
//    view->load(QUrl("http://html5test.com/"));
    view->show();

    return app.exec();
} 
