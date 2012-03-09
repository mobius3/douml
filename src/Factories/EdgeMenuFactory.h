#ifndef EDGEMENUFACTORY_H
#define EDGEMENUFACTORY_H
#include <QObject>
#include <QToolBar>
#include <functional>
#include <map>
#include <QMap>


#include "boost/functional/factory.hpp"
#include "misc/SingletonHolder.h"


//#include <pair>


struct Orientationvariables
{
    int orientation;
    std::map<std::pair<int,QString>, QString> iconNames;
};

typedef std::function<QToolBar*()>  ToolbarFactory;

QToolBar* CreateClassDialogMenu();

class EdgeMenuFactory : public QObject
{
    Q_OBJECT
public:
    EdgeMenuFactory();
    virtual ~EdgeMenuFactory();
    void SpawnEdgeMenu(uint);
    void AddFactory(uint, ToolbarFactory);

public slots:
    void OnEdgeMenuRequested(uint classID);

private :
    QMap<uint, ToolbarFactory > factories;
    QMap<uint, QToolBar*> createdToolbars;
    QMap<int, Orientationvariables> orientationSwitch;

};
BIND_TO_SELF_SINGLE(EdgeMenuFactory);


#endif // EDGEMENUFACTORY_H
