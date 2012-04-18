#include "settingdlg.h"

#include <QDialogButtonBox>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QShowEvent>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QSize>
#include <QApplication>
#include <QDesktopWidget>

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
    text = new QTextEdit(this);
    text->setReadOnly(true);

    QString msg = tr("jCtrlSrv Qt version\n\n\nbuf1024@gmail.com");

    QFile file(":/res/about.html");
    if (file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        msg = in.readAll();
    }
    text->setHtml(msg);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setSizeConstraint(QLayout::SetNoConstraint);
    layout->addWidget(text);
    setLayout(layout);
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

    centerWidget();
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

void SettingDlg::centerWidget()
{
    static QSize desktopSize = QApplication::desktop()->size();
    static int w = desktopSize.width()/2;
    static int h = desktopSize.height()/2;
    static int x = (desktopSize.width() - w) / 2;
    static int y = (desktopSize.height() - h) / 2;

    setFixedHeight(h);
    setFixedWidth(w);
    setGeometry(x, y, w, h);
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