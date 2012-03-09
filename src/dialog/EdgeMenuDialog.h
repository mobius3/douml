#ifndef EDGEMENUDIALOG_H
#define EDGEMENUDIALOG_H
#include <Q3TabDialog>
#include <QWidget>
#include <QList>
#include <QHash>

unsigned int ClosestEdge(QWidget*, QPoint);
class BrowserNode;

class EdgeMenuDialog : public Q3TabDialog
{
Q_OBJECT
public:
    EdgeMenuDialog(QWidget * parent = 0, const char * name = 0, bool modal = false, Qt::WindowFlags f = 0);
    virtual ~EdgeMenuDialog();

    virtual void InitGui() = 0;

    bool IsConnectedToToolBar();
    void ConnectionToToolBarEstablished();
    void BreakConnectionToToolBar();

protected:
    virtual uint TypeID() = 0;

    virtual void leaveEvent ( QEvent * event );
    void showEvent ( QShowEvent * event );
    void wheelEvent ( QWheelEvent * event );

    virtual void RegisterTab(QString, QWidget*);
    virtual void HideTab(QString);
    virtual void ShowTab(QString);

    virtual void SetDialogMode(bool _isWritable);
    virtual BrowserNode * GetCurrentNode() = 0;
    virtual void SaveData() = 0;
    virtual void FillGuiElements(BrowserNode *) = 0;

    bool isWritable;
    QHash<QString, QWidget*> tabs;
    int currentTab;
    bool isConnectedToToolBar;


signals:
    void edgeMenuRequested(uint);

public slots:
    virtual void OnPickNextSibling();
    virtual void OnPickPreviousSibling();


};

#endif // EDGEMENUDIALOG_H
