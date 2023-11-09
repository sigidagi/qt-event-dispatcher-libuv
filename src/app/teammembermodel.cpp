#include "teammembermodel.h"

TeamMemberModel::TeamMemberModel(QObject *parent) : QObject{parent} { m_model = new QStandardItemModel(this); }

void TeamMemberModel::onTeamMemberAdded(QString memberName) {

    QStandardItem *memberItem = new QStandardItem(memberName);
    m_model->appendRow(memberItem);
    emit teamMemberAdded(memberName);
}

// allows access to private member variable
QStandardItemModel *TeamMemberModel::getModel() { return m_model; }

void TeamMemberModel::onTeamMemberRemoved(int index) {

    m_model->removeRow(index);
    emit teamMemberRemoved(index);
}
