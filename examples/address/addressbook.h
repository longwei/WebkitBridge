#include <QWidget>
#include "ui_addressbook.h"

class AddressBook : public QWidget, public Ui::AddressBook
{
    Q_OBJECT
public:
    AddressBook(QWidget *parent=0);
    ~AddressBook();

public slots:
    void onRefreshClicked();
};
