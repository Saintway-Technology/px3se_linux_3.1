#include "basewidget.h"

#include <QStyleOption>
#include <QPainter>
#include <QPalette>

static int _id_widget = 0;

BaseWidget::BaseWidget(QWidget *parent) : QWidget(parent)
  , m_objectId(-1)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setMouseTracking(true);
}

void BaseWidget::paintEvent(QPaintEvent *)
{
    /* Slove the problem which 'setStyleSheet' and 'Q_OBJECT' can co-exist
       The below code used to repaint widgets when change became. */
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void BaseWidget::setBackgroundColor(int rValue, int gValue, int bValue)
{
    if (m_objectId == -1) {
        _id_widget++;
        m_objectId = _id_widget;
        setObjectName(QString::number(m_objectId));
    }

    QString styleStr;

    styleStr.append("#").append(QString::number(m_objectId)).append("{background-color:rgb(")
            .append(QString::number(rValue)).append(",")
            .append(QString::number(gValue)).append(",")
            .append(QString::number(bValue)).append(");")
            .append("}");

    setStyleSheet(styleStr);
}

void BaseWidget::setTextColorWhite()
{
    setStyleSheet("QLabel{color:white;}");
}

void BaseWidget::setTextColorBlack()
{
}

void BaseWidget::setWidgetFontBold(QWidget *widget)
{
    QFont font = widget->font();
    font.setBold(true);
    widget->setFont(font);
}

void BaseWidget::setWidgetFontSize(QWidget *widget, int size)
{
    QFont font = widget->font();
    font.setPixelSize(size);
    widget->setFont(font);
}

void BaseWidget::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}

void BaseWidget::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *e)
{
    QWidget::mouseReleaseEvent(e);
}
