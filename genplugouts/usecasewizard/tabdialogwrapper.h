#ifndef TABDIALOGWRAPPER_H
#define TABDIALOGWRAPPER_H

#include <QDialog>
#include <QTabWidget>
#include "QScrollArea"
class QHBoxLayout;
class TabDialogWrapper : public QDialog
{
    Q_OBJECT
public:
    explicit TabDialogWrapper(QWidget * parent = 0, const char * name = 0, bool modal = false, Qt::WidgetAttribute f = Qt::WA_Disabled);
    void addTab(QWidget* tabWidget, QString name);
    void removePage(QWidget* page);
    void setOkButton(QString name = "Ok");
    void setCancelButton(QString name = "Cancel");
    void setHelpButton(QString name = "Help");
    void showPage(QWidget* page);
    void setCaption(QString cap);
    bool hasOkButton( ) {return (m_okButton != NULL);}

    void insertTab(QWidget *tabWidget, QString name, int index);

    QTabBar *tabBar(){ return m_tabWidget->tabBar();}

    void setTabEnabled(QWidget *w, bool isEnabled);
signals:
    void helpButtonPressed();
public slots:
private:
protected:
    QTabWidget* m_tabWidget;
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
    QPushButton *m_helpButton;
    QHBoxLayout *m_buttonLayout;
    QScrollArea m_scrollArea;

};

#endif // TABDIALOG_H
