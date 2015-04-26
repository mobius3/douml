#ifndef VGRIDBOX_H
#define VGRIDBOX_H

#include <QWidget>
#include <QGroupBox>
class QGridLayout;
class VGridBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit VGridBox(int n, QWidget *parent = 0,QString name = QString());
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
