#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QVariant>
#include <QInputDialog>
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
    void setParser_(InformationParser I);
public slots:
    void nextPageButtonClicked();
    void pageBackwardsButtonClicked();
    void addMemberButtonClicked();
    void removeMemberButtonClicked();

private:
    Ui::MainWindow *ui_;
    InformationParser parser_;

    void setImage();
};
#endif // MAINWINDOW_H
