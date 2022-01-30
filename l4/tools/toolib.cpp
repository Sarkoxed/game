// sarkoxed //
#include "toolib.hpp"

unsigned int randint(unsigned int a){
    if(a != 0){
        return random() % a;
    }
    return 0;
}

nlohmann::json getconf(const std::string& filename){
    std::ifstream fin;
    fin.open(filename);
    if(!fin.is_open()){
        throw std::invalid_argument("no such a file");
    }
    nlohmann::json answer;
    fin >> answer;
    return answer;
}

void saveconf(const nlohmann::json& js, const std::string& filename){
    std::ofstream fo;
    fo.open(filename);
    if(!fo.is_open()){
        throw std::invalid_argument("no such a file");
    }
    nlohmann::json answer;
    fo << js;
}
