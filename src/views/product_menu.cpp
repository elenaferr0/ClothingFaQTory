

#include <QVBoxLayout>
#include "product_menu.h"
#include "tabs/product_tab_page.h"
#include "tabs/materials_cost_tab_page.h"

ProductMenu::ProductMenu(QWidget* parent) : QWidget(parent) {
    QHBoxLayout* hbox = new QHBoxLayout(this);

    tabWidget = new QTabWidget;

    tabWidget->addTab(new ProductTabPage(tabWidget), "Clothing Items");
    QIcon clothingIcon(":/assets/icons/clothing_items.png");
    tabWidget->setTabIcon(0, clothingIcon);

    tabWidget->addTab(new ProductTabPage(tabWidget), "Accessories");
    QIcon accessoriesIcon(":/assets/icons/accessories.png");
    tabWidget->setTabIcon(1, accessoriesIcon);

    tabWidget->addTab(new MaterialsCostTabPage(tabWidget), "Materials Cost");
    QIcon materialsIcon(":/assets/icons/materials_cost.png");
    tabWidget->setTabIcon(2, materialsIcon);

    tabWidget->setIconSize(QSize(35, 35));
    hbox->addWidget(tabWidget);
}
