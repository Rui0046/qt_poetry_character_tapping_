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
    void clickBtn(QPushButton *b);

private:
    void initHome();
    void initGame();
    void clearBtn();
    void createGrid();
    Poem getRandomPoem();

protected:
    void resizeEvent(QResizeEvent *event) override;

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