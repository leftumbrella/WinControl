#include "Controlled.h"

Controlled::Controlled(QWidget *parent) : QMainWindow(parent){
    ui.setupUi(this);

    this->setWindowIcon(QIcon(":/main/D:/Pictures/Umbrella/icon.ico"));

    QTimer* timer_ptr = new QTimer(this);

    connect(timer_ptr, &QTimer::timeout, this, &Controlled::FlushNowVolume);

    timer_ptr->start(flush_ms);

    //这个习惯来自于 GTTC.
    Kernel::GetInstance()->Initialize().Run();

    //为状态栏提示当前IP地址
    QString ip_str = QStringLiteral("当前 IPV4 地址  ");
    ip_str += QString::fromStdString(WinUtils::GetIpV4());
    ui.statusBar->showMessage(ip_str);

}
void Controlled::FlushNowVolume() {
    ui.LB_volume_now->setText(QString::number(WinUtils::Volume()));
}

void Controlled::on_btn_volume_add_clicked() {
    WinUtils::Volume(WinUtils::Volume() + 1);
}
void Controlled::on_btn_volume_less_clicked() {
    WinUtils::Volume(WinUtils::Volume() - 1);
}
void Controlled::on_btn_volume_set_clicked() {
    int volume = ui.SB_volume->value();
    WinUtils::Volume(static_cast<unsigned int>(volume));
}