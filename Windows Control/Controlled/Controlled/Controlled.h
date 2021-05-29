#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_CONTROLLED_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_CONTROLLED_H_

#include "WinUtils.h"
#include "Kernel.h"
#include "Net.h"
#include <QtCore/Qtimer>
#include <ctime>
#include <QtWidgets/QMainWindow>
#include "ui_Controlled.h"

constexpr std::time_t fps = 60;
constexpr std::time_t flush_ms = 1000 / fps;

class Controlled : public QMainWindow{
    Q_OBJECT

public:
    Controlled(QWidget *parent = Q_NULLPTR);

private slots:
    void FlushNowVolume();

    void on_btn_volume_add_clicked();
    void on_btn_volume_less_clicked();
    void on_btn_volume_set_clicked();


private:
    Ui::ControlledClass ui;
};

#endif