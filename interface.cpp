#include "interface.h"
#include "ui_interface.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

Interface::Interface(QString progName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
    loadTranslators();
    myName = progName;
    initCompleter();
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
    QApplication::removeTranslator(translate);
    delete translate;
}

void Interface::loadTranslators()
{
    translate = new QTranslator();
    QDir dir(QApplication::applicationDirPath());
    dir.setFilter(QDir::Files);
    QFileInfoList list = dir.entryInfoList();
    QRegExp exp(R"(language_(\w+)\.qm)");
    bool isEmpty = true;

    for (int i = 0; i < list.size(); ++i){
        QFileInfo fileInfo = list.at(i);
        if (exp.indexIn(fileInfo.fileName()) == 0){
            ui->language->addItem(exp.cap(1));
            isEmpty = false;
            static bool isLngSet = false;
            if (!isLngSet){
                isLngSet = true;
                translate->load(fileInfo.fileName(), QApplication::applicationDirPath());
                QApplication::installTranslator(translate);
            }
        }
    }

    if (isEmpty){
        ui->language->setHidden(true);
        ui->label_lng->setHidden(true);
    }
}

void Interface::fuckHistoryOf(QString fileName)
{
    QFileInfoList list = getFileList();

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." || fileInfo.fileName() ==  "..")
            continue;
        if (fileInfo.fileName().toLower().indexOf(fileName.toLower()) != -1){
            if (fileInfo.isDir()){
                QDir dir(fileInfo.filePath());
                dir.removeRecursively();
            }
            else QFile::remove(fileInfo.filePath());
        }
    }
}

int Interface::countMatchInHistory()
{
    int count = 0;
    QString fileName = ui->file->text();
    QFileInfoList list = getFileList();

    if (fileName.isEmpty())
        return 0;

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." || fileInfo.fileName() ==  "..")
            continue;
        if (fileInfo.fileName().toLower().indexOf(fileName.toLower()) != -1)
            ++count;
    }
    return count;
}

void Interface::initCompleter()
{
    autoComplete = new QCompleter(listHistory(), this);
    autoComplete->setCaseSensitivity(Qt::CaseInsensitive);
    ui->file->setCompleter(autoComplete);
}

QFileInfoList Interface::getFileList()
{
    QDir dir(QDir::homePath() + "/AppData/Roaming/Microsoft/Windows/Recent/");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::AllEntries | QDir::System);
    QFileInfoList list = dir.entryInfoList();
    dir.setPath("C:\\Windows\\Prefetch\\");
    list += dir.entryInfoList();
    return list;
}

QStringList Interface::listHistory()
{
    QStringList retList;
    QFileInfoList list = getFileList();

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "." || fileInfo.fileName() ==  "..")
            continue;
        retList << fileInfo.fileName();
    }
    return retList;
}

void Interface::on_toolButton_clicked()
{
    QMessageBox msg;
    msg.setText(tr("Укажите название файла или программы, которую хотите удалить.\n"
                "Название можно указывать не полностью, а только его часть.\n\n"
                "Пример. Хотим удалить из истории калькулятор, и мы знаем, что "
                "его exe фал завется calc.exe, по этому напишем в поле ввода "
                "\"calc\" и нажмем кнопку \"Почистить\", в результате чего "
                "калькулятор уйдет из истории."));
    msg.exec();
}

void Interface::on_file_textChanged(const QString &arg1)
{
    int count = countMatchInHistory();
    if (count > 0){
        ui->clear->setEnabled(true);
        ui->matches->setText(tr("Совпадений: ") + QString::number(count));
    } else {
        ui->clear->setEnabled(false);
        ui->matches->setText(tr("Совпадений: 0"));
    }
}

void Interface::on_clear_clicked()
{
    fuckHistoryOf(ui->file->text());
    ui->file->clear();
    delete autoComplete;
    initCompleter();
}

void Interface::on_language_activated(const QString &arg1)
{
    translate->load("language_" + arg1, QApplication::applicationDirPath());
    QApplication::installTranslator(translate);
}
