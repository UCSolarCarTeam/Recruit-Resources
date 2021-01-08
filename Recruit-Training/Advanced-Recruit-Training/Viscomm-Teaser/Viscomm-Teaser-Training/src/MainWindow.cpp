#include "MainMindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    connect(ui_->nextPageButton, SIGNAL(clicked()), this, SLOT(nextPageButtonClicked()));
    connect(ui_->pageBackwardsButton, SIGNAL(clicked()), this, SLOT(pageBackwardsButtonClicked()));
    connect(ui_->addMemberButton, SIGNAL(clicked()), this, SLOT(addMemberButtonClicked()));
    connect(ui_->removeMemberButton, SIGNAL(clicked()), this, SLOT(removeMemberButtonClicked()));
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
    ui_->imageLabel->setText("");
    QPixmap pm("./../../images/solarCar.png");
    ui_->imageLabel->setPixmap(pm);
    ui_->imageLabel->setScaledContents(true);
}

void MainWindow::updateInformation()
{
    ui_->ownerLabel->setText("Owner: " + (parser_.getObj())["owner"].toString());
    ui_->carNameLabel->setText("Car Name: " + (parser_.getObj())["carName"].toString());
    ui_->carTypeLabel->setText("Car Type: " + (parser_.getObj())["type"].toString());
    ui_->colorLabel->setText("Color: " + (parser_.getObj())["color"].toString());
    ui_->locationLabel->setText("Location: " + (parser_.getObj())["location"].toString());
    ui_->batteryPercentageBar->setValue((parser_.getObj())["batteryPercentage"].toInt());

    ui_->listWidget->clear();
    QJsonArray a = parser_.getMem();
    for (int i = 0; i < a.size(); i++)
    {
        QString name = a.at(i)["firstName"].toString();
        QString last = a.at(i)["lastName"].toString();
        QString grad = a.at(i)["gradYear"].toString();
        ui_->listWidget->addItem("First Name: " + name + ", Last Name: " + last + ", Graduation Year: " + grad + "\n");
    }
}

void MainWindow::pageBackwardsButtonClicked()
{
    ui_->stackedPages->setCurrentIndex(0);
}

void MainWindow::setParser_(InformationParser I)
{
    parser_ = I;
}

void MainWindow::addMemberButtonClicked()
{
    QString name = QInputDialog::getText(this, tr("Add Member"),
                                             tr("First Name :"), QLineEdit::Normal);

    QString last = QInputDialog::getText(this, tr("Add Member"),
                                             tr("Last Name:"), QLineEdit::Normal);

    QString grad = QInputDialog::getText(this, tr("Add Member"),
                                             tr("Graduation Year:"), QLineEdit::Normal);

    ui_->listWidget->addItem("First Name: " + name + ", Last Name: " + last + ", Graduation Year: " + grad + "\n");
}

void MainWindow::removeMemberButtonClicked()
{
     ui_->listWidget->takeItem(ui_->listWidget->currentRow());
}
