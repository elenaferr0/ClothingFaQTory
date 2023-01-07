#include "product_wizard_view.h"
#include "choose_product_type_wizard_page.h"
#include "generic_product_info_wizard_page.h"
#include "specific_product_info_wizard_page.h"
#include <memory>
#include <QMessageBox>
#include <QDialogButtonBox>

using std::dynamic_pointer_cast;
using Views::Wizard::ProductWizardView;
using Views::Wizard::ChooseProductTypeWizardPage;

ProductWizardView::ProductWizardView(Mode mode,
                                     MainView* mainView,
                                     QWidget* parent,
                                     const QList<QString>& materials,
                                     const QList<QString>& sizes,
                                     shared_ptr<Product> product,
                                     Product::ProductType productType)
        : QWizard(parent), mode(mode), product(product) {
    controller = new WizardController(this);
    connect(controller, SIGNAL(databaseError(Error * )), mainView, SLOT(handleDatabaseError(Error * )));

    if (mode == Mode::Create) {
        addPage(new ChooseProductTypeWizardPage(this));
    }
    addPage(new GenericProductInfoWizardPage(materials, sizes, productType, this));
    addPage(new SpecificProductInfoWizardPage(this));
    setWindowTitle(mode == Create ? "Insert a new product" : "Edit product");

    setDefaultProperty("QTextEdit", "plainText", "textChanged");

    connect(this, SIGNAL(completed(shared_ptr<Product>, Product::ProductType)),
            controller, SLOT(handleProductEditAndCreate(shared_ptr<Product>, Product::ProductType)));

}

void ProductWizardView::setProduct(shared_ptr<Product> product) {
    this->product = product;
}

WizardController* ProductWizardView::getController() const {
    return dynamic_cast<WizardController*>(controller);
}

shared_ptr<Product> ProductWizardView::getProduct() const {
    return product;
}

void ProductWizardView::done(int result) {
    if (result == QDialog::Accepted) {
        Product::ProductType productType = static_cast<Product::ProductType>(field("productType").toInt());
        switch (productType) {
            case Product::Jeans: {
                shared_ptr<Jeans> jeans = dynamic_pointer_cast<Jeans>(product);
                jeans->setSustainableMaterials(getSustainableMaterials());
                jeans->setGender(getGender());
                jeans->setShorts(field("shorts").toBool());
                break;
            }
            case Product::Overalls: {
                shared_ptr<Overalls> overalls = dynamic_pointer_cast<Overalls>(product);
                overalls->setSustainableMaterials(getSustainableMaterials());
                overalls->setGender(getGender());
                overalls->setShorts(field("shorts").toBool());
                overalls->setHasButtons(field("hasButtons").toBool());
                break;
            }
            case Product::Hat: {
                shared_ptr<Hat> hat = dynamic_pointer_cast<Hat>(product);
                hat->setCategory(getCategory());
                hat->setBaseballCap(field("baseballCap").toBool());
                break;
            }
            case Product::Bracelet: {
                shared_ptr<Bracelet> bracelet = dynamic_pointer_cast<Bracelet>(product);
                bracelet->setCategory(getCategory());
                bracelet->setPearlDiameter(field("pearlDiameter").toDouble());
                bracelet->setPearlNumber(field("pearlNumber").toInt());
                break;
            }
            case Product::Vest: {
                shared_ptr<Vest> vest = dynamic_pointer_cast<Vest>(product);
                vest->setSustainableMaterials(getSustainableMaterials());
                vest->setGender(getGender());
                vest->setHasButtons(field("hasButtons").toBool());
                break;
            }
            case Product::BackPack: {
                shared_ptr<BackPack> backpack = dynamic_pointer_cast<BackPack>(product);
                backpack->setCategory(getCategory());
                backpack->setCapacity(field("capacity").toDouble());
                break;
            }
        }
        emit completed(product,
                       static_cast<Product::ProductType>(field("productType").toInt()));
    }

    product = nullptr;
    QWizard::done(result);
}

string ProductWizardView::getCategory() {
    int categoryIndex = field("category").toInt();
    return Accessory::getCategoryAsString(static_cast<Accessory::Category>(categoryIndex));
}

bool ProductWizardView::getSustainableMaterials() {
    return field("sustainableMaterials").toBool();
}

ClothingItem::Gender ProductWizardView::getGender() {
    int genderIndex = field("gender").toInt();
    return static_cast<ClothingItem::Gender>(genderIndex);
}

void ProductWizardView::cleanupPage(int id) {
    for (int i = 0; i < id; ++i) {
        QWizardPage* page = this->page(i);
        page->cleanupPage();
    }
    QWizard::cleanupPage(id);
}

ProductWizardView::Mode Views::Wizard::ProductWizardView::getMode() const {
    return mode;
}

void Views::Wizard::ProductWizardView::reject() {
    QMessageBox* confirmMessageBox = new QMessageBox;
    confirmMessageBox->setWindowTitle("Cancel confirmation");
    confirmMessageBox->setText("### Do you really want to cancel this operation?");
    confirmMessageBox->setInformativeText("Unsaved changes will not be recoverable");
    confirmMessageBox->setTextFormat(Qt::MarkdownText);

    QPushButton* confirmButton = new QPushButton(tr("&Confirm"));
    QPushButton* keepEditingButton = new QPushButton(tr("&Keep editing"));
    confirmMessageBox->addButton(confirmButton, QMessageBox::ButtonRole::AcceptRole);
    confirmMessageBox->addButton(keepEditingButton, QMessageBox::ButtonRole::RejectRole);

    confirmMessageBox->setAttribute(Qt::WA_DeleteOnClose);
    confirmMessageBox->resize(300, 200);
    int result = confirmMessageBox->exec();

    if (result == QMessageBox::Rejected) {
        QWizard::reject();
    }
}
