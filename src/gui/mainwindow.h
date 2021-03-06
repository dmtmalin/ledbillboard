#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void slotSuccessAllPlaylist();
    void slotFinishedDownloadMediaFiles();
    void slotPressedButtonShowBoard();
    void slotPressedButtonHideBoard();
};

#endif // MAINWINDOW_H
