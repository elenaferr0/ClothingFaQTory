#include <QToolButton>
#include "materials_view.h"

using Views::MaterialsView;
using Controllers::MainController;

int MaterialsView::COLUMN_COUNT = 4;

MaterialsView::MaterialsView(MainView* mainView, QWidget* parent) : WidgetViewParent(parent),
                                                                    materials(MaterialsList()) {
    setController(new MainController(this));
    connect(controller, SIGNAL(databaseError(Error * )), mainView, SLOT(handleDatabaseError(Error * )));
}

void MaterialsView::init() {
    this->materials = dynamic_cast<MainController*>(controller)->findAllMaterials();
    gridLayout = new QGridLayout(this);
    gridLayout->setAlignment(Qt::AlignCenter);
    gridLayout->setSpacing(60);

    initGrid();
}

void Views::MaterialsView::initGrid() {

    int row = 0, col = 0;

    for (auto material: materials) {
        QToolButton* button = new QToolButton();
        string materialName = material->getNameAsString();

        QString capitalizedName = QString::fromStdString(materialName).at(0).toUpper() +
                                  QString::fromStdString(materialName.substr(1, materialName.size() - 1)).toLower();

        QString text = capitalizedName + "\n"
                       + QString::number(material->getCostPerUnit(), 'f', 2) + "$/" +
                       QString::fromStdString(material->getUnitOfMeasureAsString());

        button->setText(text);
        button->setIcon(QIcon(":/assets/icons/" + QString::fromStdString(materialName).toLower() + ".png"));
        button->setIconSize(QSize(50, 50));
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button->setObjectName("materialButton"); // for stylesheet

        gridLayout->addWidget(button, row, col);

        col++;
        if (col == COLUMN_COUNT) {
            row++;
            col = 0;
        }
    }

}