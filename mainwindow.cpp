#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QAction>
#include<QComboBox>
#include<string>
#include<QDir>
#include<iostream>
#include<unistd.h>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QVideoWidget>
#include<QTimer>
#include<QMenu>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    p=new QProcess(this);//使用qt进程通过控制台调用外部可执行文件
    p1=new QProcess(this);//使用qt进程模式通过控制台调用系统默认软件打开pdf文件
    ui->setupUi(this);

    //网页部分
    view=new QWebEngineView;
    QLayout *layout1=new QVBoxLayout;
    layout1->addWidget(view);
    ui->frame_14->setLayout(layout1);

    //初始的多媒体播放面板和网页面板是不可见的
    ui->frame_12->setVisible(false);
    ui->frame_14->setVisible(false);

    //播放列表每个菜单部分
    menu_of_libOTe=new QMenu;
    menu_of_Plisade=new QMenu;
    menu_of_UC=new QMenu;
    menu_of_SPDZ=new QMenu;
    menu_of_Swanky=new QMenu;

    //libOTe视频菜单项
    libOTe_mp4_1=new QAction;
    libOTe_mp4_2=new QAction;
    libOTe_mp4_3=new QAction;
    libOTe_mp4_1->setText("libOTe算法讲解一");
    libOTe_mp4_2->setText("libOTe算法讲解二");
    libOTe_mp4_3->setText("libOTe算法讲解三");
    libOTe.append(libOTe_mp4_1);
    libOTe.append(libOTe_mp4_2);
    libOTe.append(libOTe_mp4_3);
    menu_of_libOTe->addActions(libOTe);
    connect(libOTe_mp4_1,SIGNAL(triggered()),this,SLOT(play_libOTe_mp4_1()));
    connect(libOTe_mp4_2,SIGNAL(triggered()),this,SLOT(play_libOTe_mp4_2()));
    connect(libOTe_mp4_3,SIGNAL(triggered()),this,SLOT(play_libOTe_mp4_3()));

    //palisade视频菜单项
    palisade_mp4_1=new QAction;
    palisade_mp4_2=new QAction;
    palisade_mp4_3=new QAction;
    palisade_mp4_1->setText("palisade算法讲解一");
    palisade_mp4_2->setText("palisade算法讲解二");
    palisade_mp4_3->setText("palisade算法讲解三");
    palisade.append(palisade_mp4_1);
    palisade.append(palisade_mp4_2);
    palisade.append(palisade_mp4_3);
    menu_of_Plisade->addActions(palisade);
    connect(palisade_mp4_1,SIGNAL(triggered()),this,SLOT(play_palisade_mp4_1()));
    connect(palisade_mp4_2,SIGNAL(triggered()),this,SLOT(play_palisade_mp4_2()));
    connect(palisade_mp4_3,SIGNAL(triggered()),this,SLOT(play_palisade_mp4_3()));

    //UC视频菜单项
    UC_mp4_1=new QAction;
    UC_mp4_2=new QAction;
    UC_mp4_1->setText("UC算法讲解一");
    UC_mp4_2->setText("UC算法讲解二");
    UC.append(UC_mp4_1);
    UC.append(UC_mp4_2);
    menu_of_UC->addActions(UC);
    connect(UC_mp4_1,SIGNAL(triggered()),this,SLOT(play_UC_mp4_1()));
    connect(UC_mp4_2,SIGNAL(triggered()),this,SLOT(play_UC_mp4_2()));

    //SPDZ菜单项
    SPDZ_mp4_1=new QAction;
    SPDZ_mp4_2=new QAction;
    SPDZ_mp4_1->setText("SPDZ算法讲解一");
    SPDZ_mp4_2->setText("SPDZ算法讲解二");
    SPDZ.append(SPDZ_mp4_1);
    SPDZ.append(SPDZ_mp4_2);
    menu_of_SPDZ->addActions(SPDZ);
    connect(SPDZ_mp4_1,SIGNAL(triggered()),this,SLOT(play_SPDZ_mp4_1()));
    connect(SPDZ_mp4_2,SIGNAL(triggered()),this,SLOT(play_SPDZ_mp4_2()));

    //swanky菜单项
    swanky_mp4_1=new QAction;
    swanky_mp4_2=new QAction;
    swanky_mp4_1->setText("Swanky算法讲解一");
    swanky_mp4_2->setText("Swanky算法讲解二");
    swanky.append(swanky_mp4_1);
    swanky.append(swanky_mp4_2);
    menu_of_Swanky->addActions(swanky);
    connect(swanky_mp4_1,SIGNAL(triggered()),this,SLOT(play_swanky_mp4_1()));
    connect(swanky_mp4_2,SIGNAL(triggered()),this,SLOT(play_swanky_mp4_2()));

    //播放源头player部分
    player=new QMediaPlayer(this);

    //播放窗口vd部分
    vd=new QVideoWidget(this);

    //承载播放窗口frame_2面板部分
    QLayout *layout=new QVBoxLayout;
    layout->addWidget(vd);
    ui->widget_3->setLayout(layout);

    //设置播放窗口大小
    vd->setMinimumSize(ui->widget_3->width(),ui->widget_3->height());

    //将播放的视频添加到窗口中
    player->setVideoOutput(vd);
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/快速缩放转场与旋转转场的综合利用.mp4"));

    //进度条部分
    ui->horizontalSlider->setEnabled(true);
    ui->horizontalSlider->setRange(0,maxValue);
    timer = new QTimer();
    timer->setInterval(10);//如果想看起来流畅些，可以把时间间隔调小，如100ms
    //将timer连接至onTimerOut槽函数
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    connect(ui->horizontalSlider,&CustomSlider::costomSliderClicked,this,&MainWindow::slider_progress_clicked);
    connect(ui->horizontalSlider,&CustomSlider::sliderMoved,this,&MainWindow::slider_progress_moved);
    connect(ui->horizontalSlider,&CustomSlider::sliderReleased,this,&MainWindow::slider_progress_released);

    vd->show();//展示视频播放面板

    /*以下为大开始面板的默认可见状态，打开软件时面板都是不可见的，只有点击了对应的按钮才可以设置可见*/
    ui->frame_4->setVisible(false);
    ui->frame_5->setVisible(false);
    ui->frame->setVisible(false);
    ui->frame_6->setVisible(false);
    ui->frame_7->setVisible(false);
    ui->frame_8->setVisible(false);
    ui->frame_9->setVisible(false);
    ui->frame_10->setVisible(false);
    p->setWorkingDirectory("/usr/src/FTGtest/");// 需要设置的运行时默认工作路径

    QObject::connect(p,SIGNAL(readyReadStandardOutput()),this,SLOT(readResult()));//将进程运行的结果输出到程序当中
    //    QObject::connect(p,SIGNAL(readyReadStandardError()),this,SLOT(readError()));//将进程运行的错误输出到程序当中
}

//读取控制台进程输出的内容
void MainWindow::readResult()
{
    QString qb=p->readAllStandardOutput();
    /*以下为使用正则表达式来去除颜色乱码和与测试不相干的信息*/
    qb.replace(QRegExp("\\\\[1m\\\\[34m"),"");
    qb.replace(QRegExp("\\\\[0m\\\\[1m\\\\[32m"),"");
    qb.replace(QRegExp("\\\\[0m"),"");
    qb.replace(QRegExp("\\\\[1m\\\\[32m"),"");
    qb.replace(QRegExp("\\\\[1m\\\\[33m"),"");
    qb.replace(QRegExp("\\\\[1m\\\\[31m"),"");
    qb.replace(QRegExp("Gnuplot not found, disabling plotting"),"");
    if(!qb.isEmpty())
    {
        ui->textBrowser->append(qb);
    }
}

//清空文本框的事件
void MainWindow::clearoutput()
{
    ui->textBrowser->clear();
}

//停止正在进行的进程
void MainWindow::stopprocess()
{
    p->kill();
}

//析构函数
MainWindow::~MainWindow(){

}

//点击“clear"按钮来清空textBrowse文本框中的内容
void MainWindow::on_pushButton_2_clicked()
{
    clearoutput();
}

void MainWindow::on_pushButton_clicked()
{
    p->close();
    stopprocess();
}













/**frontend_libOTe测试板块面板可见控制部分**/
void MainWindow::on_pushButton_7_clicked()
{
    //网址操作
    url="https://github.com/osu-crypto/libOTe";

    //计时器停止
    timer->stop();

    textbrowser_show();


    ui->label_5->setText("frontend_libOTe:第一集");

    //菜单操作
    ui->pushButton_73->setMenu(menu_of_libOTe);


    //视频操作
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/快速缩放转场与旋转转场的综合利用.mp4"));//这个mp4文件只是一个用来测试的文件，如果要更改请放在制定路径下，其它的视频路径同理

    ui->frame_5->setVisible(false);
    ui->frame_7->setVisible(false);
    ui->frame_8->setVisible(false);
    if(ui->frame_4->isVisible()==false){
        ui->frame_4->setVisible(true);
    }
    else{
        ui->frame_4->setVisible(false);
    }
}

/**frontend_libOTe测试部分**/
//快速测试
void MainWindow::on_pushButton_11_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/libOTe/frontend_libOTe -u");
}
//简介
void MainWindow::on_pushButton_3_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/libOTe/frontend_libOTe");
}
//Asm-simplestOT测试
void MainWindow::on_pushButton_8_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/libOTe/frontend_libOTe -simplest-asm ");
}
//SimplestOT测试
void MainWindow::on_pushButton_9_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/libOTe/frontend_libOTe -simplest");
}
//moellerpopf -eke测试
void MainWindow::on_pushButton_4_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/libOTe/frontend_libOTe -moellerpopf -eke");
}
//moellerpopf -mrPopf测试
void MainWindow::on_pushButton_12_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/libOTe/frontend_libOTe -moellerpopf -mrPopf");
}

//mr测试
void MainWindow::on_pushButton_13_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/libOTe/frontend_libOTe -mr");
}
//np测试
void MainWindow::on_pushButton_16_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/libOTe/frontend_libOTe -np");

}
//iknp测试
void MainWindow::on_pushButton_17_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/libOTe/frontend_libOTe -iknp");

}
//kos测试
void MainWindow::on_pushButton_19_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/libOTe/frontend_libOTe -kos");

}
//oos测试

void MainWindow::on_pushButton_20_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/libOTe/frontend_libOTe -oos");

}
//kkrt测试
void MainWindow::on_pushButton_15_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/libOTe/frontend_libOTe -kkrt");
}








/**palisade测试板块面板可见控制部分**/
void MainWindow::on_pushButton_6_clicked()
{
    //网页切换
    url="https://gitlab.com/palisade/palisade-development.git";

    //计时器停止
    timer->stop();

    //可见面板切换
    textbrowser_show();

    ui->label_5->setText("Palisade:第一集");

    ui->pushButton_73->setMenu(menu_of_Plisade);

    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/录制_2022_07_08_15_07_37_522.mp4"));



    ui->frame_4->setVisible(false);
    ui->frame_7->setVisible(false);
    ui->frame_8->setVisible(false);
    if(ui->frame_5->isVisible()==false){
        ui->frame_5->setVisible(true);
    }
    else{
        ui->frame_5->setVisible(false);
    }
}




/**palisade测试部分**/
void MainWindow::on_pushButton_21_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/unittest/binfhe_tests");
}

void MainWindow::on_pushButton_23_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/unittest/core_tests");
}

void MainWindow::on_pushButton_22_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/unittest/pke_tests");

}

void MainWindow::on_pushButton_24_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/binfhe/boolean");
}

void MainWindow::on_pushButton_25_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/binfhe/boolean-serial-binary");
}

void MainWindow::on_pushButton_26_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/binfhe/boolean-truth-tables");
}

void MainWindow::on_pushButton_27_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/binfhe/boolean-ap");

}

void MainWindow::on_pushButton_28_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/binfhe/boolean-serial-json");

}

void MainWindow::on_pushButton_29_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/core/parallel");

}

void MainWindow::on_pushButton_30_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/core/sampling");
}

void MainWindow::on_pushButton_31_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/advanced-real-numbers");
}

void MainWindow::on_pushButton_32_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/advanced-real-numbers-128");

}




void MainWindow::on_pushButton_33_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/depth-bfvrns");

}

void MainWindow::on_pushButton_34_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/depth-bfvrns-b");

}

void MainWindow::on_pushButton_35_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/depth-bgvrns");

}

void MainWindow::on_pushButton_36_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/evalatindex");

}

void MainWindow::on_pushButton_37_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/pke");

}

void MainWindow::on_pushButton_38_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/polynomial_evaluation");

}

void MainWindow::on_pushButton_39_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/pre");

}

void MainWindow::on_pushButton_40_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/pre-buffer");

}

void MainWindow::on_pushButton_41_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/pre-text");

}

void MainWindow::on_pushButton_42_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/simple-integers");

}

void MainWindow::on_pushButton_43_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/simple-integers-bgvrns");

}

void MainWindow::on_pushButton_44_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/simple-integers-serial");

}

void MainWindow::on_pushButton_45_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/simple-integers-serial-bgvrns");

}

void MainWindow::on_pushButton_46_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/simple-real-numbers");

}

void MainWindow::on_pushButton_47_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/simple-real-numbers-serial");

}

void MainWindow::on_pushButton_48_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/palisade-development/build/bin/examples/pke/threshold-fhe");

}





/**palisade面板可见控制部分**/
void MainWindow::on_pushButton_5_clicked()
{
    if(ui->frame->isVisible()==false)
    {
        ui->frame->setVisible(true);
    }
    else
    {
        ui->frame->setVisible(false);
    }
    ui->frame_6->setVisible(false);
}

void MainWindow::on_pushButton_10_clicked()
{
    if(ui->frame_6->isVisible()==false)
    {
        ui->frame_6->setVisible(true);
    }
    else
    {
        ui->frame_6->setVisible(false);
    }
    ui->frame->setVisible(false);
}







//UC面板可见控制部分
void MainWindow::on_pushButton_49_clicked()
{

    //网址切换部分
    url="https://github.com/encryptogroup/UC";

    //计时器停止
    timer->stop();

    textbrowser_show();
    ui->pushButton_73->setMenu(menu_of_UC);
    ui->label_5->setText("UC:第一集");

    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/录制_2022_07_08_15_08_56_179.mp4"));

    ui->frame_4->setVisible(false);
    ui->frame_5->setVisible(false);
    ui->frame_8->setVisible(false);

    if(ui->frame_7->isVisible()==false){
        ui->frame_7->setVisible(true);
    }
    else{
        ui->frame_7->setVisible(false);
    }

}





/*UC的相关测试*/
void MainWindow::on_pushButton_50_clicked()
{
    textbrowser_show();
    ui->textBrowser->append("\n当前用户身份为：");
    p->start("whoami");
    p->waitForFinished();
    ui->textBrowser->append("\n当前工作路径为：");
    p->start("pwd");
    p->waitForFinished();
    p->start("/usr/src/FTGtest/UC/bristol adder_32bit.txt");
    p->waitForFinished();
    p->start("/usr/src/FTGtest/UC/UC adder_32bit.txt_SHDL.circuit");
}


void MainWindow::on_pushButton_52_clicked()
{
    textbrowser_show();
    ui->textBrowser->append("\n当前用户身份为：");
    p->start("whoami");
    p->waitForFinished();
    ui->textBrowser->append("\n当前工作路径为：");
    p->start("pwd");
    p->waitForFinished();
    p->start("/usr/src/FTGtest/UC/bristol comparator_32bit_signed_lt.txt");
    p->waitForFinished();
    p->start("/usr/src/FTGtest/UC/UC comparator_32bit_signed_lt.txt_SHDL.circuit");
}

void MainWindow::on_pushButton_51_clicked()
{
    textbrowser_show();
    ui->textBrowser->append("\n当前用户身份为：");
    p->start("whoami");
    p->waitForFinished();
    ui->textBrowser->append("\n当前工作路径为：");
    p->start("pwd");
    p->waitForFinished();
    //    p->start("/usr/src/FTGtest/UC/bristol CreditChecking.txt");
    p->waitForFinished();
    p->start("/usr/src/FTGtest/UC/UC CreditChecking.circuit");
}

void MainWindow::on_pushButton_54_clicked()
{
    textbrowser_show();
    ui->textBrowser->append("\n当前用户身份为：");
    p->start("whoami");
    p->waitForFinished();
    ui->textBrowser->append("\n当前工作路径为：");
    p->start("pwd");
    p->waitForFinished();
    p->start("/usr/src/FTGtest/UC/bristol mult_32x32.txt");
    p->waitForFinished();
    p->start("/usr/src/FTGtest/UC/UC mult_32x32.txt_SHDL.circuit");
}

void MainWindow::on_pushButton_53_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/UC/UC MobileCode.circuit");
}



//MP-SPDZ部分测试
void MainWindow::on_pushButton_55_clicked()
{

    //网址切换部分
    url="https://github.com/data61/MP-SPDZ";

    //计时器停止
    timer->stop();

    ui->label_5->setText("SPDZ:第一集");
    ui->pushButton_73->setMenu(menu_of_SPDZ);
    textbrowser_show();


    //多媒体源头切换
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/录制_2022_07_08_15_10_00_424.mp4"));

    ui->frame_4->setVisible(false);
    ui->frame_5->setVisible(false);
    ui->frame_7->setVisible(false);
    ui->frame_8->setVisible(false);

    p->setWorkingDirectory("/usr/src/FTGtest/MP-SPDZ/");// 转移工作路径
    p->start("Scripts/mascot.sh tutorial");
}



//swanky测试板块可见部分
void MainWindow::on_pushButton_56_clicked()
{
    //网址切换
    url="https://github.com/GaloisInc/swanky";

    //计时器停止
    timer->stop();

    textbrowser_show();
    ui->label_5->setText("Swanky:第一集");
    ui->pushButton_73->setMenu(menu_of_Swanky);

    //多媒体源头切换
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/录制_2022_07_08_15_10_51_351.mp4"));

    ui->frame_4->setVisible(false);
    ui->frame_5->setVisible(false);
    ui->frame_7->setVisible(false);
    if(ui->frame_8->isVisible()==false){
        ui->frame_8->setVisible(true);
    }
    else{
        ui->frame_8->setVisible(false);
    }
}



//swanky综合测试部分
void MainWindow::on_pushButton_57_clicked()
{
    p->setWorkingDirectory("/usr/src/FTGtest/swanky/target/debug/deps/");// 转移工作路径
    if(ui->frame_10->isVisible()){
        ui->frame_10->setVisible(false);
    }
    else{
        ui->frame_10->setVisible(true);
    }
    ui->frame_9->setVisible(false);

    //    ui->textBrowser->append("当前用户身份为：");
    //    p->start("whoami");
    //    p->waitForFinished(-1);
    //    ui->textBrowser->append("当前工作路径为：");
    //    p->start("pwd");
    //    p->waitForFinished(-1);
    //    sleep(2);
    //    p->start("./target/debug/deps/aes128-91f358f1377134cb");
    //    p->start("./target/debug/deps/aes128-91f358f1377134cb");
    //    p->waitForFinished(-1);
    //    ui->textBrowser->append("测试结束");
    //    p->start("./target/debug/deps/aes256-a319e7a92d3df083");
    //    p->waitForStarted(-1);
    //    ui->textBrowser->append("正在执行AES256测试......");
    //    p->waitForFinished(-1);
    //    ui->textBrowser->append("测试结束");
}


//swanky样例测试面板
void MainWindow::on_pushButton_58_clicked()
{

    p->setWorkingDirectory("/usr/src/FTGtest/swanky/");// 转移工作路径

    if(ui->frame_9->isVisible()){
        ui->frame_9->setVisible(false);
    }
    else{
        ui->frame_9->setVisible(true);
    }
    ui->frame_10->setVisible(false);
}

//kkrt测试
void MainWindow::on_pushButton_59_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/swanky/target/debug/examples/kkrt");
}

void MainWindow::on_pushButton_60_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/swanky/target/debug/examples/kmprt");

}

void MainWindow::on_pushButton_61_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/swanky/target/debug/examples/psz");

}



void MainWindow::on_pushButton_62_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/swanky/target/debug/examples/psz-payload");

}

void MainWindow::on_pushButton_63_clicked()
{
    textbrowser_show();
    p->start("/usr/src/FTGtest/swanky/target/debug/examples/semihonest_2pc");

}





//关于视频播放部分
void MainWindow::on_pushButton_65_clicked()
{
    ui->pushButton_72->setText("暂停");
    player->play();
    timer->start();
    ui->textBrowser->setVisible(false);
    ui->frame_14->setVisible(false);
    ui->frame_12->setVisible(true);
}

//关于视频播放条的操作
void MainWindow::onTimerOut()
{
    ui->horizontalSlider->setValue(static_cast<int>(player->position()*maxValue/player->duration()));
}
void MainWindow::slider_progress_clicked()
{
    player->setPosition(ui->horizontalSlider->value()*player->duration()/maxValue);
}
void MainWindow::slider_progress_moved()
{
    //暂时停止计时器，在用户拖动过程中不修改slider的值
    timer->stop();
    player->setPosition(ui->horizontalSlider->value()*player->duration()/maxValue);
}
void MainWindow::slider_progress_released()
{

    //用户释放滑块后，重启定时器
    timer->start();
}

//多媒体面板中播放时选择暂停或者继续播放
void MainWindow::on_pushButton_72_clicked()
{
    if(player->state()==QMediaPlayer::PausedState){
        ui->pushButton_72->setText("暂停");
        player->play();
    }
    else if(player->state()==QMediaPlayer::PlayingState){
        ui->pushButton_72->setText("播放");
        player->pause();
    }
    else if(player->state()==QMediaPlayer::StoppedState){
        ui->pushButton_72->setText("暂停");
        timer->start();
        player->play();
    }
}


//打开网址的按钮
void MainWindow::on_pushButton_66_clicked()
{
    //    QDesktopServices::openUrl(QUrl(url));
    ui->textBrowser->setVisible(false);
    ui->frame_12->setVisible(false);
    ui->frame_14->setVisible(true);
    view->setUrl(QUrl(url));
}


//office操作
void MainWindow::on_pushButton_64_clicked()
{
    p1->start("evince /usr/src/FTGtest/office/libOTe.pdf");
}


//展示文本框
void MainWindow::textbrowser_show(){
    player->pause();
    ui->frame_12->setVisible(false);
    ui->frame_14->setVisible(false);
    ui->textBrowser->setVisible(true);
}

//libOTe视频播放分集
void MainWindow::play_libOTe_mp4_1(){
    timer->stop();
    ui->label_5->setText("frontend_libOTe:第一集");
    ui->pushButton_72->setText("播放");
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/快速缩放转场与旋转转场的综合利用.mp4"));

}
void MainWindow::play_libOTe_mp4_2(){
    timer->stop();
    ui->label_5->setText("frontend_libOTe:第二集");
    ui->pushButton_72->setText("播放");
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/录制_2022_07_08_15_10_00_424.mp4"));
}
void MainWindow::play_libOTe_mp4_3(){
    timer->stop();
    ui->label_5->setText("frontend_libOTe:第三集");
    ui->pushButton_72->setText("播放");
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/录制_2022_07_08_15_08_56_179.mp4"));
}




//palisade视频播放分集
void MainWindow::play_palisade_mp4_1(){
    timer->stop();
    ui->label_5->setText("Palisade:第一集");
    ui->pushButton_72->setText("播放");
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/录制_2022_07_08_15_07_37_522.mp4"));
}
void MainWindow::play_palisade_mp4_2(){
    timer->stop();
    ui->label_5->setText("Palisade:第二集");
    ui->pushButton_72->setText("播放");
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/快速缩放转场与旋转转场的综合利用.mp4"));
}
void MainWindow::play_palisade_mp4_3(){
    timer->stop();
    ui->label_5->setText("Palisade:第三集");
    ui->pushButton_72->setText("播放");
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/录制_2022_07_08_15_10_51_351.mp4"));
}



//UC视频播放分集
void MainWindow::play_UC_mp4_1(){
    timer->stop();
    ui->label_5->setText("UC:第一集");
    ui->pushButton_72->setText("播放");
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/录制_2022_07_08_15_08_56_179.mp4"));
}
void MainWindow::play_UC_mp4_2(){
    timer->stop();
    ui->label_5->setText("UC:第二集");
    ui->pushButton_72->setText("播放");
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/录制_2022_07_08_15_07_37_522.mp4"));
}

//SPDZ视频部分分集
void MainWindow::play_SPDZ_mp4_1(){
    timer->stop();
    ui->label_5->setText("SPDZ:第一集");
    ui->pushButton_72->setText("播放");
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/录制_2022_07_08_15_10_00_424.mp4"));
}
void MainWindow::play_SPDZ_mp4_2(){
    timer->stop();
    ui->label_5->setText("SPDZ:第二集");
    ui->pushButton_72->setText("播放");
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/快速缩放转场与旋转转场的综合利用.mp4"));
}

//Swanky视频部分分集
void MainWindow::play_swanky_mp4_1(){
    timer->stop();
    ui->label_5->setText("Swanky:第一集");
    ui->pushButton_72->setText("播放");
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/录制_2022_07_08_15_10_51_351.mp4"));
}
void MainWindow::play_swanky_mp4_2(){
    timer->stop();
    ui->label_5->setText("Swanky:第二集");
    ui->pushButton_72->setText("播放");
    player->setMedia(QUrl::fromLocalFile("/usr/src/FTGtest/media/录制_2022_07_08_15_07_37_522.mp4"));
}


//swanky单元测试
void MainWindow::on_pushButton_67_clicked()
{
    textbrowser_show();
    p->start("./fancy_garbling-b0de9511caa54b92");
}

void MainWindow::on_pushButton_68_clicked()
{
    textbrowser_show();
    p->start("./popsicle-3fc8239d965965a0");
}

void MainWindow::on_pushButton_69_clicked()
{
    textbrowser_show();
    p->start("./ocelot-7e5c8013d9ddfe22");
}

void MainWindow::on_pushButton_70_clicked()
{
    textbrowser_show();
    p->start("./scuttlebutt-7c8b91f6251c0cef");
}
