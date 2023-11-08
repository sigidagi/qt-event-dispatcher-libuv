#ifndef TEAMMEMBERMODEL_H
#define TEAMMEMBERMODEL_H

#include <QObject>
#include <QStandardItemModel>

class TeamMemberModel : public QObject {
    Q_OBJECT
  public:
    explicit TeamMemberModel(QObject *parent = nullptr);
    QStandardItemModel *getModel();

  public slots:
    void onTeamMemberAdded(QString);
    void onTeamMemberRemoved(int);

  signals:
    void teamMemberAdded(QString);
    void teamMemberRemoved(int);

  private:
    QStandardItemModel *m_model;
};

#endif // TEAMMEMBERMODEL_H
