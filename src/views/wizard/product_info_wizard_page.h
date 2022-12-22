#ifndef PRODUCT_INFO_WIZARD_PAGE_H
#define PRODUCT_INFO_WIZARD_PAGE_H

#include "../../models/product.h"
#include "../../controllers/wizard_controller.h"
#include <QWizardPage>
#include <QSet>
#include "select_color_button.h"

QT_BEGIN_NAMESPACE
namespace Views::Wizard { class InsertProductInfoWizardPage; }
QT_END_NAMESPACE

using Models::Product;
using Controllers::WizardController;

class ProductInfoWizardPage : public QWizardPage {
    Q_OBJECT
    private:
        static const int MAX_SPIN_BOX_VALUE = 99999999;
        static const int SPIN_BOX_STEP = 100;

    public:
        ProductInfoWizardPage(const QList<QString>& = QList<QString>(),
                              const QList<QString>& = QList<QString>(),
                              QWidget* parent = nullptr);

        bool validatePage() override;

};


#endif //PRODUCT_INFO_WIZARD_PAGE_H
