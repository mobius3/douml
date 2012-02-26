#ifndef GRIDCONVERTER_H
#define GRIDCONVERTER_H

#include <QWidget>
#include <Q3Grid>
#include <QGridLayout>
#include <QLabel>
#include "../data/HaveKeyValueData.h"
#include "../dialog/KeyValueTable.h"
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

    static QWidget* InitNewGrid(QWidget*, int columns);
    static QWidget* InitNewHBox(QWidget*);

    static QWidget* PlaceWidget(QWidget* parent, QWidget* grid);
    static QWidget* PlaceWidget(KeyValuesTable* data,  QWidget* grid);
    static QWidget* PlaceVertical(QWidget* parent, QWidget* grid);
    static QWidget* PlaceHorizontal(QWidget* parent, QWidget* grid);
    static QWidget* PlaceVertical(QWidget* parent);
    static QWidget* PlaceHorizontal(QWidget* parent);



    static QList<GridDataStack> grids;
};

//struct Grid

#endif // GRIDCONVERTER_H
