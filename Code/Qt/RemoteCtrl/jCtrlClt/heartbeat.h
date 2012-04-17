#ifndef __48SLOTS_HEART_BEAT_H__
#define __48SLOTS_HEART_BEAT_H__

#include <QThread>

class HeartBeat
    : public QThread
{
    Q_OBJECT

public:
    HeartBeat(QObject* parent = 0);
    ~HeartBeat();
};


#endif /* __48SLOTS_HEART_BEAT_H__ */

