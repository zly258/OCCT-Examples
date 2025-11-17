#include "MainWindow.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("OCCT AutoCAD Project");

    // Create central widget and layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Create menu bar
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // Create file menu
    QMenu *fileMenu = menuBar->addMenu("File");
    QAction *openAction = new QAction("Open", this);
    QAction *saveAction = new QAction("Save", this);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    // Create toolbar
    QToolBar *toolBar = addToolBar("Main Toolbar");
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);

    // Create status bar
    QStatusBar *statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
}

MainWindow::~MainWindow()
{
}