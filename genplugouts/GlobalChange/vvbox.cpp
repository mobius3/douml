#include "vvbox.h"

VVBox::VVBox(QWidget *parent) :
    QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    this->setLayout(m_layout);
    m_layout->setSpacing(0);
    m_layout->setMargin(0);
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
}
void VVBox::setMargin(int margin)
{
    m_layout->setMargin(margin);
}
