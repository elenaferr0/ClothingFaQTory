#ifndef CREATE_PRODUCT_WIZARD_H
#define CREATE_PRODUCT_WIZARD_H


#include <QWizard>

QT_BEGIN_NAMESPACE
namespace Views::Wizard { class CreateProductWizard; }
QT_END_NAMESPACE


class CreateProductWizard : public QWizard{
    Q_OBJECT
public:
    CreateProductWizard(QWidget* parent = nullptr);
    void accept() override; // called when the user clicks finish
};


#endif //CREATE_PRODUCT_WIZARD_H
