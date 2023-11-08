#ifndef TEAMMEMBERVIEW_H
#define TEAMMEMBERVIEW_H

#include <QAbstractItemModel>
#include <QSharedPointer>
#include <QWidget>

#include "addmemberdialog.h"
#include "teammembermodel.h"

namespace Ui {
class TeamMemberView;
}

class TeamMemberView : public QWidget {
    Q_OBJECT

  public:
    explicit TeamMemberView(QWidget *parent = nullptr);

    TeamMemberModel *getModel() const;

    ~TeamMemberView();

  signals:
    void teamMemberAddedUi(QString);
    void teamMemberAddedModel(QString);

  public slots:
    void onAddMemberClicked();
    void onAddMemberAccepted();
    void onTeamMemberAdded(QString);
    void onRemoveMemberClicked();
    void onTeamMemberRemoved(int);

  private:
    void connectUi();

    Ui::TeamMemberView *ui;
    QSharedPointer<AddMemberDialog> m_addMemberDialog;

    TeamMemberModel *m_model;
};

#endif // TEAMMEMBERVIEW_H
