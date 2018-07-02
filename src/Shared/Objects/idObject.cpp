#include "idObject.hpp"

using namespace OpenGMP::Objects;
using namespace OpenGMP::Components;

Id IdObject::GetId() const
{
    return id;
}

void IdObject::SetId(const Id &value)
{
    id = value;
}
