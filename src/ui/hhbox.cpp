#include "hhbox.h"

HHBox::HHBox(QWidget *parent, QString name) :
    QWidget(parent)
{
    m_layout = new QHBoxLayout(this);
    this->setLayout(m_layout);
    m_layout->setSpacing(2);
    m_layout->setMargin(2);
    setObjectName(name);
}

void HHBox::addWidget(QWidget *widget)
{
    m_layout->addWidget(widget);
}

bool HHBox::setStretchFactor(QWidget *w, int stretch)
{
    //if not in layout
    if(m_layout->indexOf(w) == -1)
        m_layout->addWidget(w);
    m_layout->setStretchFactor(w, stretch);
    return 0;
}

void HHBox::setMargin(int margin)
{
    m_layout->setMargin(margin);
}
