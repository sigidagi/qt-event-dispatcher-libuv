#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QList>
#include <QScopedPointer>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>

#include "xmlhandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_teamMemberView(new TeamMemberView()), m_teamView(new TeamView()),
      m_loadDialog(new QFileDialog(this)) {
    ui->setupUi(this);

    setWindowTitle(QStringLiteral("EntUI Stand-up Bingo"));

    ui->viewLayout->addWidget(m_teamMemberView);
    ui->viewLayout->addWidget(m_teamView);
    ui->viewLayout->setStretch(1, 1);

    m_loadDialog->setAcceptMode(QFileDialog::AcceptOpen);
    m_loadDialog->setFileMode(QFileDialog::ExistingFile);
    m_loadDialog->setNameFilter(QStringLiteral("XML Files (*.xml)"));

    connectUi();
}

const TeamMemberView *MainWindow::teamMemberView() { return m_teamMemberView; }

void MainWindow::connectUi() {
    connect(m_teamMemberView, SIGNAL(teamMemberAddedModel(QString)), m_teamView, SLOT(onTeamMemberAdded(QString)));
    connect(m_teamMemberView->getModel(), SIGNAL(teamMemberRemoved(int)), m_teamView, SLOT(onTeamMemberRemoved(int)));

    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(onSaveFileTriggered()));

    connect(ui->actionLoad, SIGNAL(triggered()), m_loadDialog, SLOT(show()));
    connect(m_loadDialog, SIGNAL(fileSelected(QString)), this, SLOT(onLoadFileSelected(QString)));
}

void MainWindow::onSaveFileTriggered() {
    const QString fileSavePath = QFileDialog::getSaveFileName(this, "Save team members", "team_members.xml");

    onSaveFileSelected(fileSavePath);
}

void MainWindow::onSaveFileSelected(QString file) {
    QScopedPointer<xmlHandler> saveHandler(new xmlHandler());

    connect(saveHandler.get(), SIGNAL(fileStatus(QString)), ui->statusBar, SLOT(showMessage(QString)));

    saveHandler->saveMembersToFile(m_teamMemberView->getModel()->getModel(), file);
}

void MainWindow::onLoadFileSelected(QString file) {
    QScopedPointer<xmlHandler> loadHandler(new xmlHandler());
    QScopedPointer<QFile> loadFile(new QFile(file));

    // Maybe better API call here?
    m_teamMemberView->getModel()->getModel()->clear();
    m_teamView->onClearTeamMembers();

    connect(loadHandler.get(), SIGNAL(teamMemberAdded(QString)), m_teamMemberView->getModel(),
            SLOT(onTeamMemberAdded(QString)));
    connect(loadHandler.get(), SIGNAL(fileStatus(QString)), ui->statusBar, SLOT(showMessage(QString)));

    loadHandler->setTeamMembers(loadFile.get());
}

MainWindow::~MainWindow() { delete ui; }
