#include "teamview.h"
#include "ui_teamview.h"
#include <QLayoutItem>
#include <vector>

TeamView::TeamView(QWidget *parent) : QWidget(parent), ui(new Ui::TeamView) { ui->setupUi(this); }

TeamView::~TeamView() { delete ui; }

void TeamView::onClearTeamMembers() {
    for (int buttonNumber = 0; buttonNumber < m_numberTeamMembers; buttonNumber++) {
        QLayoutItem *p_item = ui->gridLayout->itemAt(0);
        if (p_item) {
            QWidget *p_button = p_item->widget();
            if (p_button) {
                ui->gridLayout->removeWidget(p_button);
                p_button->close();
            }
        }
    }
    m_buttonSize = 0;
    m_gridSize = 0;
    m_numberTeamMembers = 0;
}

void TeamView::onTeamMemberAdded(const QString &teamMemberName) {
    m_numberTeamMembers++;
    if (m_numberTeamMembers > m_gridSize * m_gridSize) {
        m_gridSize++;
        std::vector<QWidget *> buttons;
        for (int buttonNumber = m_gridSize; buttonNumber < m_numberTeamMembers; buttonNumber++) {
            QLayoutItem *p_item = ui->gridLayout->itemAt(m_gridSize - 1);
            if (p_item) {
                QWidget *p_button = p_item->widget();
                if (p_button) {
                    ui->gridLayout->removeWidget(p_button);
                    buttons.push_back(p_button);
                }
            }
        }
        for (int buttonNumber = 0; buttonNumber < m_numberTeamMembers - m_gridSize; buttonNumber++) {
            int rowNumber = (buttonNumber + m_gridSize - 1) / m_gridSize;
            int columnNumber = (buttonNumber + m_gridSize - 1) % m_gridSize;
            ui->gridLayout->addWidget(buttons[buttonNumber], rowNumber, columnNumber);
        }
    }
    int rowNumber = (m_numberTeamMembers - 1) / m_gridSize;
    int columnNumber = (m_numberTeamMembers - 1) % m_gridSize;
    QPushButton *p_newButton = (new QPushButton(teamMemberName));
    if (m_buttonSize < p_newButton->sizeHint().width()) {
        m_buttonSize = p_newButton->sizeHint().width();
        for (int buttonNumber = 0; buttonNumber < m_numberTeamMembers - 1; buttonNumber++) {
            QLayoutItem *p_oldItem = ui->gridLayout->itemAt(buttonNumber);
            if (p_oldItem) {
                QWidget *p_oldButton = p_oldItem->widget();
                if (p_oldButton) {
                    p_oldButton->setMinimumSize(m_buttonSize, m_buttonSize);
                    p_oldButton->update();
                }
            }
        }
    }
    p_newButton->setAttribute(Qt::WA_DeleteOnClose);
    p_newButton->setFlat(true);
    p_newButton->setAutoFillBackground(true);
    p_newButton->setStyleSheet("QPushButton {background-color: rgb(255,255,255);border-radius: 10px}");
    p_newButton->setMinimumSize(m_buttonSize, m_buttonSize);
    p_newButton->update();
    connect(p_newButton, SIGNAL(clicked()), this, SLOT(onClickedButton()));
    ui->gridLayout->addWidget(p_newButton, rowNumber, columnNumber);
}

void TeamView::onTeamMemberRemoved(const int &teamMemberNumber) {
    m_numberTeamMembers--;
    std::vector<QWidget *> buttons;
    bool teamMemberResize = false;
    QLayoutItem *p_item = ui->gridLayout->itemAt(teamMemberNumber);
    if (p_item) {
        QWidget *p_button = p_item->widget();
        if (p_button) {
            if (p_button->sizeHint().width() >= m_buttonSize)
                teamMemberResize = true;
            ui->gridLayout->removeWidget(p_button);
            p_button->close();
        }
    }
    int teamMemberPartition = teamMemberNumber;
    if (m_numberTeamMembers <= (m_gridSize - 1) * (m_gridSize - 1)) {
        m_gridSize--;
        teamMemberPartition = m_gridSize;
    }
    for (int buttonNumber = teamMemberPartition; buttonNumber < m_numberTeamMembers; buttonNumber++) {
        QLayoutItem *p_item = ui->gridLayout->itemAt(teamMemberPartition);
        if (p_item) {
            QWidget *p_button = p_item->widget();
            if (p_button) {
                ui->gridLayout->removeWidget(p_button);
                buttons.push_back(p_button);
            }
        }
    }
    for (int buttonNumber = 0; buttonNumber < m_numberTeamMembers - teamMemberPartition; buttonNumber++) {
        int rowNumber = (teamMemberPartition + buttonNumber) / m_gridSize;
        int columnNumber = (teamMemberPartition + buttonNumber) % m_gridSize;
        ui->gridLayout->addWidget(buttons[buttonNumber], rowNumber, columnNumber);
    }
    if (teamMemberResize) {
        int buttonSize = 0;
        for (int buttonNumber = 0; buttonNumber < m_numberTeamMembers; buttonNumber++) {
            QLayoutItem *p_item = ui->gridLayout->itemAt(buttonNumber);
            if (p_item) {
                QWidget *p_button = p_item->widget();
                if (p_button) {
                    if (buttonSize < p_button->sizeHint().width())
                        buttonSize = p_button->sizeHint().width();
                }
            }
        }
        if (m_buttonSize > buttonSize) {
            m_buttonSize = buttonSize;
            for (int buttonNumber = 0; buttonNumber < m_numberTeamMembers; buttonNumber++) {
                QLayoutItem *p_item = ui->gridLayout->itemAt(buttonNumber);
                if (p_item) {
                    QWidget *p_button = p_item->widget();
                    if (p_button) {
                        p_button->setMinimumSize(m_buttonSize, m_buttonSize);
                        p_button->update();
                    }
                }
            }
        }
    }
}

void TeamView::onClickedButton() {
    QPushButton *p_button = qobject_cast<QPushButton *>(sender());
    if (p_button) {
        if (p_button->property("clicked").toBool()) {
            p_button->setProperty("clicked", false);
            p_button->setDown(false);
            p_button->setStyleSheet("QPushButton{background-color: rgb(255,255,255); border: none; "
                                    "border-radius: 10px}");
        } else {
            p_button->setProperty("clicked", true);
            p_button->setDown(true);
            p_button->setStyleSheet("QPushButton{background-color: rgb(153,204,255); border: none; "
                                    "border-radius: 10px}");
        }
    }
}
