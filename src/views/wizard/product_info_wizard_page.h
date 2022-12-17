#ifndef PRODUCT_INFO_WIZARD_PAGE_H
#define PRODUCT_INFO_WIZARD_PAGE_H


#include <QWizardPage>
QT_BEGIN_NAMESPACE
namespace Views::Wizard { class InsertProductInfoWizardPage; }
QT_END_NAMESPACE

class ProductInfoWizardPage : public QWizardPage{
    Q_OBJECT
public:
    ProductInfoWizardPage(QWidget* parent = nullptr);
};


#endif //PRODUCT_INFO_WIZARD_PAGE_H
