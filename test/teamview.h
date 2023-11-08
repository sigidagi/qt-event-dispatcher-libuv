#ifndef TEAMVIEW_H
#define TEAMVIEW_H

#include <QObject>
#include <QPushButton>
#include <QSignalMapper>
#include <QWidget>

namespace Ui {
class TeamView;
}

class TeamView : public QWidget {
    Q_OBJECT

  public:
    explicit TeamView(QWidget *parent = nullptr);
    ~TeamView();

  public slots:
    void onClearTeamMembers();
    void onTeamMemberAdded(const QString &);
    void onTeamMemberRemoved(const int &);
    void onClickedButton();

  private:
    Ui::TeamView *ui;
    int m_buttonSize = 0;
    int m_gridSize = 0;
    int m_numberTeamMembers = 0;
};

#endif // TEAMVIEW_H
