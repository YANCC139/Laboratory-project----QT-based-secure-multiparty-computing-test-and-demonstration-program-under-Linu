#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QProcess>
#include<QPushButton>
#include<QComboBox>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QVideoWidget>
#include<customslider.h>
#include<QTimer>
#include<QUrl>
#include<QDesktopServices>
#include<QtWebEngineWidgets/QWebEngineView>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    //关于播放视频部分
    //与Slider有关的播放控制变量
    QTimer * timer;
    int maxValue = 1000;//设置进度条的最大值

    ~MainWindow();

private slots:
    void readResult();
    void clearoutput();
    void stopprocess();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();





    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();





    void on_pushButton_11_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_41_clicked();

    void on_pushButton_42_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_45_clicked();

    void on_pushButton_46_clicked();

    void on_pushButton_47_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_50_clicked();

    void on_pushButton_49_clicked();

    void on_pushButton_52_clicked();

    void on_pushButton_51_clicked();

    void on_pushButton_54_clicked();

    void on_pushButton_53_clicked();

    void on_pushButton_55_clicked();

    void on_pushButton_56_clicked();

    void on_pushButton_57_clicked();

    void on_pushButton_58_clicked();

    void on_pushButton_59_clicked();

    void on_pushButton_60_clicked();

    void on_pushButton_61_clicked();

    void on_pushButton_62_clicked();

    void on_pushButton_63_clicked();

    void on_pushButton_65_clicked();



    //多媒体播放部分的函数
    void onTimerOut();
    void slider_progress_clicked();
    void slider_progress_moved();
    void slider_progress_released();

    void on_pushButton_72_clicked();


    void on_pushButton_66_clicked();

    void on_pushButton_64_clicked();

    void textbrowser_show();//展示文本框的控件

    void play_libOTe_mp4_3();//播放libOTe第三集
    void play_libOTe_mp4_2();//播放libOTe第二集
    void play_libOTe_mp4_1();//播放libOTe第一集

    void play_palisade_mp4_1();//播放palisade第一集
    void play_palisade_mp4_2();//播放palisade第二集
    void play_palisade_mp4_3();//播放palisade第三集

    void play_UC_mp4_1();//播放UC第一集
    void play_UC_mp4_2();//播放UC第二集

    void play_SPDZ_mp4_1();//播放SPDZ第一集
    void play_SPDZ_mp4_2();//播放SDPZ第二集

    void play_swanky_mp4_1();
    void play_swanky_mp4_2();


    void on_pushButton_67_clicked();

    void on_pushButton_68_clicked();

    void on_pushButton_69_clicked();

    void on_pushButton_70_clicked();

private:
    Ui::MainWindow *ui;
    QProcess *p;
    QProcess *p1;

    bool frame4=false;
    bool frame5=false;
    bool frame7=false;
    bool frame8=false;

    bool frame=false;//palisade unittest下的frame
    bool frame6=false;//palisade example下的frame



    //播放列表中的菜单
    QMenu *menu_of_libOTe;
    QMenu *menu_of_Plisade;
    QMenu *menu_of_UC;
    QMenu *menu_of_SPDZ;
    QMenu *menu_of_Swanky;


    //frontend_libOTe菜单项
    QAction *libOTe_mp4_1;
    QAction *libOTe_mp4_2;
    QAction *libOTe_mp4_3;
    QList<QAction*> libOTe;


    //palisade菜单项
    QAction *palisade_mp4_1;
    QAction *palisade_mp4_2;
    QAction *palisade_mp4_3;
    QList<QAction*> palisade;


    //UC菜单项
    QAction *UC_mp4_1;
    QAction *UC_mp4_2;
    QList<QAction*> UC;


    //SPDZ菜单项
    QAction *SPDZ_mp4_1;
    QAction *SPDZ_mp4_2;
    QList<QAction*> SPDZ;


    //swanky菜单项
    QAction *swanky_mp4_1;
    QAction *swanky_mp4_2;
    QList<QAction*> swanky;

    //视频播放
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QVideoWidget *vd;



    //网址操作
    QString url;
    QWebEngineView *view;

};

#endif // MAINWINDOW_H
