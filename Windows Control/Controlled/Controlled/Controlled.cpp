#include "Controlled.h"

Controlled::Controlled(QWidget *parent) : QMainWindow(parent){
    ui.setupUi(this);

    QTimer* timer_ptr = new QTimer(this);

    connect(timer_ptr, &QTimer::timeout, this, &Controlled::FlushNowVolume);

    timer_ptr->start(flush_ms);

    
    Kernel::GetInstance()->Initialize().Run();


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