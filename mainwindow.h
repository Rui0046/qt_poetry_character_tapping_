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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Poem {
    QString sentence;
    int type;
    QString source;
};

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
    void clickBtn(QPushButton *b); // 声明必须和定义一致

private:
    void initHome();
    void initGame();
    void clearBtn();
    void createGrid(); // 无参声明，和cpp里的定义一致
    Poem getRandomPoem();

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
    Poem currentPoem;
    QString targetSentence;
    int currentPos;
};

#endif // MAINWINDOW_H