#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QFile>
#include <QObject>
#include <QStandardItemModel>
#include <QtXml>

class xmlHandler : public QObject {
    Q_OBJECT
  public:
    explicit xmlHandler(QObject *parent = nullptr);
    void setTeamMembers(QFile *xml);
    void saveMembersToFile(QStandardItemModel *model, QString filename);

  signals:
    void teamMemberAdded(QString);
    void fileStatus(QString);

  private:
};

#endif // XMLHANDLER_H
