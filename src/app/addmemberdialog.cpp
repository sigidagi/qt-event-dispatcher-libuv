#include "addmemberdialog.h"
#include "ui_addmemberdialog.h"
#include <QAbstractButton>

AddMemberDialog::AddMemberDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddMemberDialog) {
    ui->setupUi(this);

    connectUi();
}

QString AddMemberDialog::getMemberName() const { return ui->teamMemberNameLineEdit->text(); }

void AddMemberDialog::show() {
    ui->teamMemberNameLineEdit->clear();

    emit ui->teamMemberNameLineEdit->textChanged(ui->teamMemberNameLineEdit->text());

    QWidget::show();
}

void AddMemberDialog::onLineEditTextChanged(QString text) {
    ui->teamMemberNameButtonBox->buttons().at(0)->setEnabled(!text.isEmpty());
}

void AddMemberDialog::connectUi() {
    connect(ui->teamMemberNameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(onLineEditTextChanged(QString)));
}

AddMemberDialog::~AddMemberDialog() { delete ui; }
