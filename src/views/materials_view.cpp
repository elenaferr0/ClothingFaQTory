#include <QToolButton>
#include "materials_view.h"
#include "components/material_icon_button.h"
#include "components/edit_material_cost_box.h"

using Views::MaterialsView;
using Controllers::MainController;

int MaterialsView::COLUMN_COUNT = 4;

MaterialsView::MaterialsView(MainView* mainView, QWidget* parent) : WidgetViewParent(parent) {
    setController(new MainController(this));
    connect(controller, SIGNAL(databaseError(Error * )), mainView, SLOT(handleDatabaseError(Error * )));
}

void MaterialsView::init() {
    auto materials = dynamic_cast<MainController*>(controller)->findAllMaterials();
    gridLayout = new QGridLayout(this);
    gridLayout->setAlignment(Qt::AlignCenter);
    gridLayout->setSpacing(60);
    initGrid(materials);
}

void Views::MaterialsView::initGrid(MaterialsView::MaterialsList materials) {

    int row = 0, col = 0;

    for (auto material: materials) {
        MaterialIconButton* button = new MaterialIconButton(material, this);

        QString text = getButtonText(material);

        button->setText(text);
        button->setIcon(
                QIcon(":/assets/icons/" + QString::fromStdString(material->getNameAsString()).toLower() + ".png"));
        button->setIconSize(QSize(50, 50));
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button->setObjectName("materialButton"); // for stylesheet
        connect(button, SIGNAL(clicked(Material * )), this,
                SLOT(handleMaterialButtonClicked(Material * )));

        gridLayout->addWidget(button, row, col);

        col++;
        if (col == COLUMN_COUNT) {
            row++;
            col = 0;
        }
    }

}

QString Views::MaterialsView::getButtonText(const Material* material) const {
    string materialName = material->getNameAsString();

    QString capitalizedName = QString::fromStdString(materialName).at(0).toUpper() +
                              QString::fromStdString(materialName.substr(1, materialName.size() - 1)).toLower();

    QString text = capitalizedName + "\n"
                   + QString::number(material->getCostPerUnit(), 'f', 2) + "$/"
                   + QString::fromStdString(material->getUnitOfMeasureAsString());
    return text;
}

void Views::MaterialsView::handleMaterialButtonClicked(Material* material) {
    EditMaterialCostMessageBox* materialCostMessageBox = new EditMaterialCostMessageBox(material, this);
    materialCostMessageBox->setAttribute(Qt::WA_DeleteOnClose);
    int result = materialCostMessageBox->exec();

    if (result == QDialog::Accepted) {
        dynamic_cast<MainController*>(controller)->saveCostPerUnit(material);
        // Remove all widgets from the layout
        while (gridLayout->count() > 0) {
            QLayoutItem* item = gridLayout->takeAt(0);
            if (item->widget()) {
                gridLayout->removeWidget(item->widget());
                delete item->widget();
            }
            delete item;
        }
        initGrid(dynamic_cast<MainController*>(controller)->findAllMaterials());
        emit materialCostChanged();
    }

}
