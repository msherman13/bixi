#include "Bixi.h"

class CBixiQuickCG : public CBixi
{
    public:
        static CBixiQuickCG& Instance();
        ~CBixiQuickCG();

    private:
        CBixiQuickCG();

    protected:
        virtual void Show() final;
};
