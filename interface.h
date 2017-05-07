#ifndef INTERFACE_H
#define INTERFACE_H

#include <QtWidgets/QMainWindow>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include <QCompleter>

namespace Ui {
class Interface;
}

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QString progName, QWidget *parent = 0);
    ~Interface();

    static QStringList listHistoryOf();
    static void fuckHistoryOf(QString fileName);

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent * e);

    virtual int countHistoryOf();
    virtual void initCompleter();

private slots:
    void on_toolButton_clicked();

    void on_file_textChanged(const QString &arg1);

    void on_clear_clicked();

private:
    Ui::Interface *ui;
    QString myName;
    QCompleter *autoComplete;
};

#endif // INTERFACE_H
