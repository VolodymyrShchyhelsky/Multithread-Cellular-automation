#include "cellularautomation.h"
#include "ui_cellularautomation.h"

QMutex m_coor;

CellularAutomation::CellularAutomation(QWidget *parent, int _Sexual, int _SizeW, int _SizeH, int _RadDisp,
                                       int _RadBreed, int _Fertility, int _Density, int _Time, int _CountKind) :
    QDialog(parent), Sexual(_Sexual), SizeW(_SizeW), SizeH(_SizeH), RadDisp(_RadDisp), RadBreed(_RadBreed),
                     Fertility(_Fertility), Density(_Density), CountKind(_CountKind), Time(_Time),
    ui(new Ui::CellularAutomation)
{
    ui->setupUi(this);

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    //create Pixmap, Painter and colors vector
    pm = new QPixmap(QSize(ui->label->width(), ui->label->height()));
    pm->fill(Qt::white);
    paint = new QPainter(pm);
    paint->fillRect(paint->viewport(), QColor(255,255,255));
    ui->label->setPixmap(*pm);
    color << Qt::white << Qt::black << Qt::red <<
             Qt::green << Qt::blue << Qt::cyan <<
             Qt::magenta << Qt::yellow << Qt::gray <<
             Qt::darkCyan << Qt::darkYellow;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(next_step()));
    FillArray();
    timer->start(100);
}

void CellularAutomation::next_step() {
    draw();
    step();
    --Time;
    if(Time == 0)
        timer->stop();
}

void CellularAutomation::draw() {
    for(int i = 0; i < SizeH; ++i)
        for(int j = 0; j < SizeW; ++j) {
            paint->setBrush(color[Array[i][j]]);
            paint->drawRect(j*(ui->label->width())/SizeW, i*(ui->label->height())/SizeH, (ui->label->width())/SizeW, (ui->label->height())/SizeH);
        }
    ui->label->setPixmap(*pm);
}

int don=0;
void CellularAutomation::step() {
    don = 0;
    for(int i=1; i<=CountKind; ++i)
    {
        MyThread* newThread = new MyThread(this, i);
        newThread->start();
    }

    while(don<CountKind) {}
    SwitchArray();
}

void MyThread::run() {
    for(int it = 0; it < CelAut->Coordinates[num].size(); ++it) {
        int i=CelAut->Coordinates[num][it].first, j=CelAut->Coordinates[num][it].second;

        bool proliferation = false;
        if(CelAut->Sexual != 0) {
            int count_of_friend = 0;
            for(int _i = i - CelAut->RadBreed; _i <= i + CelAut->RadBreed; ++_i)
                for(int _j = j - CelAut->RadBreed; _j <= j + CelAut->RadBreed; ++_j) {
                    if(_i>=0 && _i<CelAut->SizeH && _j>=0 && _j<CelAut->SizeW) {
                        if(CelAut->Array[_i][_j] == CelAut->Array[i][j])
                            count_of_friend++;
                    }
                }
            if( (CelAut->Sexual == 2 && count_of_friend>=2) || count_of_friend>=1 ) proliferation = 1;
        } else proliferation = true;

        if(proliferation)
        {
            for(int child = 0; child < CelAut->Fertility; ++child)
            {
                int x,y;
                bool flag = 0;
                do {
                    if(qrand() % 2)
                        x = i - (qrand() % (CelAut->RadDisp + 1));
                    else
                        x = i + (qrand() % (CelAut->RadDisp + 1));
                    if(qrand() % 2)
                        y = j - (qrand() % (CelAut->RadDisp + 1));
                    else
                        y = j + (qrand() % (CelAut->RadDisp + 1));

                    if(x >= 0  && x < CelAut->SizeH && y >= 0 && y < CelAut->SizeW && !(x==i && y==j) )
                        flag = 1;
                } while(!flag);
                CelAut->NewArray[x][y].append(CelAut->Array[i][j]);
            }
        }

        //CelAut->NewArray[i][j].append(0);

    }
    don++;
    qDebug() << don << "d";
}

void CellularAutomation::SwitchArray() {
    qDebug() << "SWIt";
    Coordinates.clear();
    Coordinates.resize(10);

    for(int i = 0; i < SizeH; ++i)
        for(int j = 0; j < SizeW; ++j) {
            if(NewArray[i][j].size() == 0)// || NewArray[i][j][NewArray[i][j].size()-1] == 0)
                Array[i][j] = 0;
            else {
                int it = qrand() % NewArray[i][j].size();
                Array[i][j] = NewArray[i][j][it];
                Coordinates[Array[i][j]].append(qMakePair(i,j));
            }
            NewArray[i][j].clear();
        }
}

void CellularAutomation::FillArray() {
    Array.resize(SizeH+2);
    NewArray.resize(SizeH+2);
    Coordinates.resize(10);
    for(int i = 0; i < SizeH; ++i)
    {
        Array[i].resize(SizeW+2);
        Array[i].fill(0);
        NewArray[i].resize(SizeW+2);
    }

    for(int i = 1; i <= CountKind; ++i)
        for(int d = 0; d < Density; ++d)
        {
            int x,y;
            do {
                x = qrand() % SizeH;
                y = qrand() % SizeW;
            } while(Array[x][y] != 0);
            Coordinates[i].append(qMakePair(x,y));
            Array[x][y] = i;
        }
}

CellularAutomation::~CellularAutomation()
{
    delete ui;
}
