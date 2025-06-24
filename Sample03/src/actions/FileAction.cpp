#include "FileAction.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "core/ViewportManager.h"
#include "core/EntityFactory.h"
#include "core/Viewport.h"

FileAction::FileAction(FileActionType type, QObject* parent)
    : Action(parent), m_type(type) {}

QString FileAction::id() const {
    switch (m_type) {
    case Open: return "OpenFile";
    case SaveAs: return "SaveAsFile";
    default: return QString();
    }
}

QString FileAction::name() const {
    switch (m_type) {
    case Open: return tr("打开");
    case SaveAs: return tr("另存为");
    default: return QString();
    }
}

QString FileAction::description() const {
    switch (m_type) {
    case Open: return tr("打开文件");
    case SaveAs: return tr("另存为文件");
    default: return QString();
    }
}

QString FileAction::icon() const {
    switch (m_type) {
    case Open: return ":/icons/open.png";
    case SaveAs: return ":/icons/save_as.png";
    default: return QString();
    }
}

void FileAction::execute() {
    Viewport* viewport = ViewportManager::instance()->activeViewport();
    if (!viewport) {
        QMessageBox::warning(nullptr, tr("错误"), tr("没有活动的视口！"));
        return;
    }

    QString filePath;
    switch (m_type) {
    case Open: {
        filePath = QFileDialog::getOpenFileName(nullptr, tr("打开文件"), "", tr("OCCT 文件 (*.json)"));
        if (filePath.isEmpty()) return;

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(nullptr, tr("错误"), tr("无法打开文件！"));
            return;
        }

        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();

        if (doc.isNull() || !doc.isArray()) {
            QMessageBox::warning(nullptr, tr("错误"), tr("文件格式无效！"));
            return;
        }

        QJsonArray entities = doc.array();
        for (const QJsonValue& value : entities) {
            if (value.isObject()) {
                SimpleEntity* entity = EntityFactory::createEntity(value.toObject());
                if (entity) {
                    viewport->displaySimpleEntity(entity);
                }
            }
        }
        break;
    }
    case SaveAs: {
        if (m_type == SaveAs || viewport->getAllSimpleEntities().isEmpty()) {
            filePath = QFileDialog::getSaveFileName(nullptr, tr("保存文件"), "", tr("OCCT 文件 (*.json)"));
            if (filePath.isEmpty()) return;
        }

        QJsonArray entities;
        for (SimpleEntity* entity : viewport->getAllSimpleEntities()) {
            QJsonObject json;
            entity->serialize(json);
            entities.append(json);
        }

        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(nullptr, tr("错误"), tr("无法保存文件！"));
            return;
        }

        file.write(QJsonDocument(entities).toJson());
        file.close();
        break;
    }
    }
}