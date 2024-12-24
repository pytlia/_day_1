#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>

std::tuple<std::vector<int>, std::vector<int>> prochytaemo_spysok_locationsiv() {
    auto pershyi_spysok { std::vector<int>() }, drugyi_spysok { std::vector<int>() };
    
    std::ifstream fin("locationsy.txt", std::ifstream::in);
    while (!fin.eof()) {
        int pershyi_locations{ -1 }, drugyi_locations{ -1 };
        fin >> pershyi_locations >> drugyi_locations;

        pershyi_spysok.push_back(pershyi_locations);
        drugyi_spysok.push_back(drugyi_locations);
    }
    fin.close();

    return  { pershyi_spysok, drugyi_spysok };
}


void posortuemo_locationsy_po_poryadochku(std::vector<int>& spysok_locationsiv) {
    std::sort(spysok_locationsiv.begin(), spysok_locationsiv.end(), std::less<int>());
}

int poshukaem_distancy_mizh_locationsamy(const std::vector<int>& pershyi_spysok_locationsiv, const std::vector<int>& drugyi_spysok_locationsiv) {
    int yak_daleko_toi_tip_zabig_po_locationsah{ 0 };

    for (int i{ 0 }; i < pershyi_spysok_locationsiv.size() && i < drugyi_spysok_locationsiv.size(); i++) {
        int distanciya_mizh_locationsamy = std::abs(pershyi_spysok_locationsiv.at(i) - drugyi_spysok_locationsiv.at(i));
        yak_daleko_toi_tip_zabig_po_locationsah += distanciya_mizh_locationsamy;
    }

    return yak_daleko_toi_tip_zabig_po_locationsah;
}


std::vector<std::tuple<int, int>> namutym_spisok_similyaritiv(const std::vector<int>& drugyi_spysok_locationsiv) {
    std::vector<std::tuple<int, int>> spisok_similyaritiv{ std::vector<std::tuple<int, int>>() };

    for (auto locations : drugyi_spysok_locationsiv) {
        auto znaishovsya_iterator = std::find_if(spisok_similyaritiv.begin(), spisok_similyaritiv.end(), [&locations] (const std::tuple<int, int>& similyar) {return std::get<0>(similyar) == locations;});
        if (znaishovsya_iterator != spisok_similyaritiv.end()) {
            std::get<1>(*znaishovsya_iterator)++;
            continue;
        }
            
        spisok_similyaritiv.push_back(std::make_tuple(locations, 1));
    }

    return spisok_similyaritiv;
}


int nu_a_teper_znaidem_zagalnyi_similyariti_scor(const std::vector<int>& pershyi_spysok_locationsiv, std::vector<std::tuple<int, int>> spisok_similyaritiv) {
    int similyariti_scor{ 0 };

    for (auto locations : pershyi_spysok_locationsiv) {
        auto znaishovsya_iterator = std::find_if(spisok_similyaritiv.begin(), spisok_similyaritiv.end(), [&locations] (const std::tuple<int, int>& similyar) {return std::get<0>(similyar) == locations;});
        if (znaishovsya_iterator != spisok_similyaritiv.end())
            similyariti_scor += locations * std::get<1>(*znaishovsya_iterator);
    }

    return similyariti_scor;
}


void nu_davaite_podyvymos_sho_tam(const int& vyvodym_otse, const std::string& vyvodym_suda) {
    std::ofstream fout(vyvodym_suda, std::ofstream::out);
    fout << vyvodym_otse << std::endl;
}


int main() {
    auto [pershyi_spysok_locationsiv, drugyi_spysok_locationsiv] = prochytaemo_spysok_locationsiv(); 

    posortuemo_locationsy_po_poryadochku(pershyi_spysok_locationsiv);
    posortuemo_locationsy_po_poryadochku(drugyi_spysok_locationsiv);

    // part 1
    int yak_daleko_toi_tip_zabig_po_locationsah = poshukaem_distancy_mizh_locationsamy(pershyi_spysok_locationsiv, drugyi_spysok_locationsiv);
    nu_davaite_podyvymos_sho_tam(yak_daleko_toi_tip_zabig_po_locationsah, "sho_po_distansah (_part_1_).txt");
    // end part 1

    // part 2
    std::vector<std::tuple<int, int>> spisok_similyaritiv = namutym_spisok_similyaritiv(drugyi_spysok_locationsiv);
    int similyariti_scor = nu_a_teper_znaidem_zagalnyi_similyariti_scor(pershyi_spysok_locationsiv, spisok_similyaritiv);
    nu_davaite_podyvymos_sho_tam(similyariti_scor, "sho_po_similyariti (_part_2_).txt");
    // end part 2

    return 0;
}