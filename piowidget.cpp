#include "piowidget.h"

#include <QtWidgets>

struct PioWidget::PioWidgetPrivate {
    QList<QLineEdit*> inEdits;
    QList<QToolButton*> inButtons;
    QList<QLineEdit*> outEdits;
    QToolButton* resetButton;
};

PioWidget::PioWidget(QWidget* parent)
    : QWidget(parent)
    , d(new PioWidgetPrivate)
{
    this->setupUI();
}

PioWidget::~PioWidget()
{
    delete d;
}

void PioWidget::showCurrentValue(quint32 value)
{
    d->outEdits[0]->setText(QString::number(value));
}

void PioWidget::showDeviation(quint32 value)
{
    d->outEdits[1]->setText(QString::number(value));
}

void PioWidget::showCurrentValuePlusDeviation(quint32 value)
{
    d->outEdits[2]->setText(QString::number(value));
}

void PioWidget::showUpper(quint32 value)
{
    d->outEdits[3]->setText(QString::number(value));
}

void PioWidget::showLower(quint32 value)
{
    d->outEdits[4]->setText(QString::number(value));
}

void PioWidget::showUpperAlarm(quint32 value)
{
    d->outEdits[5]->setText(QString::number(value));
}

void PioWidget::showLowerAlarm(quint32 value)
{
    d->outEdits[6]->setText(QString::number(value));
}


void PioWidget::onSetClicked()
{
    QToolButton* btn = qobject_cast<QToolButton*>(sender());
    int index = d->inButtons.indexOf(btn);
    quint32 value = d->inEdits[index]->text().toUInt();
    switch (index) {
    case 0: emit requestSetDeviation(value); break;
    case 1: emit requestSetUpper(value); break;
    case 2: emit requestSetLower(value); break;
    default:
        break;
    }
}


void PioWidget::setupUI()
{
     QGroupBox* boxIn = this->creatInputBox();
     QGroupBox* boxOut = this->creatOutputBox();

     QVBoxLayout* layout = new QVBoxLayout;
     layout->addStretch(1);
     layout->addWidget(boxIn);
     layout->addWidget(boxOut);
     layout->addStretch(1);
     this->setLayout(layout);
}


QGroupBox* PioWidget::creatInputBox()
{
    QGroupBox* box = new QGroupBox(QStringLiteral("输入"), this);
    QGridLayout* grid = new QGridLayout(box);
    int row = 0;

    QStringList names;
    names << QStringLiteral("补偿值")
          << QStringLiteral("上限值")
          << QStringLiteral("下限值");

    foreach (QString name, names) {
        QLineEdit* edit = new QLineEdit(this);
        edit->setFixedHeight(26);
        QToolButton* btn = new QToolButton(this);
        btn->setFixedHeight(24);
        btn->setText("SET");

        grid->addWidget(new QLabel(name + ":", this), row, 0, Qt::AlignRight);
        grid->addWidget(edit, row, 1);
        grid->addWidget(btn, row++, 2);
        d->inEdits.append(edit);
        d->inButtons.append(btn);

        connect(btn, &QToolButton::clicked, this, &PioWidget::onSetClicked);
    }

    d->resetButton = new QToolButton(this);
    d->resetButton->setFixedSize(100, 28);
    d->resetButton->setText("Reset");
    connect(d->resetButton, &QToolButton::clicked, this, &PioWidget::requestDoReset);
    grid->addWidget(d->resetButton, row++, 1);
    return box;
}

QGroupBox* PioWidget::creatOutputBox()
{
    QGroupBox* box = new QGroupBox(QStringLiteral("输出"), this);
    QGridLayout* grid = new QGridLayout(box);
    int row = 0;

    QStringList names;
    names << QStringLiteral("测量值")
          << QStringLiteral("补偿值")
          << QStringLiteral("显示值")
          << QStringLiteral("上限值")
          << QStringLiteral("下限值")
          << QStringLiteral("上限报警")
          << QStringLiteral("下限报警");

    foreach (QString name, names) {
        QLineEdit* edit = new QLineEdit(this);
        edit->setFixedHeight(26);
        grid->addWidget(new QLabel(name + ":", this), row, 0, Qt::AlignRight);
        grid->addWidget(edit, row++, 1);
        d->outEdits.append(edit);
    }
    return box;
}
