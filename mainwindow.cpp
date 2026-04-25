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

// 背景图片路径
#define HOME_BG "./image/home.jpg"
#define GAME_BG "./image/game.jpg"

// 诗句结构
struct Poem {
    QString sentence;
    int type;
};

// 诗句库
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

// 设置背景
void setBg(QWidget *w, QString path) {
    w->setAutoFillBackground(true);
    QPalette p;
    QPixmap pic(path);
    if (!pic.isNull()) {
        p.setBrush(QPalette::Window, pic.scaled(w->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    } else {
        p.setColor(QPalette::Window, QColor(245, 242, 235));
    }
    w->setPalette(p);
}

// 获取按钮统一样式：轻微圆角、古风底色
QString getBtnStyle()
{
    return R"(
        QPushButton{
            background-color:#D2B48C;
            border:2px solid #8B4513;
            border-radius:8px;
            color:#5D4037;
        }
        QPushButton:hover{
            background-color:#C4A882;
        }
        QPushButton:disabled{
            background-color:#E0D2BC;
            color:#999999;
        }
    )";
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    score = 0;
    isPractice = false;
    currentCorrect = 0;

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

// 首页
void MainWindow::initHome()
{
    setBg(homePage, HOME_BG);
    QVBoxLayout *v = new QVBoxLayout(homePage);
    v->setAlignment(Qt::AlignCenter);
    v->setSpacing(25);

    // 标题：点字成诗
    titleLabel = new QLabel("点字成诗");
    QFont titleFont("楷体", 42, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color:#8B4513;");
    titleLabel->setAlignment(Qt::AlignCenter);

    QPushButton *b1 = new QPushButton("练习模式");
    QPushButton *b2 = new QPushButton("闯关模式");

    QFont btnFont("楷体", 16);
    b1->setFont(btnFont);
    b2->setFont(btnFont);

    b1->setFixedSize(220, 65);
    b2->setFixedSize(220, 65);

    // 首页按钮也用圆角样式
    b1->setStyleSheet(getBtnStyle());
    b2->setStyleSheet(getBtnStyle());

    v->addWidget(titleLabel);
    v->addSpacing(30);
    v->addWidget(b1);
    v->addWidget(b2);

    connect(b1, &QPushButton::clicked, this, &MainWindow::practice);
    connect(b2, &QPushButton::clicked, this, &MainWindow::challenge);
}

// 游戏页
void MainWindow::initGame()
{
    setBg(gamePage, GAME_BG);
    QVBoxLayout *v = new QVBoxLayout(gamePage);
    QHBoxLayout *h = new QHBoxLayout;

    labMode = new QLabel("模式");
    labScore = new QLabel("得分：0");
    QPushButton *bBack = new QPushButton("返回");
    QPushButton *bStop = new QPushButton("停止");

    QFont f("楷体", 13);
    labMode->setFont(f);
    labScore->setFont(f);
    bBack->setFont(f);
    bStop->setFont(f);

    // 顶部小按钮圆角
    bBack->setStyleSheet(getBtnStyle());
    bStop->setStyleSheet(getBtnStyle());

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

// 清空按钮
void MainWindow::clearBtn()
{
    for (auto b : btnList) {
        gridLayout->removeWidget(b);
        delete b;
    }
    btnList.clear();
    currentCorrect = 0;
}

// 生成宫格
void MainWindow::createGrid(int type)
{
    clearBtn();

    Poem now;
    while (true) {
        int idx = QRandomGenerator::global()->bounded(poemNum);
        now = poems[idx];
        if (now.type == type) break;
    }

    rightStr = now.sentence;
    needRightCnt = rightStr.length();

    QStringList list;
    for (QChar c : now.sentence) list << QString(c);

    int add = (type == 9) ? 4 : 5;
    for (int i=0; i<add; i++) {
        int r = QRandomGenerator::global()->bounded(badChars.size());
        list << badChars[r];
    }

    std::shuffle(list.begin(), list.end(), std::mt19937(std::random_device{}()));

    int col = (type == 9) ? 3 : 4;
    for (int i=0; i<type; i++) {
        QPushButton *b = new QPushButton(list[i]);
        b->setFixedSize(75,75);
        b->setFont(QFont("楷体", 18));

        // 宫格字按钮 轻微圆角 8px
        b->setStyleSheet(getBtnStyle());

        btnList << b;
        gridLayout->addWidget(b, i/col, i%col);

        connect(b, &QPushButton::clicked, [=]() { clickBtn(i); });
    }
}

// 练习模式
void MainWindow::practice()
{
    isPractice = true;
    score = 0;
    stack->setCurrentWidget(gamePage);
    labMode->setText("练习模式");
    labScore->setText("得分：0");
    createGrid(9);
}

// 闯关模式
void MainWindow::challenge()
{
    isPractice = false;
    score = 0;
    stack->setCurrentWidget(gamePage);
    labMode->setText("闯关模式");
    labScore->setText("得分：0");
    createGrid(9);
}

// 返回主页
void MainWindow::backHome()
{
    stack->setCurrentWidget(homePage);
    clearBtn();
}

// 停止游戏
void MainWindow::stopGame()
{
    QString s = "最终得分：" + QString::number(score) + "\n";
    if (score <= 10)      s += "初学起步，继续加油！";
    else if (score <= 20) s += "稳步进步，表现不错！";
    else if (score <= 40) s += "诗词功底很棒！";
    else                  s += "超级厉害，诗词大师！";

    QMessageBox::information(this, "游戏结束", s);
    backHome();
}

// 点击字按钮
void MainWindow::clickBtn(int i)
{
    QPushButton *b = btnList[i];
    if (!b->isEnabled()) return;

    b->setEnabled(false);
    QString t = b->text();

    if (rightStr.contains(t)) {
        currentCorrect++;
    }

    // 答对完整一句诗才加1分
    if (currentCorrect >= needRightCnt) {
        if (!isPractice) {
            score++;
            labScore->setText("得分：" + QString::number(score));
        }

        QTimer::singleShot(600, this, [=]() {
            if (!isPractice && score > 20) {
                createGrid(12);
            } else {
                createGrid(9);
            }
        });
    }
}