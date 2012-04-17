/*
 * File       : cuteapp.h
 * Description: Qt 全局热键，与平台相关
 * Version    : 2012-04-15 Created, Windows Platform
 * Author     : buf1024@gmail.com
 */
#ifndef __48SLOTS_CUTE_APP_H__
#define __48SLOTS_CUTE_APP_H__

#include <QApplication>
#include <QWidget>
#include <QMap>

#include <windows.h>

// 全局热键消息
struct HotKeyInfo
{
    QWidget* widget;
    int id;
    unsigned int fsModifiers;
    unsigned int vk;
};

// 全局热键Application类
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
    /* 注册全局热键，调用此函数时，切记调用unregisterHotKey，更多参考MSDN
     *
     * widget      响应全局热键的窗口
     * id          全局热键ID
     * fsModifiers 修饰键
     * vk          虚拟键
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
     /* 取消注册全局热键
      *
      * widget      响应全局热键的窗口
      * id          全局热键ID
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
    /* 当热键产生时，产生此信号
     * 更多参考MSDN，WM_HOTKEY
     * 
     * id          全局热键ID
     * mod         修饰键
     * key         虚拟键
     */
    void hotKeyGenerated(int id, int mod, int key);

private:
    QMap<int, HotKeyInfo> hotKeyInfo;
};

#endif /* __48SLOTS_CUTE_APP_H__ */



