#ifndef EDGEMENUFACTORY_H
#define EDGEMENUFACTORY_H
#include <QObject>
#include <QToolBar>
#include <functional>
#include <map>
#include <QMap>

#include "misc/SingletonHolder.h"


//#include <pair>
class EdgeMenuDialog;

struct Orientationvariables
{
    int orientation;
    //std::map<std::pair<int,QString>, QString> iconNames;
};

typedef std::function<QToolBar*()>  ToolbarFactory;

QToolBar* CreateClassDialogMenu();

class EdgeMenuFactory : public QObject
{
    Q_OBJECT
public:
    EdgeMenuFactory();
    virtual ~EdgeMenuFactory();

    void AddFactory(uint, ToolbarFactory);
    void SpawnEdgeMenu(uint, EdgeMenuDialog*,  QPoint);
public slots:
    void OnEdgeMenuRequested(uint classID);

private :
    QMap<uint, ToolbarFactory > factories;
    QMap<uint, QToolBar*> createdToolbars;
    QMap<int, Orientationvariables> orientationSwitch;
    void SpawnEdgeMenu(uint, EdgeMenuDialog*);

};
BIND_TO_SELF_SINGLE(EdgeMenuFactory);


#endif // EDGEMENUFACTORY_H
