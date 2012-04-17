/*
 客户端主功能
 */

#ifndef __48SLOTS_CTRL_CLT_H__
#define __48SLOTS_CTRL_CLT_H__

#include <QWidget>

class CtrlCtl
    : public QWidget
{
    Q_OBJECT

public:
    CtrlCtl(QWidget* parent = 0);
    ~CtrlCtl();

public:
    void start();
};

#endif /* __48SLOTS_CTRL_CLT_H__ */

