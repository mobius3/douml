#ifndef EDGEMENUFACTORY_H
#define EDGEMENUFACTORY_H
#include <QObject>
#include <QToolBar>

#include "boost/functional/factory.hpp"
#include <functional>
#include <map>
#include <QMap>

//#include <pair>


struct Orientationvariables
{
    int orientation;
    std::map<std::pair<int,QString>, QString> iconNames;
};

typedef std::function<QToolBar*(uint)>  ToolbarFactory;


class EdgeMenuFactory : public QObject
{
    Q_OBJECT
public:
    EdgeMenuFactory();
    virtual ~EdgeMenuFactory();
    void CreateEdgeMenu(uint, uint _orientation);

public slots:
    void OnEdgeMenuRequested(uint classID, uint orientation);

private :
    QMap<uint,ToolbarFactory > factories;
    QMap<uint, QToolBar*> createdToolbars;
    QMap<uint, QToolBar*> menus;
    QMap<int, Orientationvariables> orientationSwitch;

};




#endif // EDGEMENUFACTORY_H
