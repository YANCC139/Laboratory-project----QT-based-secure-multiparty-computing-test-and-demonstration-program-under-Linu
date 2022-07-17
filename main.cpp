#include "mainwindow.h"
#include <QApplication>
#include <qdesktopwidget.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //以下为设置程序居中显示
    QDesktopWidget *desktop = QApplication::desktop();
    w.resize(1568,882);
    w.move((desktop->width() - w.width())/ 2, (desktop->height() - w.height()) /2);
    //设置程序窗口尺寸
    w.show();
    //    w.showFullScreen();//
    return a.exec();
}

