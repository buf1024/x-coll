#include "settingdlg.h"

#include <QDialogButtonBox>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QShowEvent>

SettingPage::SettingPage(QWidget* parent)
: QWidget(parent)
{

}
SettingPage::~SettingPage()
{

}

// general page
GeneralPage::GeneralPage(QWidget* parent)
: SettingPage(parent)
{

}
GeneralPage::~GeneralPage()
{

}


// about page
AboutPage::AboutPage(QWidget* parent)
: SettingPage(parent)
{

}
AboutPage::~AboutPage()
{

}

// setting dialog
SettingDlg::SettingDlg(QWidget* parent)
: QDialog(parent)
{
    initDefaultSetting();
}
SettingDlg::~SettingDlg()
{

}
void SettingDlg::showEvent(QShowEvent* event)
{
    initSetting();
    event->accept();
}
void SettingDlg::initSetting()
{
    propertyChanged = false;

    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(false);
    buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);

    tabWidget->setCurrentIndex(0);
}
void SettingDlg::initDefaultSetting()
{
    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Apply);
    buttonBox->addButton(QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));

    tabWidget = new QTabWidget;
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onPageChanged(int)));

    int index = 0;
    QWidget* pageWidget = NULL;
    // general page
    pageWidget = new GeneralPage;
    connect(pageWidget, SIGNAL(pageModified(QWidget*)), this, SLOT(onPageModified(QWidget*)));
    tabWidget->insertTab(index++, pageWidget, tr("General"));

    pageWidget = new AboutPage;
    connect(pageWidget, SIGNAL(pageModified(QWidget*)), this, SLOT(onPageModified(QWidget*)));
    tabWidget->insertTab(index++, pageWidget, tr("About"));

    // setup window
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Setting Dialog"));
}

void SettingDlg::onButtonClicked(QAbstractButton* button)
{
    if (button == buttonBox->button(QDialogButtonBox::Ok)
        || button == buttonBox->button(QDialogButtonBox::Apply)){
            if (propertyChanged){
                // change setting
            }
    }
    hide();
    
}
void SettingDlg::onPageChanged(int)
{

}
void SettingDlg::onPageModified(QWidget*)
{
    buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);

    propertyChanged = true;
}