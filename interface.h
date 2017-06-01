#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include <QApplication>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include <QCompleter>
#include <QTranslator>
#include <QSettings>

namespace Ui {
class Interface;
}

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QString progName, QWidget *parent = 0);
    ~Interface();

    static QStringList listHistory();
    static void fuckHistoryOf(QString fileName);

protected:
    void changeEvent(QEvent *e) override;
    void closeEvent(QCloseEvent * e) override;
    void loadTranslators();
    void setTranslate(QString tr);

    virtual int countMatchInHistory();
    virtual void initCompleter();

    static QFileInfoList getFileList();

    QTranslator *translate;
    QSettings *sets;

private slots:
    void on_toolButton_clicked();

    void on_file_textChanged(const QString &arg1);

    void on_clear_clicked();

    void on_language_activated(const QString &arg1);

private:
    Ui::Interface *ui;
    QString myName;
    QCompleter *autoComplete;
};

#endif // INTERFACE_H
