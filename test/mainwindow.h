#pragma once

#include <QFileDialog>
#include <QList>
#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>

#include "teammemberview.h"
#include "teamview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  public slots:
    /**
     * This is example of doxygen comments.
     * @brief executed once File is selected (slot)
     */
    void onSaveFileSelected(QString file);

    void onLoadFileSelected(QString file);
    void onSaveFileTriggered();

  private:
    void connectUi();

    Ui::MainWindow *ui;
    TeamMemberView *m_teamMemberView;
    TeamView *m_teamView;
    QFileDialog *m_loadDialog;
};
