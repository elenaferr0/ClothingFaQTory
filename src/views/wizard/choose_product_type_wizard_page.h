#ifndef CHOOSE_PRODUCT_TYPE_WIZARD_PAGE_H
#define CHOOSE_PRODUCT_TYPE_WIZARD_PAGE_H


#include <QWizardPage>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Views::Wizard { class ChooseProductTypeWizardPage; }
QT_END_NAMESPACE

class ChooseProductTypeWizardPage : public QWizardPage {
    Q_OBJECT
    private:
        QComboBox* comboBox;
    public:
        ChooseProductTypeWizardPage(QWidget* parent = nullptr);
};


#endif //CHOOSE_PRODUCT_TYPE_WIZARD_PAGE_H
