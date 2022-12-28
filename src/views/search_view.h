

#ifndef SEARCH_VIEW_H
#define SEARCH_VIEW_H

#include "widget_view_parent.h"
#include "main_view.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QDoubleValidator>
#include "../core/filters/filter.h"

using Core::Filter;
namespace Views {
    class MainView;

    class SearchDialog : public QDialog {
        Q_OBJECT
        private:
            QGroupBox* productTypeGroupBox;
            QGroupBox* codeGroupBox;
            QLineEdit* minPriceLineEdit;
            QLineEdit* maxPriceLineEdit;
            QDoubleValidator* maxValidator;
            QGroupBox* sortGroupBox;
            Filter filters;
        public:
            SearchDialog(QWidget* parent = nullptr);

        signals:

            void searchStarted(Filter);

        private slots:

            void handleMinPriceTextChanged(const QString& price);
    };
}

#endif //SEARCH_VIEW_H
