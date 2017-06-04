#pragma once

#include <stdlib.h>
#include "PixelArray.h"
#include "DomeMappings.h"

class CRoutine;

class CDome : public CPixelArray
{
    public:
        CDome();
        ~CDome();

    public:
        virtual void Continue() override;

    private:
        CPixelArray* m_shapes[DomeMappings::c_num_shapes] = {};
};
