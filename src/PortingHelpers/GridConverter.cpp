#include "PortingHelpers/GridConverter.h"

QGridLayout* GridDataStack::layout = 0;
QWidget* GridDataStack::parent = 0;
int GridDataStack::columnCounter = 0;
int GridDataStack::columns = 0;
int GridDataStack::rowCounter = 0;
QList<GridDataStack> GridConverter::grids;
QWidget* GridConverter::PlaceWidget(QWidget* parent, QWidget* grid/*swallowed at this point*/)
{
    if(!grids.last().parent)
        return;
    bool columLimitReached = grids.last().columnCounter==1;
    if(columLimitReached)
    {
        grids.last().row++;
        grids.last().columnCounter = 0;
    }
    grids.last().layout->addWidget(grids.last().widget,grids.last().columnCounter, grids.last().row);
    grids.last().columnCounter++;
}

QWidget* GridConverter::PlaceWidget(HaveKeyValueData* data,  QWidget* grid)
{

}

QWidget* GridConverter::PlaceVertical(QWidget* parent, QWidget* grid)
{}
QWidget* GridConverter::PlaceHorizontal(QWidget* parent, QWidget* grid)
{}
QWidget* GridConverter::PlaceVertical(QWidget* parent)
{}
QWidget* GridConverter::PlaceHorizontal(QWidget* parent)
{}
QWidget* GridConverter::PlaceWidget(QWidget* parent,const char*, QWidget* grid)
{}
QWidget* GridConverter::InitNewGrid(QWidget * w, int _columns)
{
    grids.clear();
    grids.append(GridDataStack());
    grids.last().columns = _columns;
    grids.last().parent = w;
}


