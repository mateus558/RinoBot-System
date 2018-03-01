/********************************************************************************
** Form generated from reading UI file 'informationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFORMATIONWINDOW_H
#define UI_INFORMATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InformationWindow
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *imgLeonalbl;
    QLabel *imgPrestolbl;
    QLabel *imgGandalflbl;
    QLabel *channelGandalflbl;
    QLabel *velocityGandalflbl;
    QLabel *channelLeonalbl;
    QLabel *velocityLeonalbl;
    QLabel *channelPrestolbl;
    QLabel *velocityPrestolbl;
    QLabel *pidlbl;
    QLabel *velocityMaxGandalflbl;
    QLabel *velocityMaxLeonalbl;
    QLabel *velocityMaxPrestolbl;
    QPushButton *pidbtn;
    QPushButton *velocityMaxGandalfbtn;
    QPushButton *velocityMaxLeonabtn;
    QPushButton *velocityMaxPrestobtn;
    QLabel *strategylbl;
    QComboBox *strategycbx;
    QPushButton *strategybtn;
    QLabel *gandalflbl;
    QLabel *leonalbl;
    QLabel *prestolbl;
    QLabel *label_39;
    QDoubleSpinBox *velocityMaxGandalfspb;
    QDoubleSpinBox *velocityMaxLeonaspb;
    QDoubleSpinBox *velocityMaxPrestospb;
    QDoubleSpinBox *pidspb;
    QLabel *currentStrategylbl;
    QWidget *tab_2;
    QLabel *velocityPrestolbl_2;
    QLabel *imgLeonalbl_2;
    QLabel *velocityGandalflbl_2;
    QLabel *velocityLeonalbl_2;
    QLabel *imgGandalflbl_2;
    QLabel *positionGandalflbl;
    QLabel *positionPrestolbl;
    QLabel *positionLeonalbl;
    QLabel *imgPrestolbl_2;
    QLabel *velocityBalllbl;
    QLabel *imgBalllbl;
    QLabel *positionBalllbl;
    QLabel *leonalbl_2;
    QLabel *prestolbl_2;
    QLabel *gandalflbl_2;
    QLabel *balllbl;
    QPushButton *startFilterbtn;
    QLabel *chopFrequencylbl;
    QDoubleSpinBox *filterspb;
    QPushButton *valueFilterchangebtn;
    QLabel *frequencyFilterlbl;

    void setupUi(QDialog *InformationWindow)
    {
        if (InformationWindow->objectName().isEmpty())
            InformationWindow->setObjectName(QStringLiteral("InformationWindow"));
        InformationWindow->resize(771, 439);
        tabWidget = new QTabWidget(InformationWindow);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 771, 441));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        imgLeonalbl = new QLabel(tab);
        imgLeonalbl->setObjectName(QStringLiteral("imgLeonalbl"));
        imgLeonalbl->setGeometry(QRect(10, 140, 81, 81));
        imgPrestolbl = new QLabel(tab);
        imgPrestolbl->setObjectName(QStringLiteral("imgPrestolbl"));
        imgPrestolbl->setGeometry(QRect(10, 270, 81, 81));
        imgGandalflbl = new QLabel(tab);
        imgGandalflbl->setObjectName(QStringLiteral("imgGandalflbl"));
        imgGandalflbl->setGeometry(QRect(10, 10, 81, 81));
        channelGandalflbl = new QLabel(tab);
        channelGandalflbl->setObjectName(QStringLiteral("channelGandalflbl"));
        channelGandalflbl->setGeometry(QRect(100, 30, 131, 31));
        velocityGandalflbl = new QLabel(tab);
        velocityGandalflbl->setObjectName(QStringLiteral("velocityGandalflbl"));
        velocityGandalflbl->setGeometry(QRect(100, 60, 131, 31));
        channelLeonalbl = new QLabel(tab);
        channelLeonalbl->setObjectName(QStringLiteral("channelLeonalbl"));
        channelLeonalbl->setGeometry(QRect(100, 150, 141, 31));
        velocityLeonalbl = new QLabel(tab);
        velocityLeonalbl->setObjectName(QStringLiteral("velocityLeonalbl"));
        velocityLeonalbl->setGeometry(QRect(100, 180, 141, 31));
        channelPrestolbl = new QLabel(tab);
        channelPrestolbl->setObjectName(QStringLiteral("channelPrestolbl"));
        channelPrestolbl->setGeometry(QRect(100, 280, 141, 31));
        velocityPrestolbl = new QLabel(tab);
        velocityPrestolbl->setObjectName(QStringLiteral("velocityPrestolbl"));
        velocityPrestolbl->setGeometry(QRect(100, 310, 141, 31));
        pidlbl = new QLabel(tab);
        pidlbl->setObjectName(QStringLiteral("pidlbl"));
        pidlbl->setGeometry(QRect(440, 30, 63, 31));
        velocityMaxGandalflbl = new QLabel(tab);
        velocityMaxGandalflbl->setObjectName(QStringLiteral("velocityMaxGandalflbl"));
        velocityMaxGandalflbl->setGeometry(QRect(100, 90, 171, 31));
        velocityMaxLeonalbl = new QLabel(tab);
        velocityMaxLeonalbl->setObjectName(QStringLiteral("velocityMaxLeonalbl"));
        velocityMaxLeonalbl->setGeometry(QRect(100, 210, 141, 31));
        velocityMaxPrestolbl = new QLabel(tab);
        velocityMaxPrestolbl->setObjectName(QStringLiteral("velocityMaxPrestolbl"));
        velocityMaxPrestolbl->setGeometry(QRect(100, 340, 141, 31));
        pidbtn = new QPushButton(tab);
        pidbtn->setObjectName(QStringLiteral("pidbtn"));
        pidbtn->setGeometry(QRect(640, 30, 71, 36));
        velocityMaxGandalfbtn = new QPushButton(tab);
        velocityMaxGandalfbtn->setObjectName(QStringLiteral("velocityMaxGandalfbtn"));
        velocityMaxGandalfbtn->setGeometry(QRect(330, 90, 71, 36));
        velocityMaxLeonabtn = new QPushButton(tab);
        velocityMaxLeonabtn->setObjectName(QStringLiteral("velocityMaxLeonabtn"));
        velocityMaxLeonabtn->setGeometry(QRect(330, 210, 71, 36));
        velocityMaxPrestobtn = new QPushButton(tab);
        velocityMaxPrestobtn->setObjectName(QStringLiteral("velocityMaxPrestobtn"));
        velocityMaxPrestobtn->setGeometry(QRect(330, 340, 71, 36));
        strategylbl = new QLabel(tab);
        strategylbl->setObjectName(QStringLiteral("strategylbl"));
        strategylbl->setGeometry(QRect(440, 130, 91, 31));
        strategycbx = new QComboBox(tab);
        strategycbx->setObjectName(QStringLiteral("strategycbx"));
        strategycbx->setGeometry(QRect(530, 130, 103, 36));
        strategybtn = new QPushButton(tab);
        strategybtn->setObjectName(QStringLiteral("strategybtn"));
        strategybtn->setGeometry(QRect(640, 130, 71, 36));
        gandalflbl = new QLabel(tab);
        gandalflbl->setObjectName(QStringLiteral("gandalflbl"));
        gandalflbl->setGeometry(QRect(10, 100, 63, 20));
        leonalbl = new QLabel(tab);
        leonalbl->setObjectName(QStringLiteral("leonalbl"));
        leonalbl->setGeometry(QRect(10, 220, 63, 20));
        prestolbl = new QLabel(tab);
        prestolbl->setObjectName(QStringLiteral("prestolbl"));
        prestolbl->setGeometry(QRect(10, 350, 63, 20));
        label_39 = new QLabel(tab);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(170, 0, 63, 20));
        velocityMaxGandalfspb = new QDoubleSpinBox(tab);
        velocityMaxGandalfspb->setObjectName(QStringLiteral("velocityMaxGandalfspb"));
        velocityMaxGandalfspb->setGeometry(QRect(270, 90, 81, 36));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(velocityMaxGandalfspb->sizePolicy().hasHeightForWidth());
        velocityMaxGandalfspb->setSizePolicy(sizePolicy);
        velocityMaxGandalfspb->setFocusPolicy(Qt::WheelFocus);
        velocityMaxGandalfspb->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        velocityMaxGandalfspb->setButtonSymbols(QAbstractSpinBox::NoButtons);
        velocityMaxLeonaspb = new QDoubleSpinBox(tab);
        velocityMaxLeonaspb->setObjectName(QStringLiteral("velocityMaxLeonaspb"));
        velocityMaxLeonaspb->setGeometry(QRect(270, 210, 81, 36));
        sizePolicy.setHeightForWidth(velocityMaxLeonaspb->sizePolicy().hasHeightForWidth());
        velocityMaxLeonaspb->setSizePolicy(sizePolicy);
        velocityMaxLeonaspb->setFocusPolicy(Qt::WheelFocus);
        velocityMaxLeonaspb->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        velocityMaxLeonaspb->setButtonSymbols(QAbstractSpinBox::NoButtons);
        velocityMaxPrestospb = new QDoubleSpinBox(tab);
        velocityMaxPrestospb->setObjectName(QStringLiteral("velocityMaxPrestospb"));
        velocityMaxPrestospb->setGeometry(QRect(270, 340, 81, 36));
        sizePolicy.setHeightForWidth(velocityMaxPrestospb->sizePolicy().hasHeightForWidth());
        velocityMaxPrestospb->setSizePolicy(sizePolicy);
        velocityMaxPrestospb->setFocusPolicy(Qt::WheelFocus);
        velocityMaxPrestospb->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        velocityMaxPrestospb->setButtonSymbols(QAbstractSpinBox::NoButtons);
        pidspb = new QDoubleSpinBox(tab);
        pidspb->setObjectName(QStringLiteral("pidspb"));
        pidspb->setGeometry(QRect(580, 30, 81, 36));
        sizePolicy.setHeightForWidth(pidspb->sizePolicy().hasHeightForWidth());
        pidspb->setSizePolicy(sizePolicy);
        pidspb->setFocusPolicy(Qt::WheelFocus);
        pidspb->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pidspb->setButtonSymbols(QAbstractSpinBox::NoButtons);
        currentStrategylbl = new QLabel(tab);
        currentStrategylbl->setObjectName(QStringLiteral("currentStrategylbl"));
        currentStrategylbl->setGeometry(QRect(440, 190, 301, 20));
        tabWidget->addTab(tab, QString());
        imgLeonalbl->raise();
        imgPrestolbl->raise();
        imgGandalflbl->raise();
        channelGandalflbl->raise();
        velocityGandalflbl->raise();
        channelLeonalbl->raise();
        velocityLeonalbl->raise();
        channelPrestolbl->raise();
        velocityPrestolbl->raise();
        pidlbl->raise();
        velocityMaxGandalflbl->raise();
        velocityMaxLeonalbl->raise();
        velocityMaxPrestolbl->raise();
        strategylbl->raise();
        strategycbx->raise();
        strategybtn->raise();
        gandalflbl->raise();
        leonalbl->raise();
        prestolbl->raise();
        label_39->raise();
        velocityMaxGandalfspb->raise();
        velocityMaxLeonaspb->raise();
        velocityMaxPrestospb->raise();
        pidspb->raise();
        currentStrategylbl->raise();
        velocityMaxGandalfbtn->raise();
        velocityMaxLeonabtn->raise();
        pidbtn->raise();
        velocityMaxPrestobtn->raise();
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        velocityPrestolbl_2 = new QLabel(tab_2);
        velocityPrestolbl_2->setObjectName(QStringLiteral("velocityPrestolbl_2"));
        velocityPrestolbl_2->setGeometry(QRect(100, 350, 161, 31));
        imgLeonalbl_2 = new QLabel(tab_2);
        imgLeonalbl_2->setObjectName(QStringLiteral("imgLeonalbl_2"));
        imgLeonalbl_2->setGeometry(QRect(10, 140, 81, 81));
        velocityGandalflbl_2 = new QLabel(tab_2);
        velocityGandalflbl_2->setObjectName(QStringLiteral("velocityGandalflbl_2"));
        velocityGandalflbl_2->setGeometry(QRect(100, 90, 141, 31));
        velocityLeonalbl_2 = new QLabel(tab_2);
        velocityLeonalbl_2->setObjectName(QStringLiteral("velocityLeonalbl_2"));
        velocityLeonalbl_2->setGeometry(QRect(100, 210, 151, 31));
        imgGandalflbl_2 = new QLabel(tab_2);
        imgGandalflbl_2->setObjectName(QStringLiteral("imgGandalflbl_2"));
        imgGandalflbl_2->setGeometry(QRect(10, 10, 81, 81));
        positionGandalflbl = new QLabel(tab_2);
        positionGandalflbl->setObjectName(QStringLiteral("positionGandalflbl"));
        positionGandalflbl->setGeometry(QRect(100, 40, 141, 31));
        positionPrestolbl = new QLabel(tab_2);
        positionPrestolbl->setObjectName(QStringLiteral("positionPrestolbl"));
        positionPrestolbl->setGeometry(QRect(100, 300, 141, 31));
        positionLeonalbl = new QLabel(tab_2);
        positionLeonalbl->setObjectName(QStringLiteral("positionLeonalbl"));
        positionLeonalbl->setGeometry(QRect(100, 160, 131, 31));
        imgPrestolbl_2 = new QLabel(tab_2);
        imgPrestolbl_2->setObjectName(QStringLiteral("imgPrestolbl_2"));
        imgPrestolbl_2->setGeometry(QRect(10, 270, 81, 81));
        velocityBalllbl = new QLabel(tab_2);
        velocityBalllbl->setObjectName(QStringLiteral("velocityBalllbl"));
        velocityBalllbl->setGeometry(QRect(430, 90, 161, 31));
        imgBalllbl = new QLabel(tab_2);
        imgBalllbl->setObjectName(QStringLiteral("imgBalllbl"));
        imgBalllbl->setGeometry(QRect(340, 10, 81, 81));
        positionBalllbl = new QLabel(tab_2);
        positionBalllbl->setObjectName(QStringLiteral("positionBalllbl"));
        positionBalllbl->setGeometry(QRect(430, 40, 131, 31));
        leonalbl_2 = new QLabel(tab_2);
        leonalbl_2->setObjectName(QStringLiteral("leonalbl_2"));
        leonalbl_2->setGeometry(QRect(10, 210, 63, 31));
        prestolbl_2 = new QLabel(tab_2);
        prestolbl_2->setObjectName(QStringLiteral("prestolbl_2"));
        prestolbl_2->setGeometry(QRect(10, 350, 63, 31));
        gandalflbl_2 = new QLabel(tab_2);
        gandalflbl_2->setObjectName(QStringLiteral("gandalflbl_2"));
        gandalflbl_2->setGeometry(QRect(10, 90, 63, 31));
        balllbl = new QLabel(tab_2);
        balllbl->setObjectName(QStringLiteral("balllbl"));
        balllbl->setGeometry(QRect(340, 90, 63, 31));
        startFilterbtn = new QPushButton(tab_2);
        startFilterbtn->setObjectName(QStringLiteral("startFilterbtn"));
        startFilterbtn->setGeometry(QRect(500, 150, 41, 31));
        chopFrequencylbl = new QLabel(tab_2);
        chopFrequencylbl->setObjectName(QStringLiteral("chopFrequencylbl"));
        chopFrequencylbl->setGeometry(QRect(340, 150, 121, 31));
        filterspb = new QDoubleSpinBox(tab_2);
        filterspb->setObjectName(QStringLiteral("filterspb"));
        filterspb->setGeometry(QRect(500, 190, 81, 36));
        sizePolicy.setHeightForWidth(filterspb->sizePolicy().hasHeightForWidth());
        filterspb->setSizePolicy(sizePolicy);
        filterspb->setFocusPolicy(Qt::WheelFocus);
        filterspb->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        filterspb->setButtonSymbols(QAbstractSpinBox::NoButtons);
        valueFilterchangebtn = new QPushButton(tab_2);
        valueFilterchangebtn->setObjectName(QStringLiteral("valueFilterchangebtn"));
        valueFilterchangebtn->setGeometry(QRect(560, 190, 71, 36));
        frequencyFilterlbl = new QLabel(tab_2);
        frequencyFilterlbl->setObjectName(QStringLiteral("frequencyFilterlbl"));
        frequencyFilterlbl->setGeometry(QRect(340, 190, 171, 31));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(InformationWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InformationWindow);
    } // setupUi

    void retranslateUi(QDialog *InformationWindow)
    {
        InformationWindow->setWindowTitle(QApplication::translate("InformationWindow", "Dialog", Q_NULLPTR));
        imgLeonalbl->setText(QApplication::translate("InformationWindow", "TextLabel", Q_NULLPTR));
        imgPrestolbl->setText(QApplication::translate("InformationWindow", "TextLabel", Q_NULLPTR));
        imgGandalflbl->setText(QApplication::translate("InformationWindow", "TextLabel", Q_NULLPTR));
        channelGandalflbl->setText(QApplication::translate("InformationWindow", "Canal:", Q_NULLPTR));
        velocityGandalflbl->setText(QApplication::translate("InformationWindow", "Speed:", Q_NULLPTR));
        channelLeonalbl->setText(QApplication::translate("InformationWindow", "Canal:", Q_NULLPTR));
        velocityLeonalbl->setText(QApplication::translate("InformationWindow", "Speed:", Q_NULLPTR));
        channelPrestolbl->setText(QApplication::translate("InformationWindow", "Canal:", Q_NULLPTR));
        velocityPrestolbl->setText(QApplication::translate("InformationWindow", "Speed:", Q_NULLPTR));
        pidlbl->setText(QApplication::translate("InformationWindow", "PID:", Q_NULLPTR));
        velocityMaxGandalflbl->setText(QApplication::translate("InformationWindow", "Speed M\303\241x:", Q_NULLPTR));
        velocityMaxLeonalbl->setText(QApplication::translate("InformationWindow", "Speed M\303\241x:", Q_NULLPTR));
        velocityMaxPrestolbl->setText(QApplication::translate("InformationWindow", "Speed M\303\241x:", Q_NULLPTR));
        pidbtn->setText(QApplication::translate("InformationWindow", "Change", Q_NULLPTR));
        velocityMaxGandalfbtn->setText(QApplication::translate("InformationWindow", "Change", Q_NULLPTR));
        velocityMaxGandalfbtn->setShortcut(QApplication::translate("InformationWindow", "F5", Q_NULLPTR));
        velocityMaxLeonabtn->setText(QApplication::translate("InformationWindow", "Change", Q_NULLPTR));
        velocityMaxPrestobtn->setText(QApplication::translate("InformationWindow", "Change", Q_NULLPTR));
        strategylbl->setText(QApplication::translate("InformationWindow", "Strategy:", Q_NULLPTR));
        strategycbx->clear();
        strategycbx->insertItems(0, QStringList()
         << QApplication::translate("InformationWindow", "2", Q_NULLPTR)
         << QApplication::translate("InformationWindow", "1", Q_NULLPTR)
         << QApplication::translate("InformationWindow", "Text", Q_NULLPTR)
        );
        strategybtn->setText(QApplication::translate("InformationWindow", "Change", Q_NULLPTR));
        gandalflbl->setText(QApplication::translate("InformationWindow", "Gandalf", Q_NULLPTR));
        leonalbl->setText(QApplication::translate("InformationWindow", "Leona", Q_NULLPTR));
        prestolbl->setText(QApplication::translate("InformationWindow", "Presto", Q_NULLPTR));
        label_39->setText(QApplication::translate("InformationWindow", "Robots", Q_NULLPTR));
        currentStrategylbl->setText(QApplication::translate("InformationWindow", "Current: ", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("InformationWindow", "Strategy", Q_NULLPTR));
        velocityPrestolbl_2->setText(QApplication::translate("InformationWindow", "Speed:", Q_NULLPTR));
        imgLeonalbl_2->setText(QApplication::translate("InformationWindow", "TextLabel", Q_NULLPTR));
        velocityGandalflbl_2->setText(QApplication::translate("InformationWindow", "Speed:", Q_NULLPTR));
        velocityLeonalbl_2->setText(QApplication::translate("InformationWindow", "Speed:", Q_NULLPTR));
        imgGandalflbl_2->setText(QApplication::translate("InformationWindow", "TextLabel", Q_NULLPTR));
        positionGandalflbl->setText(QApplication::translate("InformationWindow", "Posi\303\247\303\243o:", Q_NULLPTR));
        positionPrestolbl->setText(QApplication::translate("InformationWindow", "Posi\303\247\303\243o:", Q_NULLPTR));
        positionLeonalbl->setText(QApplication::translate("InformationWindow", "Posi\303\247\303\243o:", Q_NULLPTR));
        imgPrestolbl_2->setText(QApplication::translate("InformationWindow", "TextLabel", Q_NULLPTR));
        velocityBalllbl->setText(QApplication::translate("InformationWindow", "Speed:", Q_NULLPTR));
        imgBalllbl->setText(QApplication::translate("InformationWindow", "TextLabel", Q_NULLPTR));
        positionBalllbl->setText(QApplication::translate("InformationWindow", "Posi\303\247\303\243o:", Q_NULLPTR));
        leonalbl_2->setText(QApplication::translate("InformationWindow", "Leona", Q_NULLPTR));
        prestolbl_2->setText(QApplication::translate("InformationWindow", "Presto", Q_NULLPTR));
        gandalflbl_2->setText(QApplication::translate("InformationWindow", "Gandalf", Q_NULLPTR));
        balllbl->setText(QApplication::translate("InformationWindow", "Bola", Q_NULLPTR));
        startFilterbtn->setText(QApplication::translate("InformationWindow", "Off", Q_NULLPTR));
        chopFrequencylbl->setText(QApplication::translate("InformationWindow", "Chop Frequency:", Q_NULLPTR));
        valueFilterchangebtn->setText(QApplication::translate("InformationWindow", "Change", Q_NULLPTR));
        valueFilterchangebtn->setShortcut(QApplication::translate("InformationWindow", "F5", Q_NULLPTR));
        frequencyFilterlbl->setText(QApplication::translate("InformationWindow", "Frequency:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("InformationWindow", "Vision", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InformationWindow: public Ui_InformationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATIONWINDOW_H
