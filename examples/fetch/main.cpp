#include <iostream>
#include <QCoreApplication>
#include <QtNetwork>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    QNetworkAccessManager manager;

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " <url>" << std::endl;
        return 0;
    }

    QUrl url(app.arguments().value(1));
    QNetworkRequest request(url);

    QNetworkReply *reply = manager.get(request);
    app.connect(reply, SIGNAL(finished()), SLOT(quit()));
    app.exec();

    QFile outfile("request.header");
    if (outfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&outfile);
        QList<QByteArray> list = reply->rawHeaderList();
        foreach (QByteArray name, list) {
            stream << name << ": " << reply->rawHeader(name) << endl;
        }
        outfile.close();
    }

    outfile.setFileName("request.data");
    if (outfile.open(QIODevice::WriteOnly)) {
        outfile.write(reply->readAll());
        outfile.close();
    }

    delete reply;
}
