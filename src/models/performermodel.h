#ifndef PERFORMERMODELE_H
#define PERFORMERMODELE_H

#include "../base/basemodel.h"
#include "../../MusicBaseData/Persons/headers/Performer.h"

class PerformerModel: public BaseModel
{
public:
    PerformerModel(Poco::SharedPtr <Performer> performer);

    Poco::SharedPtr <Performer> getPerformer();

private:
    Poco::SharedPtr <Performer> m_performerBase;
};

#endif // PERFORMERMODELE_H
