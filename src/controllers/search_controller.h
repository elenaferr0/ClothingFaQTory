#ifndef SEARCH_CONTROLLER_H
#define SEARCH_CONTROLLER_H

#include "controller.h"

namespace Controllers {
    class SearchController : public Controller {
        Q_OBJECT
        public:
            SearchController(View*);
    };
}


#endif //SEARCH_CONTROLLER_H
