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
    connect(ui_->addNoUpdateButton, SIGNAL(clicked()), this, SLOT(addNoUpdateButtonClicked()));
    connect(ui_->addAndUpdateButton, SIGNAL(clicked()), this, SLOT(addAndUpdateButtonClicked()));
    connect(ui_->noAddButton, SIGNAL(clicked()), this, SLOT(nextPageButtonClicked()));
    connect(ui_->removeMemberButton, SIGNAL(clicked()), this, SLOT(removeMemberButtonClicked()));
    connect(ui_->noRemoveButton, SIGNAL(clicked()), this, SLOT(nextPageButtonClicked()));
    connect(ui_->removeNoUpdateButton, SIGNAL(clicked()), this, SLOT(removeNoUpdateButtonClicked()));
    connect(ui_->removeAndUpdateButton, SIGNAL(clicked()), this, SLOT(removeAndUpdateButtonClicked()));

    setImage();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::nextPageButtonClicked()
{
    clearFields();
    ui_->stackedPages->setCurrentIndex(1);
}

void MainWindow::pageBackwardsButtonClicked()
{
    ui_->stackedPages->setCurrentIndex(0);
}

void MainWindow::addMemberButtonClicked()
{
    ui_->stackedPages->setCurrentIndex(2);
}

void MainWindow::addNoUpdateButtonClicked()
{
    addButtonClicked(false);
}

void MainWindow::addAndUpdateButtonClicked()
{
    addButtonClicked(true);
}

void MainWindow::addButtonClicked(bool updateFile)
{
    ui_->listWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    if(ui_->firstNameTextArea->document()->isEmpty())
    {
        ui_->errorLabel->setText("First Name is Required.");
        return;
    }

    if(ui_->lastNameTextArea->document()->isEmpty())
    {
        ui_->errorLabel->setText("Last Name is Required.");
        return;
    }

    if(ui_->gradYearList->selectedItems().size() != 1)
    {
        ui_->errorLabel->setText("Graduation Year is Required.Please Select a graduation Year.");
        return;
    }

    ui_->listWidget->addItem("First Name:" + ui_->firstNameTextArea->toPlainText() + ",  " + "Last Name:" +  ui_->lastNameTextArea->toPlainText() + ",  " + "Graduation Year:" + ui_->gradYearList->currentItem()->text() + ".\n");
    ui_->toRemoveList->addItem("First Name:" + ui_->firstNameTextArea->toPlainText() + ",  " + "Last Name:" +  ui_->lastNameTextArea->toPlainText() + ",  " + "Graduation Year:" + ui_->gradYearList->currentItem()->text() + ".\n");

    if(updateFile)
    {
        QJsonArray membersArray = parser_.getTeamMembers();
        membersArray.append(this->addMember(ui_->firstNameTextArea->toPlainText(), ui_->lastNameTextArea->toPlainText(), ui_->gradYearList->currentItem()->text()));
        parser_.updateTeamMembers(membersArray);
    }

    clearFields();
    ui_->stackedPages->setCurrentIndex(1);
}

void MainWindow::removeMemberButtonClicked() 
{
    ui_->toRemoveList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui_->stackedPages->setCurrentIndex(3);
    ui_->toRemoveList->clearSelection();
}

void MainWindow::removeNoUpdateButtonClicked()
{
    if(ui_->toRemoveList->selectedItems().size() != 1)
    {
        ui_->removeErrorLabel->setText("Please Select a member to remove.");
        return;
    }

    QListWidgetItem* item = ui_->toRemoveList->currentItem();
    QList<QListWidgetItem *> teamInfoItems = ui_->listWidget->findItems(item->text(), Qt::MatchExactly);

    foreach(QListWidgetItem * infoItem, teamInfoItems)
    {
        ui_->listWidget->removeItemWidget(infoItem);
        delete infoItem;
    }

    ui_->toRemoveList->removeItemWidget(item);
    delete item;

    ui_->stackedPages->setCurrentIndex(1);
}

void MainWindow::removeAndUpdateButtonClicked()
{
    if(ui_->toRemoveList->selectedItems().size() != 1)
    {
        ui_->removeErrorLabel->setText("Please Select a member to remove.");
        return;
    }

    QListWidgetItem* item = ui_->toRemoveList->currentItem();
    QString selectedText = item->text();
    removeNoUpdateButtonClicked();
    QJsonArray membersArray = parser_.getTeamMembers();

    QRegularExpression myRegex("(?<=:)\\w+");
    QString capturedGroup[3];
    int j = 0;
    QRegularExpressionMatchIterator i = myRegex.globalMatch(selectedText);
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        if (match.hasMatch())
        {
            capturedGroup[j] = match.captured(0);
            j++;
        }
    }

    int k = 0;
    foreach (const QJsonValue & memberObject, membersArray)
    {
        QJsonObject currentMember = memberObject.toObject();
        if(currentMember["firstName"] == capturedGroup[0] && currentMember["lastName"] == capturedGroup[1] && currentMember["gradYear"] == capturedGroup[2])
        {
            membersArray.removeAt(k);
            parser_.updateTeamMembers(membersArray);
            return;
        }
        k++;
    }
}

void MainWindow::clearFields() 
{
    ui_->firstNameTextArea->clear();
    ui_->lastNameTextArea->clear();
    ui_->gradYearList->clearSelection();
    ui_->errorLabel->clear();
    ui_->toRemoveList->clearSelection();
}

void MainWindow::setImage()
{
    QPixmap pix("../../images/solarCar.png");
    ui_->imageLabel->setPixmap(pix);
    ui_->imageLabel->setScaledContents(true);
}

QJsonObject MainWindow::addMember(QString firstName, QString lastName, QString gradYear) 
{
    QJsonObject object;
    object.insert("firstName", firstName);
    object.insert("lastName", lastName);
    object.insert("gradYear", gradYear);
    return object;
}

void MainWindow::updateInformation()
{
    parser_.readJSON();
    ui_->ownerLabel->setText(ui_->ownerLabel->text() + " " + parser_.getOwner());
    ui_->carTypeLabel->setText(ui_->carTypeLabel->text() + " " + parser_.getType());
    ui_->carNameLabel->setText(ui_->carNameLabel->text() + " " + parser_.getCarName());
    ui_->batteryPercentageBar->setValue(parser_.getBatteryPercentage());
    ui_->colorLabel->setText(ui_->colorLabel->text() + " " + parser_.getColor());
    ui_->locationLabel->setText(ui_->locationLabel->text() + " " + parser_.getLocation());

    ui_->listWidget->clear();
    QJsonArray membersArray = parser_.getTeamMembers();

    foreach (const QJsonValue & memberObject, membersArray)
    {
        QJsonObject currentMember = memberObject.toObject();
        ui_->listWidget->addItem("First Name:" + currentMember["firstName"].toString() + ",  " + "Last Name:" +  currentMember["lastName"].toString() + ",  " + "Graduation Year:" + currentMember["gradYear"].toString() + ".\n");
        ui_->toRemoveList->addItem("First Name:" + currentMember["firstName"].toString() + ",  " + "Last Name:" +  currentMember["lastName"].toString() + ",  " + "Graduation Year:" + currentMember["gradYear"].toString() + ".\n");
    }
}
