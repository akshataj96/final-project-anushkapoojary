#include <map>
#include <vector>
#include <unordered_set>
#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

// STEP 1: Test Autocomplete function : TESTED AND VERIFIED
TEST(TrojanMapStudentTest, Autocomplete) {
  TrojanMap TM;
  TM.CreateGraphFromCSVFile();
  // Test the simple case
  auto names = TM.Autocomplete("An");
  std::unordered_set<std::string> gt1 = {"Anna39s Store"};
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt1.count(n) > 0, true);
    if (gt1.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt1.size());
  // Test the lower case
  names = TM.Autocomplete("div");
  std::unordered_set<std::string> gt2 = {"Divine Providence Kindergarten and Day Nursery","Divine Providence Convent"}; 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt2.count(n) > 0, true);
    if (gt2.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt2.size());
  // Test the lower and upper case 
  names = TM.Autocomplete("uSc"); 
  std::unordered_set<std::string> gt3 = {"USC Village Dining Hall","USC Parking","USC Village Gym","USC Fisher Museum of Art"}; 
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt3.count(n) > 0, true);
    if (gt3.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt3.size());
}


// STEP 2 : Test FindPosition function : TESTED AND VERIFIED
TEST(TrojanMapStudentTest, FindPosition) {
  TrojanMap TM;
  TM.CreateGraphFromCSVFile();
  //Test FaceHaus
  auto position = TM.GetPosition("FaceHaus");
  std::pair<double, double> gt1(34.0247014,-118.2844289);
  EXPECT_EQ(position, gt1);
  // Test Baked Bear
  position = TM.GetPosition("Baked Bear");
  std::pair<double, double> gt2(34.0249743,-118.2852124);
  EXPECT_EQ(position, gt2);
  // Test USC Fisher Museum of Art
  position = TM.GetPosition("USC Fisher Museum of Art");
  std::pair<double, double> gt3(34.0186092,-118.2873476);
  EXPECT_EQ(position, gt3);
  // Test Unknown
  position = TM.GetPosition("RandomLocation");
  std::pair<double, double> gt4(-1, -1);
  EXPECT_EQ(position, gt4);
}

//STEP 3: TESTED AND VERIFIED

// Test 1 : CalculateShortestPath_Dijkstra function 
TEST(TrojanMapStudentTest, CalculateShortestPath_Dijkstra1) {
  TrojanMap TM;
  TM.CreateGraphFromCSVFile();
  auto path = TM.CalculateShortestPath_Bellman_Ford("Target", "Ralphs");
  // Test from Target to Ralphs
  std::vector<std::string> gt{"5237417650","6813379479","4015372485","7071032399","4015372486",
                              "6813405232","122719216","6813405231","2613117893","122719255",
                              "441895335","441895337","213332111","6807243576","6807243574",
                              "122719259","2613117895","123178876","6816193783","6389467806",
                              "6816193784","6813405269","6816831441","6808093919","6808093913",
                              "6808093910","6787470571","5559640911","2578244375"}; // Expected path

  // Print the path lengths
  std::cout << "My path length: "  << TM.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << TM.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Target
  path = TM.CalculateShortestPath_Dijkstra("Ralphs", "Target");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << TM.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << TM.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

//STEP 3: Test 2
TEST(TrojanMapStudentTest, CalculateShortestPath_Dijkstra2) {
  TrojanMap TM;
  TM.CreateGraphFromCSVFile();
  auto path = TM.CalculateShortestPath_Bellman_Ford("Korean Presbyterian Church", "Subway");
  // Test from Korean Presbyterian Church to Subway
  std::vector<std::string> gt{"358850006","6814958417","6807295173","6807295178","7537074279","6818427951",
                              "63068532","6818427947","6813405224","7385039432","6816193787","6813405223",
                              "4015423968","6389467808","21098539","6389467809","4015203132","3195897587",
                              "4015203128","4015203123","1878000351","6814958436","4015203121","4015203120",
                              "4872897506","6814958395","544672064","6814958399","4015203116","4015203113",
                              "4015203110","123152312","6814955793","4015372472","4015372470","4015372465",
                              "4015372464","2613159968","6813379562","63068674","2193439972","2193439967",
                              "6792034225","123112726","6813379571","7023424984","123112725","4015405540",
                              "213431695","7023430193","213431822","7023424981","441891112","932401855",
                              "4015405541","6820935897","1781230449","4015405542","4015405543","1837212104",
                              "1837212107","2753199985","6820935907","1837212100","4015372458","6813411588",
                              "1837212101","6820935911","932416162","4060015482","4020099365","6820972450",
                              "1732243549","6820972451","122436252","1836105028","4060015481","4020099358",
                              "6814990127","7867091027","7867091030","6226313827","932378219","6814990112",
                              "1870795293","6814990128","4060015480","1870795287","4020099348","1870795282",
                              "1870787389","1870795272","1870795261","1870795259","1855150081","1759017530"}; // Expected path

  // Print the path lengths
  std::cout << "My path length: "  << TM.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << TM.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Ralphs to Target
  path = TM.CalculateShortestPath_Dijkstra("Subway", "Korean Presbyterian Church");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << TM.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << TM.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

//step 4: tsp

// STEP 5: Test cycle detection function - MAP NOT WORKING HENCE CANNOT TEST
// TEST(TrojanMapTest, CycleDetection) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   // Test case 1
//   std::vector<double> square1 = {-118.230,-118.26011, 34.02511233, 34.01962235};
//   bool result1 = m.CycleDetection(square1);
//   EXPECT_EQ(result1, false);

//   // Test case 2
//   std::vector<double> square2 = {118.243333, -118.263322, 34.0113222, 34.019474};
//   bool result2 = m.CycleDetection(square2);
//   EXPECT_EQ(result2, false);

//     // Test case 3
//   std::vector<double> square3 = {-118.297, -118.263, 34.03, 34.01};
//   bool result3 = m.CycleDetection(square3);
//   EXPECT_EQ(result3, true);

//     // Test case 4
//   std::vector<double> square4 = {-118.28, -118.265, 34.031, 34.012};
//   bool result4 = m.CycleDetection(square4);
//   EXPECT_EQ(result4, true);
// }


//STEP 6 : Test cycle detection function - THIS WORKS AND VERIFIED
TEST(TrojanMapStudentTest, TopologicalSort) {
  TrojanMap TM;
  TM.CreateGraphFromCSVFile();

  //TEST 1 : Direct Read
  std::vector<std::string> location_names = {"BBCM", "FaceHaus","Ground Zero",};
  std::vector<std::vector<std::string>> dependencies = {{"FaceHaus","Ground Zero"}, {"FaceHaus","BBCM"}, {"Ground Zero","BBCM"}};
  auto result1 = TM.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt1 ={"FaceHaus","Ground Zero","BBCM"};
  EXPECT_EQ(result1, gt1);

  //TEST 2 : Reading from CSV file
  std::string locations_filename = "/home/anushkapoojary/final-project-anushkapoojary/input/topologicalsort_locations.csv";
  std::string dependencies_filename ="/home/anushkapoojary/final-project-anushkapoojary/input/topologicalsort_dependencies.csv";
  location_names = TM.ReadLocationsFromCSVFile(locations_filename);
  dependencies = TM.ReadDependenciesFromCSVFile(dependencies_filename);
  auto result2 = TM.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt2 ={"CVS","Cardinal Gardens","Ralphs","Coffee Bean1",};
  EXPECT_EQ(result2, gt2);
  

 //TEST 3 : Reading from CSV file
  std::string locations_filename_2 = "/home/anushkapoojary/final-project-anushkapoojary/input/LOC2.csv";
  std::string dependencies_filename_2 = "/home/anushkapoojary/final-project-anushkapoojary/input/DEP2.csv";
  location_names = TM.ReadLocationsFromCSVFile(locations_filename_2);
  dependencies = TM.ReadDependenciesFromCSVFile(dependencies_filename_2);
  auto result3 = TM.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt3 ={"Wahlburgers", "The Pearl", "Target", "Dulce", "FaceHaus"};
  EXPECT_EQ(result3, gt3);

}

//step 7
