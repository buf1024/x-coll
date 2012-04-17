#ifndef __48SLOTS_SETTINGDLG_H__
#define __48SLOTS_SETTINGDLG_H__

#include <QDialog>

class QDialogButtonBox;
class QTabWidget;
class QAbstractB

class GeneralPage
    : public QWidget
{
    Q_OBJECT

public:
    GeneralPage(QWidget* parent = 0);
    ~GeneralPage();
};

class AboutPage
    : public QWidget
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

private:
    void initSetting();

public slots:
    void onButtonClicked(QAbstractButton* button);
    void onPageChanged(int index);

private:
    QDialogButtonBox* buttonBox;
    QTabWidget* tabWidget;
};


#endif /* __48SLOTS_SETTINGDLG_H__ */







