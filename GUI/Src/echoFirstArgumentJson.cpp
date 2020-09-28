// g++ write.cpp -o test

#include <iostream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

int main(int argc, char** argv)
{
    // cout << "Number of command line arguments (argc) entered: " << argc<<endl;

    // for (int i = 0; i < argc; ++i)
        // cout <<"argv["<<i<<"] : "<<argv[i] << "\n";
  string input = argv[1];
  string json_string = R"({"durations":[[0,5778.09,91041.77,401050.16],[5713.41,0,89194.74,399203.13],[90312.08,88381.13,0,313309.03],[400877.22,398946.28,312571.78,0]],"destinations":[{"location":[9.698609,48.477663],"snapped_distance":172.37},{"location":[9.207773,49.153882],"snapped_distance":10.54},{"location":[37.572926,55.80129],"snapped_distance":19.8},{"location":[115.665017,38.100717],"snapped_distance":648.79}],"sources":[{"location":[9.698609,48.477663],"snapped_distance":172.37},{"location":[9.207773,49.153882],"snapped_distance":10.54},{"location":[37.572926,55.80129],"snapped_distance":19.8},{"location":[115.665017,38.100717],"snapped_distance":648.79}],"metadata":{"attribution":"openrouteservice.org | OpenStreetMap contributors","service":"matrix","timestamp":1578220021234,"query":{"locations":[[9.70093,48.477473],[9.207916,49.153868],[37.573242,55.801281],[115.663757,38.106467]],"profile":"driving-car","responseType":"json"},"engine":{"version":"5.0.2","build_date":"2019-11-14T08:49:09Z"}}})";
  auto test = json::parse(json_string);
  auto testTab = test["durations"];
  // cout << testTab;
  for (int i = 0; i < testTab.size(); ++i) {
    // cout << i << endl;
    for (int j = 0; j<testTab[i].size(); ++j) {
      cout << testTab[i][j] << ",";
    }
    cout << "\r\n";
  }

  // cout << testTab[0][0] << endl;
  // auto const testTab = test.find("durations");

  // for (auto it = testTab.begin();it != testTab.end(); ++it)
  // {
  //   cout << (*it) << "TEST"<< endl;
  // }
  // for (auto const& line : testTab->items())
  // {
  //   cout << line << endl;
  // }

    return 0;
}
