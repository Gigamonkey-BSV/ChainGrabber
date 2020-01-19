//
// Created by nekosune on 19/01/2020.
//

#ifndef CHAIN_GRABBER_DATABASECOMPONENT_H
#define CHAIN_GRABBER_DATABASECOMPONENT_H
#include <fruit/fruit.h>
#include "chainGrabber/Database.h"
namespace chain_grabber {
    fruit::Component<Database> GetDatabaseComponent();
}
#endif //CHAIN_GRABBER_DATABASECOMPONENT_H
