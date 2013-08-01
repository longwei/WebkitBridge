#ifndef SPINNER_H
#define SPINNER_H

#include <QWidget>

class QPaintEvent;
class QTimerEvent;

class Spinner : public QWidget
{
    Q_OBJECT
public:

    Spinner(QWidget *parent=0);
    virtual ~Spinner();

    bool animated() const { return (m_timerid != 0); }
    void setAnimation(bool on);

    virtual QSize sizeHint() const;

private:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    int m_timerid;
    int m_count;
};

#endif // SPINNER_H
