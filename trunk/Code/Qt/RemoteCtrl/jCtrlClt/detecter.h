
#ifndef __48SLOTS_DETECTER_H__
#define __48SLOTS_DETECTER_H__

#include <QThread>

class Detecter
    : public QThread
{
    Q_OBJECT

public:
    Detecter(QObject* parent = 0);
    ~Detecter();
};


#endif /* __48SLOTS_DETECTER_H__ */

