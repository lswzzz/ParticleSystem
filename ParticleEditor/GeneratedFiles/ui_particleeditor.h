/********************************************************************************
** Form generated from reading UI file 'particleeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTICLEEDITOR_H
#define UI_PARTICLEEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParticleEditorClass
{
public:
    QAction *actionAddRes;
    QAction *actionAddRes_2;
    QAction *actionAdd_Res;
    QAction *actionOpenConfig;
    QAction *actionSaveConfig;
    QAction *actionSave_as;
    QAction *actionOutput;
    QAction *actionControlView;
    QAction *actionResView;
    QAction *actionModelView;
    QWidget *centralWidget;
    QDockWidget *SceneWidget;
    QWidget *SceneWidgetContents;
    QDockWidget *LogWidget;
    QWidget *LogWidgetContents;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ParticleEditorClass)
    {
        if (ParticleEditorClass->objectName().isEmpty())
            ParticleEditorClass->setObjectName(QStringLiteral("ParticleEditorClass"));
        ParticleEditorClass->resize(1669, 866);
        ParticleEditorClass->setStyleSheet(QStringLiteral(""));
        actionAddRes = new QAction(ParticleEditorClass);
        actionAddRes->setObjectName(QStringLiteral("actionAddRes"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/Resources/add.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddRes->setIcon(icon);
        actionAddRes_2 = new QAction(ParticleEditorClass);
        actionAddRes_2->setObjectName(QStringLiteral("actionAddRes_2"));
        actionAdd_Res = new QAction(ParticleEditorClass);
        actionAdd_Res->setObjectName(QStringLiteral("actionAdd_Res"));
        actionAdd_Res->setIcon(icon);
        actionOpenConfig = new QAction(ParticleEditorClass);
        actionOpenConfig->setObjectName(QStringLiteral("actionOpenConfig"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/Resources/open.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenConfig->setIcon(icon1);
        actionSaveConfig = new QAction(ParticleEditorClass);
        actionSaveConfig->setObjectName(QStringLiteral("actionSaveConfig"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/Resources/save_as.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveConfig->setIcon(icon2);
        actionSave_as = new QAction(ParticleEditorClass);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionSave_as->setIcon(icon2);
        actionOutput = new QAction(ParticleEditorClass);
        actionOutput->setObjectName(QStringLiteral("actionOutput"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/Resources/output.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionOutput->setIcon(icon3);
        actionControlView = new QAction(ParticleEditorClass);
        actionControlView->setObjectName(QStringLiteral("actionControlView"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icon/Resources/show.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionControlView->setIcon(icon4);
        actionResView = new QAction(ParticleEditorClass);
        actionResView->setObjectName(QStringLiteral("actionResView"));
        actionResView->setIcon(icon4);
        actionModelView = new QAction(ParticleEditorClass);
        actionModelView->setObjectName(QStringLiteral("actionModelView"));
        actionModelView->setIcon(icon4);
        centralWidget = new QWidget(ParticleEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(" background-color:rgba(191, 191, 191, 191)"));
        SceneWidget = new QDockWidget(centralWidget);
        SceneWidget->setObjectName(QStringLiteral("SceneWidget"));
        SceneWidget->setEnabled(true);
        SceneWidget->setGeometry(QRect(0, 0, 960, 662));
        SceneWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        SceneWidgetContents = new QWidget();
        SceneWidgetContents->setObjectName(QStringLiteral("SceneWidgetContents"));
        SceneWidget->setWidget(SceneWidgetContents);
        LogWidget = new QDockWidget(centralWidget);
        LogWidget->setObjectName(QStringLiteral("LogWidget"));
        LogWidget->setGeometry(QRect(0, 665, 960, 140));
        LogWidget->setMinimumSize(QSize(960, 140));
        LogWidget->setStyleSheet(QStringLiteral(" background-color:rgba(191, 191, 191, 191)"));
        LogWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        LogWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
        LogWidgetContents = new QWidget();
        LogWidgetContents->setObjectName(QStringLiteral("LogWidgetContents"));
        plainTextEdit = new QPlainTextEdit(LogWidgetContents);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(0, 0, 960, 120));
        LogWidget->setWidget(LogWidgetContents);
        ParticleEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ParticleEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1669, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        ParticleEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ParticleEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ParticleEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ParticleEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ParticleEditorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionOpenConfig);
        menuFile->addAction(actionSaveConfig);
        menuFile->addAction(actionSave_as);
        menuFile->addAction(actionOutput);
        menuEdit->addAction(actionAdd_Res);
        menuView->addAction(actionControlView);
        menuView->addAction(actionResView);
        menuView->addAction(actionModelView);

        retranslateUi(ParticleEditorClass);

        QMetaObject::connectSlotsByName(ParticleEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *ParticleEditorClass)
    {
        ParticleEditorClass->setWindowTitle(QApplication::translate("ParticleEditorClass", "ParticleEditor", 0));
        actionAddRes->setText(QApplication::translate("ParticleEditorClass", "\346\267\273\345\212\240\350\265\204\346\272\220", 0));
        actionAddRes_2->setText(QApplication::translate("ParticleEditorClass", "add_Res", 0));
        actionAdd_Res->setText(QApplication::translate("ParticleEditorClass", "\346\267\273\345\212\240\350\265\204\346\272\220", 0));
        actionOpenConfig->setText(QApplication::translate("ParticleEditorClass", "\346\211\223\345\274\200", 0));
        actionSaveConfig->setText(QApplication::translate("ParticleEditorClass", "\344\277\235\345\255\230", 0));
        actionSave_as->setText(QApplication::translate("ParticleEditorClass", "\345\217\246\345\255\230\344\270\272", 0));
        actionOutput->setText(QApplication::translate("ParticleEditorClass", "\345\257\274\345\207\272", 0));
        actionControlView->setText(QApplication::translate("ParticleEditorClass", "\346\216\247\345\210\266\345\231\250\350\247\206\345\233\276", 0));
        actionResView->setText(QApplication::translate("ParticleEditorClass", "\350\265\204\346\272\220\350\247\206\345\233\276", 0));
        actionModelView->setText(QApplication::translate("ParticleEditorClass", "\346\250\241\345\236\213\350\247\206\345\233\276", 0));
        SceneWidget->setWindowTitle(QApplication::translate("ParticleEditorClass", "\347\274\226\350\276\221\345\231\250\350\247\206\345\233\276", 0));
        LogWidget->setWindowTitle(QApplication::translate("ParticleEditorClass", "\350\276\223\345\207\272\350\247\206\345\233\276", 0));
        menuFile->setTitle(QApplication::translate("ParticleEditorClass", "\346\226\207\344\273\266", 0));
        menuEdit->setTitle(QApplication::translate("ParticleEditorClass", "\347\274\226\350\276\221", 0));
        menuView->setTitle(QApplication::translate("ParticleEditorClass", "\350\247\206\345\233\276", 0));
    } // retranslateUi

};

namespace Ui {
    class ParticleEditorClass: public Ui_ParticleEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTICLEEDITOR_H
