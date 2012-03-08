#ifndef EDGEMENUFACTORY_H
#define EDGEMENUFACTORY_H
#include <QObject>
#include <QToolBar>

#include "boost/functional/factory.hpp"
#include <functional>
#include <QMap>

//#include <pair>


struct Orientationvariables
{
    int orientation;
    std::map<std::pair<int,QString>, QString> iconNames;
};


class EdgeMenuFactory : public QObject
{
    Q_OBJECT
public:
    EdgeMenuFactory();
    virtual ~EdgeMenuFactory();
    CreateEdgeMenu(uint, uint);

public slots:
    void OnEdgeMenuRequested(uint classID, uint orientation);

    QMap<uint,boost::function<QToolBar*(uint)> > factories;
    QMap<uint, QToolBar*> createdToolbars;
    QMap<uint, QToolBar*> menus;
    QMap<int, Orientationvariables> orientationSwitch;

};




#endif // EDGEMENUFACTORY_H
