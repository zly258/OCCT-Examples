#ifndef WIDGET_UTILS_H
#define WIDGET_UTILS_H

#include <QWidget>

namespace Utils {

template<typename T>
T* findParentWidget(QWidget* widget)
{
    while (widget) {
        if (T* parent = qobject_cast<T*>(widget)) {
            return parent;
        }
        widget = widget->parentWidget();
    }
    return nullptr;
}

} // namespace Utils

#endif // WIDGET_UTILS_H 