#ifndef GRIDCONVERTER_H
#define GRIDCONVERTER_H

#include <QWidget>
#include <Q3Grid>
#include <QGridLayout>
#include <QLabel>
struct GridDataStack
{
    static QGridLayout* layout;
    static QWidget* parent;
    static int columnCounter;
    static int columns;
    static int rowCounter;
};


class GridConverter
{
public:
    GridConverter();
    ~GridConverter();

    static void InitNewGrid(QWidget*, int columns);
    static void operator()(QWidget* widget, Q3Grid* grid/*swallowed at this point*/)
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

    static QList<GridDataStack> grids;
};

//struct Grid

#endif // GRIDCONVERTER_H
