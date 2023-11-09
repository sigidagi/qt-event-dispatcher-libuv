#include "teammemberview.h"
#include "ui_teammemberview.h"

TeamMemberView::TeamMemberView(QWidget *parent)
    : QWidget(parent), ui(new Ui::TeamMemberView), m_addMemberDialog(new AddMemberDialog()),
      m_model(new TeamMemberModel(this)) {
    ui->setupUi(this);

    ui->addButton->setIcon(QIcon(":/images/AddIcon.png"));
    ui->removeButton->setIcon(QIcon(":/images/RemoveIcon.png"));

    ui->membersListView->setModel(m_model->getModel());

    connectUi();

    ui->removeButton->setEnabled(false);

    m_addMemberDialog->setModal(true);
}

TeamMemberModel *TeamMemberView::getModel() const { return m_model; }

void TeamMemberView::connectUi() {
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(onAddMemberClicked()));
    connect(m_addMemberDialog.get(), SIGNAL(accepted()), this, SLOT(onAddMemberAccepted()));
    connect(this, SIGNAL(teamMemberAddedUi(QString)), m_model, SLOT(onTeamMemberAdded(QString)));
    connect(m_model, SIGNAL(teamMemberAdded(QString)), this, SLOT(onTeamMemberAdded(QString)));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(onRemoveMemberClicked()));
    connect(m_model, SIGNAL(teamMemberRemoved(int)), this, SLOT(onTeamMemberRemoved(int)));
    connect(m_model, SIGNAL(teamMemberAdded(QString)), this, SIGNAL(teamMemberAddedModel(QString)));
}

void TeamMemberView::onAddMemberClicked() { m_addMemberDialog->show(); }

void TeamMemberView::onAddMemberAccepted() {
    const QString memberName = m_addMemberDialog->getMemberName();
    emit teamMemberAddedUi(memberName);
}

void TeamMemberView::onTeamMemberAdded(QString) {
    ui->membersListView->update();

    QStandardItemModel *const itemsModel = m_model->getModel();
    ui->membersListView->setCurrentIndex(itemsModel->index(itemsModel->rowCount() - 1, 0));

    ui->removeButton->setEnabled(true);
}

void TeamMemberView::onRemoveMemberClicked() {
    QModelIndex currentIndex = ui->membersListView->currentIndex();

    if (currentIndex.isValid()) {
        m_model->onTeamMemberRemoved(currentIndex.row());
    }
}

void TeamMemberView::onTeamMemberRemoved(int) {
    ui->membersListView->update();

    QStandardItemModel *const itemsModel = m_model->getModel();

    const QModelIndex nextIndex = itemsModel->index(itemsModel->rowCount() - 1, 0);

    if (nextIndex.isValid()) {
        ui->membersListView->setCurrentIndex(nextIndex);
    } else {
        ui->removeButton->setEnabled(false);
    }
}

TeamMemberView::~TeamMemberView() { delete ui; }
