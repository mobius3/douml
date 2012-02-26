#include "PortingHelpers/GridConverter.h"

QGridLayout* GridDataStack::layout = 0;
QWidget* GridDataStack::parent = 0;
int GridDataStack::columnCounter = 0;
int GridDataStack::columns = 0;
int GridDataStack::rowCounter = 0;
QList<GridDataStack> GridConverter::grids;
void GridConverter::operator()(QWidget* widget, int columns, Q3Grid* grid/*swallowed*/)
{
    if(!parent)
        return;
    bool columLimitReached = columnCounter==1;
    if(columLimitReached)
    {
        row++;
        columnCounter = 0;
    }
    layout->addWidget(widget,columnCounter, row);
    columnCounter++;
}

void GridConverter::InitNewGrid(QWidget * w, int _columns)
{
    grids.clear();
    grids.append(GridDataStack());
    grids.last().columns = _columns;
    grids.last().parent = w;
}


