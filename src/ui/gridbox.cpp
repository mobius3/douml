#include "gridbox.h"
#include <QGridLayout>
GridBox::GridBox(int n, QWidget * parent, QString name) :
    QGroupBox(name, parent)
{
    m_layout = new QGridLayout(this);
    setLayout(m_layout);
    m_numCols = n;
    currentIndex = 0;
    setSpacing(2);
    setMargin(2);
    if(!name.isEmpty())
        this->setObjectName(name);
}

void GridBox::setMargin(int mar)
{
    m_layout->setMargin(mar);
}

void GridBox::setSpacing(int spacing)
{
    m_layout->setSpacing(spacing);
}

void GridBox::addWidget(QWidget *widget)
{
    m_layout->addWidget(widget, currentIndex/m_numCols, currentIndex%m_numCols);
    currentIndex ++;
}

QString GridBox::name(QString name)
{
    if(objectName().isEmpty())
        setObjectName(name);
    return objectName();
}
