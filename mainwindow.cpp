#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QDebug>

const int GRIDSWIDTH=540;
const int GRIDSHEIGHT=540;//格子的总宽高
const int IMAGEX=20;
const int IMAGEY=80;//图片的左上角坐标

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(850,700);

    //TODO输入m,n
    m=4;
    n=3;
    gridwidth=GRIDSWIDTH/n;
    gridheight=GRIDSHEIGHT/m;

    //初始化大图
    originalImage=NULL;

    //初始化格子
    grids=new QLabel*[m*n];

    //初始化小图
    images=new QImage[m*n];

    //初始化编号
    idx=new int*[m];
    for (int i=0;i<m;i++) idx[i]=new int[n];

    //绘制格子，添加分割线
    for (int i=0;i<m*n;i++){
        grids[i]=new QLabel(this);
        grids[i]->setGeometry(0,0,gridwidth,gridheight);
        grids[i]->move(IMAGEX+gridwidth*(i%n),IMAGEY+gridheight*(i/n));
        grids[i]->setFrameShape(QFrame::Box);//添加分割线
        grids[i]->setPixmap((QPixmap(":/images/blank.jpg")));//添加空白背景
        idx[i/n][i%n]=i;
    }
    idx[m-1][n-1]=-1;//空白空格，以示区别
}

//将大图分为小图，按照顺序放进格子，最后一个为空白
void MainWindow::splitImage(){
    QImage tmp=originalImage->scaled(gridwidth*n,gridheight*m);
    for (int i=0;i<m*n;i++){
        //从大图中截取子图
        images[i]=tmp.copy(gridwidth*(i%n),gridheight*(i/n),gridwidth,gridheight);
        grids[i]->setPixmap(QPixmap::fromImage(images[i]));
        idx[i/n][i%n]=i;
    }
    idx[m-1][n-1]=-1;
    QPixmap blank(":/images/blank.jpg");
    grids[m*n-1]->setPixmap(blank);
}

//打乱图片
void MainWindow::shuffle(){
    int shuffleTimes=10;//移动图片的次数
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++)
            qDebug()<<idx[i][j]<<" ";
        qDebug()<<"\n";
    }
    for (int i=0;i<shuffleTimes;++i){
        int row=0,col=0;
        for (int j=0;j<m*n;j++){
            if (idx[j/n][j%n]==-1){
                row=j/n;
                col=j%n;
                break;
            }
        }//找到空白图片所在格子的位置
        int direction=qrand()%4;//4个方向
        switch (direction) {
        case 0://空格向下移动
            if (row<m-1){
                idx[row][col]=idx[row+1][col];
                idx[row+1][col]=-1;
            }
            break;
        case 1://上
            if (row>0){
                idx[row][col]=idx[row-1][col];
                idx[row-1][col]=-1;
            }
            break;
        case 2://左
            if (col>0){
                idx[row][col]=idx[row][col-1];
                idx[row][col-1]=-1;
            }
            break;
        case 3://右
            if (col<n-1){
                idx[row][col]=idx[row][col+1];
                idx[row][col+1]=-1;
            }
            break;
        default:
            break;
        }
        for (int i=0;i<m;i++){
            for (int j=0;j<n;j++)
                qDebug()<<idx[i][j]<<" ";
            qDebug()<<"\n";
        }
    }
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++)
            qDebug()<<idx[i][j]<<" ";
        qDebug()<<"\n";
    }
    //将更新同步到ui
    moveImage();
}

//根据idx矩阵移动格子
void MainWindow::moveImage(){
    for (int i=0;i<m*n;i++){
        int index=idx[i/n][i%n];
        if (index==-1) index=m*n-1;
        grids[index]->move(IMAGEX+gridwidth*(i%n),
                           IMAGEY+gridheight*(i/n));
    }
}


//选择图片
void MainWindow::on_select_clicked()
{
    QString selectedName=QFileDialog::getOpenFileName(this,
                                                      tr("选择一张图片"),
                                                      "",
                                                      "Images(*.png *.jpg)");
    if (selectedName.isEmpty()){
        return;
    }

    filename=selectedName;
    if (originalImage!=NULL){
        delete originalImage;
        originalImage=NULL;
    }
    originalImage=new QImage(filename);//更换大图
    //在旁边显示还原后的图像，作为提示
    QImage goalImage=originalImage->scaled(ui->goal->width(),ui->goal->height());
    ui->goal->setPixmap(QPixmap::fromImage(goalImage));
    splitImage();
    shuffle();//打乱图片
}

MainWindow::~MainWindow()
{
    delete ui;
    //因为originalImage,images,idx和本window都没有父子关系，所以都需要手动释放
    if (originalImage) delete originalImage;
    delete images;
    for (int i=0;i<m;i++) delete idx[i];
    delete idx;
    delete grids;
}

