

#ifndef FILTER_DIALOG_H
#define FILTER_DIALOG_H

#include "widget_view_parent.h"
#include "main_view.h"
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QMap>
#include <QLineEdit>
#include <QCheckBox>
#include <QDoubleValidator>
#include "../core/filters.h"

using Core::Filters;
namespace Views {
    class MainView;

    class FilterDialog : public QDialog {
        Q_OBJECT
        private:
            static QMap<QString, QString> sortableFields;
            QDoubleValidator* maxValidator;

            QGroupBox* productTypeGroupBox;
            QGroupBox* codeGroupBox;
            QGroupBox* priceRangeGroupBox;
            QLineEdit* minPriceLineEdit;
            QLineEdit* maxPriceLineEdit;
            QGroupBox* sortGroupBox;
            QComboBox* sortFieldComboBox;
            QComboBox* orderComboBox;

            QPushButton* filterButton;
            QLineEdit* codeLineEdit;
            LinkedList<QCheckBox*> productTypeCheckboxes;

            QLabel* productTypeError;
            QLabel* codeError;
            QLabel* priceError;

        public:
            static const int MAX_PRICE;

            FilterDialog(QWidget* parent = nullptr);

        signals:

            void startFiltering(Filters filters);

        private slots:

            void handleMinPriceTextChanged(const QString& price);

            void handleLineEditChanged(const QString& price);

            void validate();

            void completed();
    };
}

#endif //FILTER_DIALOG_H
