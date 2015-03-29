#include "vgridbox.h"
#include <QGridLayout>
VGridBox::VGridBox(int n, QWidget * parent, QString name) :
    QGroupBox(name, parent)
{
    m_layout = new QGridLayout(this);
    setLayout(m_layout);
    m_numCols = n;
    currentIndex = 0;
    setSpacing(0);
    setMargin(0);
    if(!name.isEmpty())
        this->setObjectName(name);
}

void VGridBox::setMargin(int mar)
{
    m_layout->setMargin(mar);
}

void VGridBox::setSpacing(int spacing)
{
    m_layout->setSpacing(spacing);
}

void VGridBox::addWidget(QWidget *widget)
{
    m_layout->addWidget(widget, currentIndex%m_numCols, currentIndex/m_numCols);
    currentIndex ++;
}

QString VGridBox::name(QString name)
{
    if(objectName().isEmpty())
        setObjectName(name);
    return objectName();
}
