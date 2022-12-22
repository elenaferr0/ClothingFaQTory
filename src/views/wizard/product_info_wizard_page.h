#ifndef PRODUCT_INFO_WIZARD_PAGE_H
#define PRODUCT_INFO_WIZARD_PAGE_H


#include <QWizardPage>
#include <QSet>
#include "select_color_button.h"

QT_BEGIN_NAMESPACE
namespace Views::Wizard { class InsertProductInfoWizardPage; }
QT_END_NAMESPACE

class ProductInfoWizardPage : public QWizardPage {
    Q_OBJECT
    private:
        SelectColorButton* button;
    public:
        ProductInfoWizardPage(QWidget* parent = nullptr, const QSet<QString>& = QSet<QString>(),
                              const QSet<QString>& = QSet<QString>());
};


#endif //PRODUCT_INFO_WIZARD_PAGE_H
