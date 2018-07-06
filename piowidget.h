#ifndef PIOWIDGET_H
#define PIOWIDGET_H

#include <QWidget>
#include <QGroupBox>

class PioWidget : public QWidget
{
    Q_OBJECT
public:
    PioWidget(QWidget* parent = 0);
    ~PioWidget();

Q_SIGNALS:
    void requestSetDeviation(quint32 value);
    void requestSetUpper(quint32 value);
    void requestSetLower(quint32 value);
    void requestDoReset();

public slots:
    void showCurrentValue(quint32 value);
    void showDeviation(quint32 value);
    void showCurrentValuePlusDeviation(quint32 value);
    void showUpper(quint32 value);
    void showLower(quint32 value);
    void showUpperAlarm(quint32 value);
    void showLowerAlarm(quint32 value);

private:
    void onSetClicked();
    void setupUI();
    QGroupBox* creatInputBox();
    QGroupBox* creatOutputBox();
    struct PioWidgetPrivate;
    PioWidgetPrivate* d;
};

#endif // PIOWIDGET_H
