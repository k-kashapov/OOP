#include <utility>
#include <list>
#include <cstdlib>
#include <ctime>

using coord = std::pair<int, int>;

class Model {
public:
    std::list<coord> rabbits;
    std::list<coord> snake;
    
    Model();
    ~Model() {};
    
    void Update();
};
