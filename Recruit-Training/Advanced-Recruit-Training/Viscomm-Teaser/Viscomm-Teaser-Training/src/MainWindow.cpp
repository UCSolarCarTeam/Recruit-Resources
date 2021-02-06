#include "MainMindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    connect(ui_->nextPageButton, SIGNAL(clicked()), this, SLOT(nextPageButtonClicked()));
    connect(ui_->pageBackwardsButton, SIGNAL(clicked()), this, SLOT(previousPageButtonClicked()));
    connect(ui_->addMemberButton, SIGNAL(clicked()), this, SLOT(addMemberButtonClicked()));
    connect(ui_->removeMemberButton, SIGNAL(clicked()), this, SLOT(removeMemberButtonClicked()));
    setImage();
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
    QPixmap img("../../images/solarCar.png");
    ui_->imageLabel->setPixmap(img);
    ui_->imageLabel->setScaledContents(true);
}

void MainWindow::updateInformation()
{
    ui_->ownerLabel->setText("Owner: " + parser_.getOwner());
    ui_->carNameLabel->setText("Car Name: " + parser_.getCarName());
    ui_->carTypeLabel->setText("Car Type: " + parser_.getType());
    ui_->colorLabel->setText("Color: " + parser_.getColor());
    ui_->locationLabel->setText("Location: " + parser_.getLocation());
    ui_->batteryPercentageBar->setValue(parser_.getBatteryPercentage());

    QStringList temp;
    for(Member m : parser_.getViscommTeamMembers())
    {
        temp.append("First Name: " +m.getFirstName()
                    +", Last Name: " +m.getLastName()
                    +", Graduation Year: " +QString::number(m.getGradYear()));
    }
    ui_->listWidget->clear();
    ui_->listWidget->addItems(temp);
}

//Add all remaining functions here
void MainWindow::previousPageButtonClicked()
{
    ui_->stackedPages->setCurrentIndex(0);
}

void MainWindow::addMemberButtonClicked()
{
    bool input;
    QString first = QInputDialog::getText(this, tr("Member Registration"), tr("Member First Name:"),
                                          QLineEdit::Normal, tr(""), &input);
    if(!input || first.isEmpty())
    {
        return;
    }

    QString last = QInputDialog::getText(this, tr("Member Registration"), tr("Member Last Name:"),
                                         QLineEdit::Normal, tr(""), &input);
    if(!input || last.isEmpty())
    {
        return;
    }

    int year = QInputDialog::getInt(this, tr("Member Registration"),
                                     tr("Member Graduation Year:"), 2021, 2000, 2030, 1, &input);
    if(!input)
    {
        return;
    }

    if(!parser_.addMember(first, last, year))
    {
        qDebug() << "Already a member named " +first +" " +last +", graduating in " << year;
    }

    QStringList temp;
    for(Member m : parser_.getViscommTeamMembers())
    {
        temp.append("First Name: " +m.getFirstName()
                    +", Last Name: " +m.getLastName()
                    +", Graduation Year: " +QString::number(m.getGradYear()));
    }
    ui_->listWidget->clear();
    ui_->listWidget->addItems(temp);
}

void MainWindow::removeMemberButtonClicked()
{
    int index = ui_->listWidget->currentRow();
    if(index == -1)
    {
        return;
    }

    Member target = parser_.getViscommTeamMembers()[index];
    parser_.removeMember(target.getFirstName(), target.getLastName(), target.getGradYear());

    QStringList temp;
    for(Member m : parser_.getViscommTeamMembers())
    {
        temp.append("First Name: " +m.getFirstName()
                    +", Last Name: " +m.getLastName()
                    +", Graduation Year: " +QString::number(m.getGradYear()));
    }
    ui_->listWidget->clear();
    ui_->listWidget->addItems(temp);
}

void MainWindow::setParser(InformationParser parser)
{
    parser_ = parser;
}
