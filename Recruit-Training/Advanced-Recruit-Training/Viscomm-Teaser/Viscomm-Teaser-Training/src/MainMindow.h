#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void setParser(InformationParser parser);
public slots:
    void nextPageButtonClicked();
    void previousPageButtonClicked();
    void addMemberButtonClicked();
    void removeMemberButtonClicked();

private:
    Ui::MainWindow *ui_;
    InformationParser parser_;

    void setImage();
};
#endif // MAINWINDOW_H
