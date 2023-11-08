#include "xmlhandler.h"

xmlHandler::xmlHandler(QObject *parent) : QObject{parent} {}

void xmlHandler::saveMembersToFile(QStandardItemModel *model, QString filename) {
    if (model->rowCount() == 0) {
        emit fileStatus("No data to save");
        return;
    }

    QDomDocument teamDoc;
    QDomElement root = teamDoc.createElement("team");
    teamDoc.appendChild(root);

    for (int i = 0; i < model->rowCount(); i++) {
        QDomElement tag = teamDoc.createElement("member");
        root.appendChild(tag);
        QStandardItem *cur = model->item(i);
        QString line = cur->text();
        QDomText t = teamDoc.createTextNode(line);
        tag.appendChild(t);
    }

    QString xml = teamDoc.toString();

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << xml;
        file.close();
    }

    if (QFile::exists(filename)) {
        emit fileStatus(QString("File saved to %1").arg(filename));
    } else {
        emit fileStatus(QString("Failed to save file to %1").arg(filename));
    }
}

void xmlHandler::setTeamMembers(QFile *xml) {
    QDomDocument domDocument;
    QString *pErrorMsg = new QString;
    int *pErrorLine = new int;
    int *pErrorColumn = new int;
    if (domDocument.setContent(xml, pErrorMsg, pErrorLine, pErrorColumn)) {
        QDomElement domDoc = domDocument.documentElement();
        QDomNode n = domDoc.firstChild();

        while (!n.isNull()) {
            QDomElement e = n.toElement();
            QString memberName = e.text();
            emit teamMemberAdded(memberName);
            n = n.nextSibling();
        }
    } else {
        QString errorLine = QString::number(*pErrorLine);
        QString errorColumn = QString::number(*pErrorColumn);
        QString errorMsg = *pErrorMsg;
        emit fileStatus(QString("Unable to load file %1:  %2 at Line: %3,  Column: %4")
                            .arg(xml->fileName())
                            .arg(errorMsg)
                            .arg(errorLine)
                            .arg(errorColumn));
    }

    xml->close();
    delete pErrorColumn;
    delete pErrorLine;
    delete pErrorMsg;
}
