#ifndef GRIDBOX_H
#define GRIDBOX_H

#include <QWidget>
#include <QGroupBox>
class QGridLayout;
class GridBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit GridBox(int n, QWidget *parent = 0,QString name = QString());
    void setMargin(int mar);
    void setSpacing(int spacing);
    void addWidget(QWidget *widget);
    QString name(QString name = QString());

signals:

public slots:
private:
    QGridLayout *m_layout;
    int m_numCols;
    int currentIndex;
};

#endif // GRIDBOX_H
