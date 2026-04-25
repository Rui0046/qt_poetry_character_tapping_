#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QRandomGenerator>
#include <algorithm>
#include <random>
#include <QTimer>
#include <QPixmap>
#include <QPalette>
#include <QFont>

// 背景
#define HOME_BG "images/home.jpg"
#define GAME_BG "images/game.jpg"

// 诗句
struct Poem {
    QString sentence;
    int type;
};

Poem poems[] = {
    {"大漠孤烟直",9},
    {"长河落日圆",9},
    {"举头望明月",9},
    {"春风花草香",9},
    {"黄沙百战穿金甲",12},
    {"不破楼兰终不还",12},
    {"明月何时照我还",12},
    {"独在异乡为异客",12}
};

int poemNum = sizeof(poems)/sizeof(Poem);

// 干扰字
QStringList badChars = {
    "风","云","山","水","春","夏","秋","冬",
    "天","地","星","辰","江","河","湖","海"
};

// 背景
void setBg(QWidget *w, QString path) {
    w->setAutoFillBackground(true);
    QPalette p;
    QPixmap pic(path);
    if(!pic.isNull()) {
        p.setBrush(QPalette::Window, pic.scaled(w->size(), Qt::IgnoreAspectRatio));
    }
    w->setPalette(p);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    score = 0;
    isPractice = false;

    stack = new QStackedWidget(this);
    homePage = new QWidget;
    gamePage = new QWidget;

    stack->addWidget(homePage);
    stack->addWidget(gamePage);
    setCentralWidget(stack);

    initHome();
    initGame();
}

MainWindow::~MainWindow() {}

void MainWindow::initHome()
{
    setBg(homePage, HOME_BG);
    QVBoxLayout *v = new QVBoxLayout(homePage);
    v->setAlignment(Qt::AlignCenter);
    v->setSpacing(20);

    QPushButton *b1 = new QPushButton("练习模式");
    QPushButton *b2 = new QPushButton("闯关模式");

    QFont font("楷体", 14);
    b1->setFont(font);
    b2->setFont(font);

    b1->setFixedSize(200,60);
    b2->setFixedSize(200,60);

    v->addWidget(b1);
    v->addWidget(b2);

    connect(b1, &QPushButton::clicked, this, &MainWindow::practice);
    connect(b2, &QPushButton::clicked, this, &MainWindow::challenge);
}

void MainWindow::initGame()
{
    setBg(gamePage, GAME_BG);
    QVBoxLayout *v = new QVBoxLayout(gamePage);
    QHBoxLayout *h = new QHBoxLayout;

    labMode = new QLabel("模式");
    labScore = new QLabel("得分：0");
    QPushButton *bBack = new QPushButton("返回");
    QPushButton *bStop = new QPushButton("停止");

    QFont font("楷体", 12);
    labMode->setFont(font);
    labScore->setFont(font);
    bBack->setFont(font);
    bStop->setFont(font);

    h->addWidget(labMode);
    h->addStretch();
    h->addWidget(labScore);
    h->addWidget(bBack);
    h->addWidget(bStop);

    gridLayout = new QGridLayout;
    v->addLayout(h);
    v->addLayout(gridLayout);

    connect(bBack, &QPushButton::clicked, this, &MainWindow::backHome);
    connect(bStop, &QPushButton::clicked, this, &MainWindow::stopGame);
}

void MainWindow::clearBtn()
{
    for(auto b : btnList) {
        gridLayout->removeWidget(b);
        delete b;
    }
    btnList.clear();
    correctCount = 0;
}

void MainWindow::createGrid(int type)
{
    clearBtn();

    // 选诗
    Poem now;
    while(true) {
        int idx = QRandomGenerator::global()->bounded(poemNum);
        now = poems[idx];
        if(now.type == type) break;
    }

    rightStr = now.sentence;
    need = rightStr.length();

    // 拆字
    QStringList list;
    for(QChar c : now.sentence) list << QString(c);

    // 干扰字
    int add = (type == 9) ? 4 : 5;
    for(int i=0; i<add; i++) {
        int r = QRandomGenerator::global()->bounded(badChars.size());
        list << badChars[r];
    }

    // 打乱
    std::shuffle(list.begin(), list.end(), std::mt19937(std::random_device{}()));

    // 布局
    int col = (type == 9) ? 3 : 4;
    for(int i=0; i<type; i++) {
        QPushButton *b = new QPushButton(list[i]);
        b->setFixedSize(75,75);
        b->setFont(QFont("楷体", 18));

        btnList << b;
        gridLayout->addWidget(b, i/col, i%col);

        connect(b, &QPushButton::clicked, [=]() { clickBtn(i); });
    }
}

void MainWindow::practice()
{
    isPractice = true;
    score = 0;
    stack->setCurrentWidget(gamePage);
    labMode->setText("练习模式");
    labScore->setText("得分：0");
    createGrid(9);
}

void MainWindow::challenge()
{
    isPractice = false;
    score = 0;
    stack->setCurrentWidget(gamePage);
    labMode->setText("闯关模式");
    labScore->setText("得分：0");
    createGrid(9);
}

void MainWindow::backHome()
{
    stack->setCurrentWidget(homePage);
    clearBtn();
}

void MainWindow::stopGame()
{
    QString s = "最终得分：" + QString::number(score) + "\n";
    if(score <= 10) s += "继续加油！";
    else if(score <= 20) s += "非常棒！";
    else if(score <= 40) s += "太厉害！";
    else s += "你是诗词大师！";

    QMessageBox::information(this, "游戏结束", s);
    backHome();
}

void MainWindow::clickBtn(int i)
{
    QPushButton *b = btnList[i];
    if(!b->isEnabled()) return;

    b->setEnabled(false);
    QString t = b->text();

    // 正确才计数
    if(rightStr.contains(t)) {
        correctCount++;
        if(!isPractice) {
            score++;
            labScore->setText("得分：" + QString::number(score));
        }
    }

    // ✅ 必须点满所有正确字 才下一题
    if(correctCount >= need) {
        QTimer::singleShot(600, this, [=]() {
            if(!isPractice && score > 20) {
                createGrid(12);
            } else {
                createGrid(9);
            }
        });
    }
}