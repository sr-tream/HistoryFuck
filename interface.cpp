#include "interface.h"
#include "ui_interface.h"

Interface::Interface(QString progName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
    myName = progName;
    autoComplete = new QCompleter(listHistoryOf(), this);
    autoComplete->setCaseSensitivity(Qt::CaseInsensitive);
//    QMessageBox msg;
//    QDir dir(QDir::homePath());
//    msg.setText(dir.path() + "\n" + QString::number(dir.entryInfoList().size())); msg.exec();
//    dir.setPath(QDir::homePath() + "/AppData/");
//    msg.setText(dir.path() + "\n" + QString::number(dir.entryInfoList().size())); msg.exec();
//    dir.setPath(QDir::homePath() + "/AppData/Roaming/");
//    msg.setText(dir.path() + "\n" + QString::number(dir.entryInfoList().size())); msg.exec();
//    dir.setPath(QDir::homePath() + "/AppData/Roaming/Microsoft/");
//    msg.setText(dir.path() + "\n" + QString::number(dir.entryInfoList().size())); msg.exec();
//    dir.setPath(QDir::homePath() + "/AppData/Roaming/Microsoft/Windows/");
//    msg.setText(dir.path() + "\n" + QString::number(dir.entryInfoList().size())); msg.exec();
//    dir.setPath(QDir::homePath() + "/AppData/Roaming/Microsoft/Windows/Recent/");
//    msg.setText(dir.path() + "\n" + QString::number(dir.entryInfoList().size())); msg.exec();
}

Interface::~Interface()
{
    delete ui;
}

void Interface::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Interface::closeEvent(QCloseEvent *e)
{
    fuckHistoryOf(myName);
}

void Interface::fuckHistoryOf(QString fileName)
{
    QDir dir(QDir::homePath() + "/AppData/Roaming/Microsoft/Windows/Recent/");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::AllEntries | QDir::System);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." || fileInfo.fileName() ==  "..")
            continue;
        if (fileInfo.fileName().toLower().indexOf(fileName.toLower()) != -1)
            QFile::remove(fileInfo.filePath());
    }
    dir.setPath("C:\\Windows\\Prefetch\\");
    list.clear();
    list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." || fileInfo.fileName() ==  "..")
            continue;
        if (fileInfo.fileName().toLower().indexOf(fileName.toLower()) != -1)
            QFile::remove(fileInfo.filePath());
    }
}

bool Interface::checkHistoryOf()
{
    QString fileName = ui->file->text();
    if (fileName.isEmpty())
        return false;

    QDir dir(QDir::homePath() + "/AppData/Roaming/Microsoft/Windows/Recent/");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::AllEntries | QDir::System);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." || fileInfo.fileName() ==  "..")
            continue;
        if (fileInfo.fileName().toLower().indexOf(fileName.toLower()) != -1)
            return true;
    }
    dir.setPath("C:\\Windows\\Prefetch\\");
    list.clear();
    list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." || fileInfo.fileName() ==  "..")
            continue;
        if (fileInfo.fileName().toLower().indexOf(fileName.toLower()) != -1)
            return true;
    }

    return false;
}

int Interface::countHistoryOf()
{
    QString fileName = ui->file->text();
    int count = 0;
    QDir dir(QDir::homePath() + "/AppData/Roaming/Microsoft/Windows/Recent/");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::AllEntries | QDir::System);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." || fileInfo.fileName() ==  "..")
            continue;
        if (fileInfo.fileName().toLower().indexOf(fileName.toLower()) != -1)
            ++count;
    }
    dir.setPath("C:\\Windows\\Prefetch\\");
    list.clear();
    list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." || fileInfo.fileName() ==  "..")
            continue;
        if (fileInfo.fileName().toLower().indexOf(fileName.toLower()) != -1)
            ++count;
    }
    return count;
}

QStringList Interface::listHistoryOf()
{
    QStringList retList;
    QDir dir(QDir::homePath() + "/AppData/Roaming/Microsoft/Windows/Recent/");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::AllEntries | QDir::System);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." || fileInfo.fileName() ==  "..")
            continue;
        retList << fileInfo.fileName();
    }
    dir.setPath("C:\\Windows\\Prefetch\\");
    list.clear();
    list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." || fileInfo.fileName() ==  "..")
            continue;
        bool add = true;
        for (int j = 0; j < retList.size(); ++j)
            if (retList[j] == fileInfo.fileName())
                add = false;
        if (add)
            retList << fileInfo.fileName();
    }
    return retList;
}

void Interface::on_toolButton_clicked()
{
    QMessageBox msg;
    msg.setText("Укажите название файла или программы, которую хотите удалить.\n"
                "Название можно указывать не полностью, а только его часть.\n\n"
                "Пример. Хотим удалить из истории калькулятор, и мы знаем, что "
                "его exe фал завется calc.exe, по этому напишем в поле ввода "
                "\"calc\" и нажмем кнопку \"Почистить\", в результате чего "
                "калькулятор уйдет из истории.");
    msg.exec();
}

void Interface::on_file_textChanged(const QString &arg1)
{
    if (checkHistoryOf()){
        ui->clear->setEnabled(true);
        ui->file->setCompleter(autoComplete);
        ui->matches->setText("Совпадений: " + QString::number(countHistoryOf()));
    } else {
        ui->clear->setEnabled(false);
        ui->matches->setText("Совпадений: 0");
    }
}

void Interface::on_clear_clicked()
{
    fuckHistoryOf(ui->file->text());
    ui->file->clear();
}
