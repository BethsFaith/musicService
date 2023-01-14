#include "performermodel.h"

PerformerModel::PerformerModel(Poco::SharedPtr <Performer> performer) : m_performerBase{performer} {}

Poco::SharedPtr <Performer> PerformerModel::getPerformer() {
    return m_performerBase;
}
