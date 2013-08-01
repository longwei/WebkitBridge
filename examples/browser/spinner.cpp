#include <QDebug>
#include <QFileInfo>
#include <QLineEdit>
#include <QPainter>
#include <QTimerEvent>
#include "spinner.h"

static const int DELAY = 100;

Spinner::Spinner(QWidget *parent)
    : QWidget(parent), m_timerid(0), m_count(0)
{
}

Spinner::~Spinner()
{
}

// start spinner animation
void Spinner::setAnimation(bool on)
{
    if (animated()) {
        killTimer(m_timerid);
        m_timerid = 0;
    }

    if (on) {
        // start animation
        m_timerid = startTimer(DELAY);
        m_count = 0;
    }

    update();
}

// update animation
void Spinner::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerid) {
        m_count++;
        update();
    }
    QWidget::timerEvent(event);
}

// return reasonable size hint
QSize Spinner::sizeHint() const
{
    return QSize(24, 24);
}

// paint spinner
void Spinner::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    int cv = 208;
    QPen pen(QColor(cv, cv, cv), 2.0, Qt::SolidLine, Qt::RoundCap);
    p.setPen(pen);

    p.translate(width() / 2.0, height() / 2.0);

    double radius = qMin(width() / 2.0, height() / 2.0);

    double y1 = radius * 0.75;
    double y2 = radius * 0.50;

    // rotate animation
    if (m_timerid > 0) {
        p.rotate((m_count % 12) * 30.0);
    }

    // draw ticks
    for (int n=0; n<12; n++) {
        p.rotate(30.0);
        p.drawLine(0, (int)y1, 0, (int)y2);
        if (m_timerid > 0) {
            cv -= 16;
            pen.setColor(QColor(cv, cv, cv));
            p.setPen(pen);
        }
    }
}
