#ifndef VVBOX_H
#define VVBOX_H

#include <QWidget>
#include <QVBoxLayout>
class VVBox : public QWidget
{
    Q_OBJECT
public:
    explicit VVBox(QWidget *parent = 0);
    void addWidget(QWidget* widget);

    bool setStretchFactor(QWidget *w, int stretch);
    void setMargin(int margin);
signals:

public slots:
private:
    QVBoxLayout *m_layout;
};

#endif // VVBOX_H
