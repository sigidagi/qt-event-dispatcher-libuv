#ifndef ADDMEMBERDIALOG_H
#define ADDMEMBERDIALOG_H

#include <QDialog>

namespace Ui {
class AddMemberDialog;
}

class AddMemberDialog : public QDialog {
    Q_OBJECT

  public:
    explicit AddMemberDialog(QWidget *parent = nullptr);

    QString getMemberName() const;

    ~AddMemberDialog();

  public:
    void show();

  public slots:
    void onLineEditTextChanged(QString);

  private:
    void connectUi();

    Ui::AddMemberDialog *ui;
};

#endif // ADDMEMBERDIALOG_H
