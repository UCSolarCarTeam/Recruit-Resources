#include "MainMindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    connect(ui_->nextPageButton, SIGNAL(clicked()), this, SLOT(nextPageButtonClicked()));
    setImage();
    ui_->listWidget->addItem("Remove this item");
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::nextPageButtonClicked()
{
    ui_->stackedPages->setCurrentIndex(1);
}

void MainWindow::setImage()
{
    //Update the image here
    ui_->imageLabel->setScaledContents(true);
}

void MainWindow::updateInformation()
{
    //Please update all information here
}

//Add all remaining functions here
