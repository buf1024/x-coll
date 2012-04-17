#ifndef __48SLOTS_SETTINGDLG_H__
#define __48SLOTS_SETTINGDLG_H__

#include <QDialog>

class QDialogButtonBox;
class QTabWidget;
class QAbstractButton;
class QShowEvent;

class SettingPage
    : public QWidget
{
    Q_OBJECT

public:
    SettingPage(QWidget* parent = 0);
    ~SettingPage();

signals:
    void pageModified(QWidget* widget);
};

class GeneralPage
    : public SettingPage
{
    Q_OBJECT

public:
    GeneralPage(QWidget* parent = 0);
    ~GeneralPage();
};

class AboutPage
    : public SettingPage
{
    Q_OBJECT

public:
    AboutPage(QWidget* parent = 0);
    ~AboutPage();
};

class SettingDlg
    : public QDialog
{
    Q_OBJECT

public:
    SettingDlg(QWidget* parent = 0);
    ~SettingDlg();

protected:
    void showEvent(QShowEvent* event);

private:
    void initDefaultSetting();
    void initSetting();

public slots:
    void onButtonClicked(QAbstractButton* button);
    void onPageChanged(int index);
    void onPageModified(QWidget* widget);

private:
    QDialogButtonBox* buttonBox;
    QTabWidget* tabWidget;

    bool propertyChanged;
};


#endif /* __48SLOTS_SETTINGDLG_H__ */







