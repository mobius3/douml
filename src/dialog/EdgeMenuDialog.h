#ifndef EDGEMENUDIALOG_H
#define EDGEMENUDIALOG_H
#include <Q3TabDialog>
#include <QWidget>

unsigned int ClosestEdge(QWidget*, QPoint);
class BrowserNode;

class EdgeMenuDialog : public Q3TabDialog
{
Q_OBJECT
public:
    EdgeMenuDialog(QWidget * parent = 0, const char * name = 0, bool modal = false, Qt::WindowFlags f = 0);
    virtual ~EdgeMenuDialog();

    virtual void InitGui() = 0;

protected:
    virtual uint TypeID() = 0;

    virtual void leaveEvent ( QEvent * event );
    void showEvent ( QShowEvent * event );
    virtual void SetDialogMode(bool _isWritable);

    bool isWritable;

    virtual BrowserNode * GetCurrentNode() = 0;
    virtual void SaveData() = 0;
    virtual void FillGuiElements(BrowserNode *) = 0;



signals:
    void edgeMenuRequested(uint);

public slots:
    virtual void OnPickNextSibling();
    virtual void OnPickPreviousSibling();


};

#endif // EDGEMENUDIALOG_H
