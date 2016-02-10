#include "vvbox.h"

VVBox::VVBox(QWidget *parent) :
    QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    this->setLayout(m_layout);
    m_layout->setSpacing(2);
    m_layout->setMargin(2);
}

void VVBox::addWidget(QWidget *widget)
{
    m_layout->addWidget(widget);
}
bool VVBox::setStretchFactor(QWidget *w, int stretch)
{
    if(m_layout->indexOf(w) == -1)
        m_layout->addWidget(w);
    m_layout->setStretchFactor(w, stretch);
    return 0;
}
void VVBox::setMargin(int margin)
{
    m_layout->setMargin(margin);
}
