#include "bbuttongroup.h"

BButtonGroup::BButtonGroup(QWidget *parent) :
    QGroupBox(parent)
{
    m_hLayout = 0;
    m_vLayout = 0;
    m_orientation = Qt::Horizontal;
    m_hLayout = new QHBoxLayout(this);
    this->setLayout(m_hLayout);
    m_hLayout->setSpacing(0);
    m_hLayout->setMargin(0);
}

BButtonGroup::BButtonGroup(const QString &title, QWidget *parent):
    QGroupBox(title, parent)
{
    m_hLayout = 0;
    m_vLayout = 0;
    m_orientation = Qt::Horizontal;
    m_hLayout = new QHBoxLayout(this);
    this->setLayout(m_hLayout);
    m_hLayout->setSpacing(0);
    m_hLayout->setMargin(0);
}

BButtonGroup::BButtonGroup(int strips, Qt::Orientation orientation, const QString &title, QWidget *parent, QString):
QGroupBox(title, parent)
{
    Q_UNUSED(strips);
    
    m_hLayout = 0;
    m_vLayout = 0;
    m_orientation = orientation;
    if(orientation == Qt::Horizontal)
    {
        m_hLayout = new QHBoxLayout(this);
        this->setLayout(m_hLayout);
        m_hLayout->setSpacing(0);
        m_hLayout->setMargin(0);
    }
    else
    {
        m_vLayout = new QHBoxLayout(this);
        this->setLayout(m_vLayout);
        m_vLayout->setSpacing(0);
        m_vLayout->setMargin(0);
    }
}

void BButtonGroup::setExclusive(bool isEx)
{
    Q_UNUSED(isEx);
}

void BButtonGroup::addWidget(QWidget *widget)
{
    if(m_orientation == Qt::Horizontal)
    {
        m_hLayout->addWidget(widget);
    }
    else
    {
        m_vLayout->addWidget(widget);
    }
}
