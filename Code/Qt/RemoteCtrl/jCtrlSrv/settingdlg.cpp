#include "settingdlg.h"

#include <QDialogButtonBox>
#include <QTabWidget>

// general page
GeneralPage::GeneralPage(QWidget* parent)
: QWidget(parent)
{

}
GeneralPage::~GeneralPage()
{

}


// about page
AboutPage::AboutPage(QWidget* parent)
: QWidget(parent)
{

}
AboutPage::~AboutPage()
{

}

// setting dialog
SettingDlg::SettingDlg(QWidget* parent)
: QDialog(parent)
{
    initSetting();
}
SettingDlg::~SettingDlg()
{

}

void SettingDlg::initSetting()
{
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
        QDialogButtonBox::Apply | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));

    tabWidget = new QTabWidget;
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onPageChanged(int)));

    int index = 0;
    // general page
    tabWidget->insertTab(index++, new GeneralPage, tr("General"));
    tabWidget->insertTab(index++, new AboutPage, tr("About"));
}

void SettingDlg::onButtonClicked(QAbstractButton* button)
{

}
void SettingDlg::onPageChanged(int index)
{

}