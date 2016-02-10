#include "bbuttongroup.h"

BButtonGroup::BButtonGroup(QWidget *parent) :
    QGroupBox(parent)
{
    m_hLayout = 0;
    m_vLayout = 0;
    m_orientation = Qt::Horizontal;
    m_hLayout = new QHBoxLayout(this);
    this->setLayout(m_hLayout);
    m_hLayout->setSpacing(3);
    m_hLayout->setMargin(3);
    connect(&m_buttonGroup, SIGNAL(buttonClicked(int)), this, SIGNAL(clicked(int)));
}

BButtonGroup::BButtonGroup(const QString &title, QWidget *parent):
    QGroupBox(title, parent)
{
    m_hLayout = 0;
    m_vLayout = 0;
    m_orientation = Qt::Horizontal;
    m_hLayout = new QHBoxLayout(this);
    this->setLayout(m_hLayout);
    m_hLayout->setSpacing(3);
    m_hLayout->setMargin(3);
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
        m_hLayout->setSpacing(3);
        m_hLayout->setMargin(3);
    }
    else
    {
        m_vLayout = new QHBoxLayout(this);
        this->setLayout(m_vLayout);
        m_vLayout->setSpacing(3);
        m_vLayout->setMargin(3);
    }
}

void BButtonGroup::setExclusive(bool isEx)
{
    m_buttonGroup.setExclusive(isEx);
}

void BButtonGroup::addWidget(QAbstractButton *widget)
{
    m_buttonGroup.addButton(widget);
    if(m_orientation == Qt::Horizontal)
    {
        m_hLayout->addWidget((QWidget*)widget);
    }
    else
    {
        m_vLayout->addWidget((QWidget*)widget);
    }
}
