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

#define HOME_BG "images/home.jpg"
#define GAME_BG "images/game.jpg"

Poem poems[] = {
    {"空山新雨后",9,"王维《山居秋暝》"},
    {"明月松间照",9,"王维《山居秋暝》"},
    {"竹喧归浣女",9,"王维《山居秋暝》"},
    {"大漠孤烟直",9,"王维《使至塞上》"},
    {"征蓬出汉塞",9,"王维《使至塞上》"},
    {"人闲桂花落",9,"王维《鸟鸣涧》"},
    {"月出惊山鸟",9,"王维《鸟鸣涧》"},
    {"江流天地外",9,"王维《汉江临眺》"},
    {"山色有无中",9,"王维《汉江临眺》"},
    {"海内存知己",9,"王勃《送杜少府之任蜀州》"},
    {"天涯若比邻",9,"王勃《送杜少府之任蜀州》"},
    {"客路青山外",9,"王湾《次北固山下》"},
    {"潮平两岸阔",9,"王湾《次北固山下》"},
    {"海日生残夜",9,"王湾《次北固山下》"},
    {"国破山河在",9,"杜甫《春望》"},
    {"感时花溅泪",9,"杜甫《春望》"},
    {"烽火连三月",9,"杜甫《春望》"},
    {"岱宗夫如何",9,"杜甫《望岳》"},
    {"造化钟神秀",9,"杜甫《望岳》"},
    {"荡胸生曾云",9,"杜甫《望岳》"},
    {"会当凌绝顶",9,"杜甫《望岳》"},
    {"离离原上草",9,"白居易《赋得古原草送别》"},
    {"野火烧不尽",9,"白居易《赋得古原草送别》"},
    {"远芳侵古道",9,"白居易《赋得古原草送别》"},
    {"千山鸟飞绝",9,"柳宗元《江雪》"},
    {"孤舟蓑笠翁",9,"柳宗元《江雪》"},
    {"移舟泊烟渚",9,"孟浩然《宿建德江》"},
    {"野旷天低树",9,"孟浩然《宿建德江》"},
    {"绿树村边合",9,"孟浩然《过故人庄》"},
    {"开轩面场圃",9,"孟浩然《过故人庄》"},
    {"春眠不觉晓",9,"孟浩然《春晓》"},
    {"夜来风雨声",9,"孟浩然《春晓》"},
    {"白日依山尽",9,"王之涣《登鹳雀楼》"},
    {"欲穷千里目",9,"王之涣《登鹳雀楼》"},
    {"泠泠七弦上",9,"刘长卿《听弹琴》"},
    {"日暮苍山远",9,"刘长卿《逢雪宿芙蓉山主人》"},
    {"柴门闻犬吠",9,"刘长卿《逢雪宿芙蓉山主人》"},
    {"红豆生南国",9,"王维《相思》"},
    {"愿君多采撷",9,"王维《相思》"},
    {"床前明月光",9,"李白《静夜思》"},
    {"举头望明月",9,"李白《静夜思》"},
    {"众鸟高飞尽",9,"李白《独坐敬亭山》"},
    {"相看两不厌",9,"李白《独坐敬亭山》"},
    {"山随平野尽",9,"李白《渡荆门送别》"},
    {"江入大荒流",9,"李白《渡荆门送别》"},
    {"月下飞天镜",9,"李白《渡荆门送别》"},
    {"仍怜故乡水",9,"李白《渡荆门送别》"},
    {"青山横北郭",9,"李白《送友人》"},
    {"白水绕东城",9,"李白《送友人》"},
    {"浮云游子意",9,"李白《送友人》"},
    {"落日故人情",9,"李白《送友人》"},
    {"太乙近天都",9,"王维《终南山》"},
    {"白云回望合",9,"王维《终南山》"},
    {"分野中峰变",9,"王维《终南山》"},
    {"寒随一夜去",9,"王湾《立春》"},
    {"春逐五更来",9,"王湾《立春》"},
    {"天意怜幽草",9,"李商隐《晚晴》"},
    {"人间重晚晴",9,"李商隐《晚晴》"},
    {"向晚意不适",9,"李商隐《登乐游原》"},
    {"夕阳无限好",9,"李商隐《登乐游原》"},
    {"猿啼洞庭树",9,"马戴《楚江怀古》"},
    {"人在木兰舟",9,"马戴《楚江怀古》"},
    {"露气寒光集",9,"马戴《楚江怀古》"},
    {"微阳下楚丘",9,"马戴《楚江怀古》"},
    {"木落雁南度",9,"孟浩然《早寒江上有怀》"},
    {"北风江上寒",9,"孟浩然《早寒江上有怀》"},
    {"我家襄水曲",9,"孟浩然《早寒江上有怀》"},
    {"遥隔楚云端",9,"孟浩然《早寒江上有怀》"},
    {"林暗草惊风",9,"卢纶《塞下曲》"},
    {"将军夜引弓",9,"卢纶《塞下曲》"},
    {"平明寻白羽",9,"卢纶《塞下曲》"},
    {"没在石棱中",9,"卢纶《塞下曲》"},
    {"月黑雁飞高",9,"卢纶《塞下曲》"},
    {"单于夜遁逃",9,"卢纶《塞下曲》"},
    {"欲将轻骑逐",9,"卢纶《塞下曲》"},
    {"大雪满弓刀",9,"卢纶《塞下曲》"},
    {"江静潮初落",9,"张循之《秋夜江行》"},
    {"林昏瘴不开",9,"张循之《秋夜江行》"},
    {"时有落花至",9,"刘昚虚《阙题》"},
    {"远随流水香",9,"刘昚虚《阙题》"},
    {"道由白云尽",9,"刘昚虚《阙题》"},
    {"春与青溪长",9,"刘昚虚《阙题》"},
    {"闲门向山路",9,"刘昚虚《阙题》"},
    {"深柳读书堂",9,"刘昚虚《阙题》"},
    {"孤山寺北贾亭西",9,"白居易《钱塘湖春行》"},
    {"水面初平云脚低",9,"白居易《钱塘湖春行》"}
};

Poem poems2[] = {
    {"秦时明月汉时关",12,"王昌龄《出塞》"},
    {"万里长征人未还",12,"王昌龄《出塞》"},
    {"黄沙百战穿金甲",12,"王昌龄《从军行》"},
    {"不破楼兰终不还",12,"王昌龄《从军行》"},
    {"独在异乡为异客",12,"王维《九月九日忆山东兄弟》"},
    {"每逢佳节倍思亲",12,"王维《九月九日忆山东兄弟》"},
    {"京口瓜洲一水间",12,"王安石《泊船瓜洲》"},
    {"春风又绿江南岸",12,"王安石《泊船瓜洲》"},
    {"日照香炉生紫烟",12,"李白《望庐山瀑布》"},
    {"飞流直下三千尺",12,"李白《望庐山瀑布》"},
    {"朝辞白帝彩云间",12,"李白《早发白帝城》"},
    {"千里江陵一日还",12,"李白《早发白帝城》"},
    {"天门中断楚江开",12,"李白《望天门山》"},
    {"孤帆一片日边来",12,"李白《望天门山》"},
    {"烟笼寒水月笼沙",12,"杜牧《泊秦淮》"},
    {"商女不知亡国恨",12,"杜牧《泊秦淮》"},
    {"君问归期未有期",12,"李商隐《夜雨寄北》"},
    {"何当共剪西窗烛",12,"李商隐《夜雨寄北》"},
    {"千里黄云白日曛",12,"高适《别董大》"},
    {"莫愁前路无知己",12,"高适《别董大》"},
    {"毕竟西湖六月中",12,"杨万里《晓出净慈寺送林子方》"},
    {"接天莲叶无穷碧",12,"杨万里《晓出净慈寺送林子方》"},
    {"忽如一夜春风来",12,"岑参《白雪歌送武判官归京》"},
    {"瀚海阑干百丈冰",12,"岑参《白雪歌送武判官归京》"},
    {"沉舟侧畔千帆过",12,"刘禹锡《酬乐天扬州初逢席上见赠》"},
    {"病树前头万木春",12,"刘禹锡《酬乐天扬州初逢席上见赠》"},
    {"怀旧空吟闻笛赋",12,"刘禹锡《酬乐天扬州初逢席上见赠》"},
    {"到乡翻似烂柯人",12,"刘禹锡《酬乐天扬州初逢席上见赠》"},
    {"朱雀桥边野草花",12,"刘禹锡《乌衣巷》"},
    {"旧时王谢堂前燕",12,"刘禹锡《乌衣巷》"},
    {"折戟沉沙铁未销",12,"杜牧《赤壁》"},
    {"东风不与周郎便",12,"杜牧《赤壁》"},
    {"人生自古谁无死",12,"文天祥《过零丁洋》"},
    {"留取丹心照汗青",12,"文天祥《过零丁洋》"},
    {"浩荡离愁白日斜",12,"龚自珍《己亥杂诗》"},
    {"落红不是无情物",12,"龚自珍《己亥杂诗》"},
    {"月落乌啼霜满天",12,"张继《枫桥夜泊》"},
    {"姑苏城外寒山寺",12,"张继《枫桥夜泊》"},
    {"峨眉山月半轮秋",12,"李白《峨眉山月歌》"},
    {"夜发清溪向三峡",12,"李白《峨眉山月歌》"},
    {"一蓑烟雨任平生",12,"苏轼《定风波》"},
    {"竹杖芒鞋轻胜马",12,"苏轼《定风波》"},
    {"大江东去浪淘尽",12,"苏轼《念奴娇·赤壁怀古》"},
    {"暖风熏得游人醉",12,"林升《题临安邸》"},
    {"直把杭州作汴州",12,"林升《题临安邸》"},
    {"山外青山楼外楼",12,"林升《题临安邸》"},
    {"僵卧孤村不自哀",12,"陆游《十一月四日风雨大作》"},
    {"夜阑卧听风吹雨",12,"陆游《十一月四日风雨大作》"},
    {"王师北定中原日",12,"陆游《示儿》"},
    {"死去元知万事空",12,"陆游《示儿》"},
    {"千古兴亡多少事",12,"辛弃疾《南乡子·登京口北固亭有怀》"},
    {"生子当如孙仲谋",12,"辛弃疾《南乡子·登京口北固亭有怀》"},
    {"郁孤台下清江水",12,"辛弃疾《菩萨蛮·书江西造口壁》"},
    {"清明时节雨纷纷",12,"杜牧《清明》"},
    {"借问酒家何处有",12,"杜牧《清明》"},
    {"远上寒山石径斜",12,"杜牧《山行》"},
    {"停车坐爱枫林晚",12,"杜牧《山行》"},
    {"春城无处不飞花",12,"韩翃《寒食》"},
    {"日暮汉宫传蜡烛",12,"韩翃《寒食》"},
    {"潮打空城寂寞回",12,"刘禹锡《石头城》"},
    {"淮水东边旧时月",12,"刘禹锡《石头城》"},
    {"山围故国周遭在",12,"刘禹锡《石头城》"},
    {"银烛秋光冷画屏",12,"杜牧《秋夕》"},
    {"轻罗小扇扑流萤",12,"杜牧《秋夕》"},
    {"天阶夜色凉如水",12,"杜牧《秋夕》"},
    {"卧看牵牛织女星",12,"杜牧《秋夕》"},
    {"唯有牡丹真国色",12,"刘禹锡《赏牡丹》"},
    {"花开时节动京城",12,"刘禹锡《赏牡丹》"},
    {"草木知春不久归",12,"韩愈《晚春》"},
    {"百般红紫斗芳菲",12,"韩愈《晚春》"},
    {"杨花榆荚无才思",12,"韩愈《晚春》"},
    {"惟解漫天作雪飞",12,"韩愈《晚春》"},
    {"沧海月明珠有泪",12,"李商隐《锦瑟》"},
    {"蓝田日暖玉生烟",12,"李商隐《锦瑟》"},
    {"庄生晓梦迷蝴蝶",12,"李商隐《锦瑟》"},
    {"望帝春心托杜鹃",12,"李商隐《锦瑟》"},
    {"锦瑟无端五十弦",12,"李商隐《锦瑟》"},
    {"一弦一柱思华年",12,"李商隐《锦瑟》"},
    {"蓬山此去无多路",12,"李商隐《无题》"},
    {"青鸟殷勤为探看",12,"李商隐《无题》"},
    {"相见时难别亦难",12,"李商隐《无题》"},
    {"东风无力百花残",12,"李商隐《无题》"}
};

int poemNum = sizeof(poems)/sizeof(Poem) + sizeof(poems2)/sizeof(Poem);

QStringList badChars = {
    "风","云","山","水","春","夏","秋","冬",
    "天","地","星","辰","江","河","湖","海",
    "花","草","林","木","日","月","雾","霜",
    "雷","雨","川","城","楼","亭","台","桥",
    "舟","君","子","情","思","朝","暮","千",
    "万","高","低","长","短","东","西","南",
    "北","前","后","左","右","寒","暖","生",
    "落","飞","舞","平","远","孤","独","空",
    "幽","静","清","淡","烟","波","帆","影",
    "萧","瑟","沧","茫","辞","归","行","游",
    "乡","国","离","别","悲","欢","今","古",
    "荣","枯","浮","沉","遥","近","虚","实",
    "微","浩","凌","绝","凭","临","登","望",
    "吟","赋","酌","醉","眠","梦","羁","旅",
    "鸿","雁","蝉","莺","猿","鹤","庭","院",
    "窗","帘","阶","廊","峰","峦","戈","甲",
    "弓","马","霜","雪","尘","烟","霄","汉"
};

void setBg(QWidget *w, QString path)
{
    QPalette palette;
    QPixmap pix(path);
    if(!pix.isNull())
    {
        pix = pix.scaled(w->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        palette.setBrush(QPalette::Window, QBrush(pix));
    }
    else
    {
        palette.setColor(QPalette::Window, QColor(245,242,235));
    }
    w->setPalette(palette);
    w->setAutoFillBackground(true);
}

QString getBtnStyle()
{
    return R"(
        QPushButton{
            background-color:#D2B48C;
            border:2px solid #8B4513;
            border-radius:8px;
            color:#5D4037;
            font-size:24px;
            font-weight:bold;
            font-family:"楷体";
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

QString getBigBtnStyle()
{
    return R"(
        QPushButton{
            background-color:#D2B48C;
            border:2px solid #8B4513;
            border-radius:12px;
            color:#5D4037;
            font-size:20px;
            font-weight:bold;
            font-family:"楷体";
        }
        QPushButton:hover{
            background-color:#C4A882;
        }
    )";
}

QString getSmallBtnStyle()
{
    return R"(
        QPushButton{
            background-color:#D2B48C;
            border:2px solid #8B4513;
            border-radius:6px;
            color:#5D4037;
            font-size:16px;
            font-family:"楷体";
        }
        QPushButton:hover{
            background-color:#C4A882;
        }
    )";
}

// 弹出统一赏析弹窗
void showPoemInfo(Poem p)
{
    QString info = "📜 完整诗句\n「" + p.sentence + "」\n\n🏷 出处\n" + p.source;
    QMessageBox msgBox;
    msgBox.setWindowTitle("诗词赏析");
    msgBox.setText(info);
    QFont msgFont("微软雅黑",14);
    msgBox.setFont(msgFont);
    msgBox.exec();
}

Poem MainWindow::getRandomPoem()
{
    int idx = QRandomGenerator::global()->bounded(poemNum);
    if(idx < sizeof(poems)/sizeof(Poem))
        return poems[idx];
    else
        return poems2[idx - sizeof(poems)/sizeof(Poem)];
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    score = 0;
    isPractice = false;
    currentPos = 0;

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
    v->setSpacing(30);

    titleLabel = new QLabel("点字成诗");
    QFont titleFont("楷体", 48, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color:#8B4513;");
    titleLabel->setAlignment(Qt::AlignCenter);

    QPushButton *b1 = new QPushButton("练习模式");
    QPushButton *b2 = new QPushButton("闯关模式");

    b1->setFixedSize(240, 70);
    b2->setFixedSize(240, 70);
    b1->setStyleSheet(getBigBtnStyle());
    b2->setStyleSheet(getBigBtnStyle());

    v->addWidget(titleLabel);
    v->addSpacing(40);
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
    QFont topFont("楷体", 16);
    labMode->setFont(topFont);
    labScore->setFont(topFont);

    QPushButton *bBack = new QPushButton("返回");
    QPushButton *bStop = new QPushButton("停止");
    bBack->setStyleSheet(getSmallBtnStyle());
    bStop->setStyleSheet(getSmallBtnStyle());

    h->addWidget(labMode);
    h->addStretch();
    h->addWidget(labScore);
    h->addWidget(bBack);
    h->addWidget(bStop);

    gridLayout = new QGridLayout;
    gridLayout->setSpacing(10);
    v->addLayout(h);
    v->addLayout(gridLayout);

    connect(bBack, &QPushButton::clicked, this, &MainWindow::backHome);
    connect(bStop, &QPushButton::clicked, this, &MainWindow::stopGame);
}

void MainWindow::clearBtn()
{
    for (auto b : btnList)
    {
        gridLayout->removeWidget(b);
        delete b;
    }
    btnList.clear();
}

void MainWindow::createGrid()
{
    clearBtn();
    Poem now = getRandomPoem();

    currentPoem = now;
    targetSentence = now.sentence;
    currentPos = 0;

    QStringList list;
    for (QChar c : now.sentence)
        list << QString(c);

    int add = (now.type == 9) ? 4 : 5;
    for (int i = 0; i < add; i++)
    {
        int r = QRandomGenerator::global()->bounded(badChars.size());
        list << badChars[r];
    }

    std::shuffle(list.begin(), list.end(), std::mt19937(std::random_device{}()));
    int col = (now.type == 9) ? 3 : 4;

    for (int i = 0; i < now.type; i++)
    {
        QPushButton *b = new QPushButton(list[i]);
        b->setFixedSize(80,80);
        b->setStyleSheet(getBtnStyle());
        btnList << b;
        gridLayout->addWidget(b, i/col, i%col);
        connect(b, &QPushButton::clicked, this, [=](){ clickBtn(b); });
    }
}

void MainWindow::practice()
{
    isPractice = true;
    labMode->setText("练习模式");
    labScore->setText("得分：" + QString::number(score));
    stack->setCurrentWidget(gamePage);
    createGrid();
}

void MainWindow::challenge()
{
    isPractice = false;
    score = 0;
    labMode->setText("闯关模式");
    labScore->setText("得分：0");
    stack->setCurrentWidget(gamePage);
    createGrid();
}

void MainWindow::backHome()
{
    stack->setCurrentWidget(homePage);
    clearBtn();
}

void MainWindow::stopGame()
{
    QString s = "最终得分：" + QString::number(score) + "\n";
    if (score <= 10)      s += "初学起步，继续加油！";
    else if (score <= 20) s += "稳步进步，表现不错！";
    else if (score <= 40) s += "诗词功底很棒！";
    else                  s += "超级厉害，诗词大师！";

    QMessageBox msgBox;
    msgBox.setWindowTitle("游戏结束");
    msgBox.setText(s);
    QFont msgFont("微软雅黑",14);
    msgBox.setFont(msgFont);
    msgBox.exec();

    backHome();
}

void MainWindow::clickBtn(QPushButton *b)
{
    if(!b->isEnabled()) return;

    QString selectText = b->text();
    QString rightChar = QString(targetSentence.at(currentPos));

    if(selectText == rightChar)
    {
        // 选对
        b->setEnabled(false);
        currentPos++;

        // 整句完成
        if(currentPos >= targetSentence.length())
        {
            score++;
            labScore->setText("得分：" + QString::number(score));
            // 答对也弹注释
            showPoemInfo(currentPoem);
            QTimer::singleShot(600, this, [=](){
                createGrid();
            });
        }
    }
    else
    {
        // 选错：直接弹全诗赏析
        showPoemInfo(currentPoem);

        if(isPractice)
        {
            // 练习模式：答错直接下一题
            QTimer::singleShot(600, this, [=](){
                createGrid();
            });
        }
        else
        {
            // 闯关模式：选错直接结束
            QMessageBox::critical(this,"闯关失败","本题答错，游戏结束！");
            stopGame();
        }
    }
}