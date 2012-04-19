#include "connectdlg.h"

ConnectDlg::ConnectDlg(QWidget* parent)
: QDialog(parent)
{

}
ConnectDlg::~ConnectDlg()
{

}

QString ConnectDlg::getHostAddress()
{
    return "127.0.0.1";
}
QString ConnectDlg::getHostPort()
{
    return "50204";
}
QString ConnectDlg::getExchangeKey()
{
    return "123";
}