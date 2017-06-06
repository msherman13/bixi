#include "Bixi.h"

class CPixelArray;

class CBixiNone : public CBixi
{
    public:
        static CBixiNone& Instance();
        ~CBixiNone();
        CBixiNone();

    protected:
        virtual void Show(CPixelArray* pixels) override;
};
