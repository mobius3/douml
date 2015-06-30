#ifndef HHBOX_H
#define HHBOX_H

#include <QWidget>
#include <QHBoxLayout>
class HHBox : public QWidget
{
    Q_OBJECT
public:
    explicit HHBox(QWidget *parent = 0, QString name= QString());
    void addWidget(QWidget* widget);
    bool setStretchFactor(QWidget *w, int stretch);
    void setMargin(int margin);

signals:

public slots:
private:
    QHBoxLayout *m_layout;
};

#endif // HHBOX_H
