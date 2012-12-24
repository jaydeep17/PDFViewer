#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    KXmlGuiWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mPageView = new PageView;
    ui->scrollArea->setWidget(mPageView);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    this->setCentralWidget(ui->scrollArea);
    mDoc = new Document();

    setupActions();
    setupGUI(Default,"pdfviewerui.rc");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showPage(int index)
{
    mPageView->setPixmap(QPixmap::fromImage(mDoc->renderPage(index)));
}

void MainWindow::openSlot()
{
    QString filename = QFileDialog::getOpenFileName(this,"Select a pdf file",QDir::homePath(),"PDF (*.pdf)");
    if(!filename.isEmpty())
        openPDF(filename);
}

bool MainWindow::openPDF(QString filename)
{
    mDoc->openFile(filename);
    showPage(0);
    // return false if some problem occurs
    return true;
}

void MainWindow::setupActions()
{
    KStandardAction::open(this,SLOT(openSlot()),actionCollection());
}