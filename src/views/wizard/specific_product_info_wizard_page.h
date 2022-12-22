

#ifndef SPECIFIC_PRODUCT_INFO_WIZARD_PAGE_H
#define SPECIFIC_PRODUCT_INFO_WIZARD_PAGE_H


#include <QWizardPage>
#include "specific_product_info_visitor.h"

namespace Wizard {
    class SpecificProductInfoWizardPage : public QWizardPage {
        Q_OBJECT
        private:
            SpecificProductInfoVisitor visitor;
        public:
            SpecificProductInfoWizardPage();
    };

}

#endif //SPECIFIC_PRODUCT_INFO_WIZARD_PAGE_H
