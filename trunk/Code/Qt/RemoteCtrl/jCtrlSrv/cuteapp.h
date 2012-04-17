/*
 * File       : cuteapp.h
 * Description: Qt ȫ���ȼ�����ƽ̨���
 * Version    : 2012-04-15 Created, Windows Platform
 * Author     : buf1024@gmail.com
 */
#ifndef __48SLOTS_CUTE_APP_H__
#define __48SLOTS_CUTE_APP_H__

#include <QApplication>
#include <QWidget>
#include <QMap>

#include <windows.h>

// ȫ���ȼ���Ϣ
struct HotKeyInfo
{
    QWidget* widget;
    int id;
    unsigned int fsModifiers;
    unsigned int vk;
};

// ȫ���ȼ�Application��
class CuteApp
    : public QApplication
{
    Q_OBJECT

public:
    CuteApp(int argc, char** argv)
        : QApplication(argc, argv)
    {
        hotKeyInfo.clear();
    }
    ~CuteApp()
    {
        hotKeyInfo.clear();
    }
public:
    /* ע��ȫ���ȼ������ô˺���ʱ���мǵ���unregisterHotKey������ο�MSDN
     *
     * widget      ��Ӧȫ���ȼ��Ĵ���
     * id          ȫ���ȼ�ID
     * fsModifiers ���μ�
     * vk          �����
     */
    bool registerHotKey(QWidget* widget, int id,
        unsigned int fsModifiers,
        unsigned int vk)
    {
        if (hotKeyInfo.contains(id)){
            HotKeyInfo& hotKey = hotKeyInfo[id];
            if (widget == hotKey.widget &&
                fsModifiers == hotKey.fsModifiers &&
                vk == hotKey.vk){
                    return true;
            }
            return false;
        }
        
        bool ret = RegisterHotKey(widget->winId(), id, fsModifiers, vk);
        if (ret){
            HotKeyInfo hotKey = {widget, id, fsModifiers, vk};
            hotKeyInfo.insert(id, hotKey);
        }

        return ret;
    }
     /* ȡ��ע��ȫ���ȼ�
      *
      * widget      ��Ӧȫ���ȼ��Ĵ���
      * id          ȫ���ȼ�ID
      */
    bool unregisterHotKey(QWidget* widget, int id)
    {
        if (!hotKeyInfo.contains(id)){
            return true;
        }

        bool ret = UnregisterHotKey(widget->winId(), id);
        if (ret){
            hotKeyInfo.remove(id);
        }

        return ret;
    }
    virtual bool winEventFilter(MSG* msg, long*)
    {
        if (msg->message == WM_HOTKEY){
            emit hotKeyGenerated((int)msg->wParam, 
                LOWORD(msg->lParam), HIWORD(msg->lParam));
            return true;
        }
        return false;
    }

    const QMap<int, HotKeyInfo>& getHotKeyInfo() const
    {
        return hotKeyInfo;
    }

signals:
    /* ���ȼ�����ʱ���������ź�
     * ����ο�MSDN��WM_HOTKEY
     * 
     * id          ȫ���ȼ�ID
     * mod         ���μ�
     * key         �����
     */
    void hotKeyGenerated(int id, int mod, int key);

private:
    QMap<int, HotKeyInfo> hotKeyInfo;
};

#endif /* __48SLOTS_CUTE_APP_H__ */



