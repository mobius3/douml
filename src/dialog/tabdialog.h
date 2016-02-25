#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include "QScrollArea"
class QHBoxLayout;
class TabDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TabDialog(QWidget * parent = 0, QString name = QString(), bool modal = false, Qt::WidgetAttribute f = Qt::WA_Disabled);
    void addTab(QWidget* tabWidget, QString name);
    void removePage(QWidget* page);
    void setOkButton(QString name);
    void setCancelButton(QString name);
    void setHelpButton(QString name);
    void showPage(QWidget* page);
    void setCaption(QString cap);
    bool hasOkButton( ) {return (m_okButton != NULL);}

    void insertTab(QWidget *tabWidget, QString name, int index);

    QTabBar *tabBar(){ return m_tabWidget->tabBar();}

    void setTabEnabled(QWidget *w, bool isEnabled);
signals:
    void currentChanged(QWidget *);
    void helpButtonPressed();
public slots:
    void onCurrentTabChanged(int i);
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
