#ifndef EDGEMENUDIALOG_H
#define EDGEMENUDIALOG_H
#include <Q3TabDialog>
#include <QWidget>

unsigned int ClosestEdge(QWidget*, QPoint);

class EdgeMenuDialog : public Q3TabDialog
{
Q_OBJECT
public:
    EdgeMenuDialog(QWidget * parent = 0, const char * name = 0, bool modal = false, Qt::WindowFlags f = 0);
    virtual ~EdgeMenuDialog();

    virtual void InitGui() = 0;
//    void FillGuiElements(BrowserNode*) = 0;
//    template <typename T>
//    void FillGuiElements(T *)
//    {
//        Q_ASSERT_X(0, "InitElements", "Attempt to use default function."
//                   "You must create an overload in inheriting class");
//    }



protected:
    virtual uint TypeID() = 0;

    virtual void leaveEvent ( QEvent * event );

    virtual void SetDialogMode(bool _isWritable);

    bool isWritable;



signals:
    void edgeMenuRequested(uint);

};

#endif // EDGEMENUDIALOG_H
