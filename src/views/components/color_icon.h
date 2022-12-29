

#ifndef COLOR_ICON_H
#define COLOR_ICON_H

#include <QIcon>
#include <string>

QT_BEGIN_NAMESPACE
namespace Components { class ColorIcon; }
QT_END_NAMESPACE

using std::string;

class ColorIcon : public QIcon {
    private:
        static const int COLOR_ICON_SIZE = 20;
        QPixmap* pixmap;

    public:
        ColorIcon(const string& hex);

        QPixmap* getPixmap() const;
};


#endif //COLOR_ICON_H
