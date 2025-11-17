#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>

class Application : public QObject {
    Q_OBJECT

public:
    Application(int &argc, char **argv);
    void run();

private:
    void initialize();
    void cleanup();
};

#endif // APPLICATION_H