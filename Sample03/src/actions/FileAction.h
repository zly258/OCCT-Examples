#ifndef FILE_ACTION_H
#define FILE_ACTION_H

#include "Action.h"

class FileAction : public Action
{
    Q_OBJECT
public:
    enum FileActionType {
        Open,
        SaveAs
    };

    explicit FileAction(FileActionType type, QObject* parent = nullptr);

    QString id() const override;
    QString name() const override;
    QString description() const override;
    QString icon() const override;

    void execute() override;

private:
    FileActionType m_type;
};

#endif // FILE_ACTION_H