#include <Includes.h>
#include <singeton.hpp>


using namespace std;
class Hooks : public Singleton<Hooks>
{
private:
    void Thread(UINT64 scrMeta);
public:

    void Initialize(UINT64 scrMeta);
};

inline auto g_tls_hook = new Hooks;