#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QWidget>
#include <QGridLayout>
#include <QList>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void practice();
    void challenge();
    void backHome();
    void stopGame();
    void clickBtn(int i);

private:
    void initHome();
    void initGame();
    void clearBtn();
    void createGrid(int type);
    QStackedWidget *stack;
    QWidget *homePage;
    QWidget *gamePage;

    QLabel *titleLabel;
    QLabel *labMode;
    QLabel *labScore;
    QGridLayout *gridLayout;
    QList<QPushButton*> btnList;
    int score;
    bool isPractice;

    QString rightStr;
    int needRightCnt;
    int currentCorrect;
};

#endif // MAINWINDOW_H