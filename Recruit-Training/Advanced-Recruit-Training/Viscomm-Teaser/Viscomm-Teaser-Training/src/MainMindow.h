#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpression>
#include <InformationParser.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateInformation();
    QJsonObject addMember(QString firstName, QString lastName, QString gradYear);
public slots:
    void nextPageButtonClicked();
    void pageBackwardsButtonClicked();
    void addMemberButtonClicked();
    void removeMemberButtonClicked();
    void addNoUpdateButtonClicked();
    void addAndUpdateButtonClicked();
    void addButtonClicked(bool updateFile);
    void removeNoUpdateButtonClicked();
    void removeAndUpdateButtonClicked();
    void clearFields();

private:
    Ui::MainWindow *ui_;
    InformationParser parser_;
    void setImage();
};
#endif // MAINWINDOW_H
