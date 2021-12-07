#include "trojanmap.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<iomanip>

#include <algorithm>
#include <sstream>
#include <fstream>
#include <locale>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <cctype>
#include <unordered_set>
#include <stack>
#include <chrono>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

//-----------------------------------------------------
// TODO (Students): You do not and should not change the following functions:
//-----------------------------------------------------

/**
 * PrintMenu: Create the menu
 * 
 */
void TrojanMap::PrintMenu() {

  std::string menu =
      "**************************************************************\n"
      "* Select the function you want to execute.                    \n"
      "* 1. Autocomplete                                             \n"
      "* 2. Find the position                                        \n"
      "* 3. CalculateShortestPath                                    \n"
      "* 4. Travelling salesman problem                              \n"
      "* 5. Cycle Detection                                          \n"
      "* 6. Topological Sort                                         \n"
      "* 7. Find K Closest Points                                    \n"
      "* 8. Exit                                                     \n"
      "**************************************************************\n";
  std::cout << menu << std::endl;
  std::string input;
  getline(std::cin, input);
  char number = input[0];
  switch (number)
  {
  case '1':
  {
    menu =
        "**************************************************************\n"
        "* 1. Autocomplete                                             \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a partial location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = Autocomplete(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '2':
  {
    menu =
        "**************************************************************\n"
        "* 2. Find the position                                        \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = GetPosition(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.first != -1) {
      std::cout << "Latitude: " <<results.first
                << " Longitude: " << results.second << std::endl;
      //std::cout << "Latitude: " << std::setprecision(10)<<results.first
                //<< " Longitude: " << std::setprecision(10)<< results.second << std::endl;
      PlotPoint(results.first, results.second);
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '3':
  {
    menu =
        "**************************************************************\n"
        "* 3. CalculateShortestPath                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the start location:";
    std::cout << menu;
    std::string input1;
    getline(std::cin, input1);
    menu = "Please input the destination:";
    std::cout << menu;
    std::string input2;
    getline(std::cin, input2);
    auto start = std::chrono::high_resolution_clock::now();
    //auto results = CalculateShortestPath_Bellman_Ford(input1, input2);
    auto results = CalculateShortestPath_Dijkstra(input1, input2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
      std::cout << "The distance of the path is:" << CalculatePathLength(results) << " miles" << std::endl;
      PlotPath(results);
    } else {
      std::cout << "No route from the start point to the destination."
                << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '4':
  {
    menu =
        "**************************************************************\n"
        "* 4. Traveling salesman problem                              \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.";
    std::cout << menu << std::endl << std::endl;
    menu = "Please input the number of the places:";
    std::cout << menu;
    getline(std::cin, input);
    int num = std::stoi(input);
    std::vector<std::string> keys;
    for (auto x : data) {
      keys.push_back(x.first);
    }
    std::vector<std::string> locations;
    srand(time(NULL));
    for (int i = 0; i < num; i++)
      locations.push_back(keys[rand() % keys.size()]);
    PlotPoints(locations);
    std::cout << "Calculating ..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    auto results = TravellingTrojan(locations);
    //auto results = TravellingTrojan_2opt(locations);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    CreateAnimation(results.second);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.second.size() != 0) {
      for (auto x : results.second[results.second.size()-1]) std::cout << x << std::endl;
      menu = "**************************************************************\n";
      std::cout << menu;
      std::cout << "The distance of the path is:" << results.first << " miles" << std::endl;
      PlotPath(results.second[results.second.size()-1]);
    } else {
      std::cout << "The size of the path is 0" << std::endl;
    }
    menu = "**************************************************************\n"
           "You could find your animation at src/lib/output.avi.          \n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '5':
  {
    menu =
        "**************************************************************\n"
        "* 5. Cycle Detection                                          \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the left bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    std::vector<double> square;
    square.push_back(atof(input.c_str()));

    menu = "Please input the right bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the upper bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the lower bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    auto start = std::chrono::high_resolution_clock::now();
    auto results = CycleDetection(square);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results == true)
      std::cout << "there exists cycle in the subgraph " << std::endl;
    else
      std::cout << "there exist no cycle in the subgraph " << std::endl;
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '6':
  {
    menu =
        "**************************************************************\n"
        "* 6. Topological Sort                                         \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the locations filename:";
    std::cout << menu;
    std::string locations_filename;
    getline(std::cin, locations_filename);
    menu = "Please input the dependencies filename:";
    std::cout << menu;
    std::string dependencies_filename;
    getline(std::cin, dependencies_filename);
    
    // Read location names from CSV file
    std::vector<std::string> location_names;
    if (locations_filename == "") 
      location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    else
      location_names = ReadLocationsFromCSVFile(locations_filename);
    
    // Read dependencies from CSV file
    std::vector<std::vector<std::string>> dependencies;
    if (dependencies_filename == "")
      dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
    else
      dependencies = ReadDependenciesFromCSVFile(dependencies_filename);
    auto start = std::chrono::high_resolution_clock::now();
    auto result = DeliveringTrojan(location_names, dependencies);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Topological Sorting Results:" << std::endl;
    for (auto x : result) std::cout << x << std::endl;
    std::vector<std::string> node_ids;
    for (auto x: result) {
      std::string id = GetID(x);
      node_ids.push_back(id);
    }
    PlotPointsOrder(node_ids);
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
    case '7':
  {
    menu =
        "**************************************************************\n"
        "* 7. Find K Closest Points                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    
    menu = "Please input the locations:";
    std::cout << menu;
    std::string origin;
    getline(std::cin, origin);
    menu = "Please input k:";
    std::cout << menu;
    getline(std::cin, input);
    int k = std::stoi(input);
    
    auto start = std::chrono::high_resolution_clock::now();
    auto result = FindKClosestPoints(origin, k);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Find K Closest Points Results:" << std::endl;
    int cnt = 1;
    for (auto x : result) { 
      std::cout << cnt << " " << data[x].name << std::endl;
      cnt++;
    }
    PlotPointsLabel(result, GetID(origin));
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '8':
    break;
  default:
  {
    std::cout << "Please select 1 - 8." << std::endl;
    PrintMenu();
    break;
  }
  }
}


/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * 
 */
void TrojanMap::CreateGraphFromCSVFile() {
  std::fstream fin;
  fin.open("src/lib/map.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '['), word.end());
      word.erase(std::remove(word.begin(), word.end(), ']'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}

/**
 * PlotPoint: Given a location id, plot the point on the map
 * 
 * @param  {std::string} id : location id
 */
void TrojanMap::PlotPoint(std::string id) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(data[id].lat, data[id].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}
/**
 * PlotPoint: Given a lat and a lon, plot the point on the map
 * 
 * @param  {double} lat : latitude
 * @param  {double} lon : longitude
 */
void TrojanMap::PlotPoint(double lat, double lon) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(lat, lon);
  cv::circle(img, cv::Point(int(result.first), int(result.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPath: Given a vector of location ids draws the path (connects the points)
 * 
 * @param  {std::vector<std::string>} location_ids : path
 */
void TrojanMap::PlotPath(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::line(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPoints(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points inside square
 * @param  {std::vector<double>} square : boundary
 */
void TrojanMap::PlotPointsandEdges(std::vector<std::string> &location_ids, std::vector<double> &square) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto upperleft = GetPlotLocation(square[2], square[0]);
  auto lowerright = GetPlotLocation(square[3], square[1]);
  cv::Point pt1(int(upperleft.first), int(upperleft.second));
  cv::Point pt2(int(lowerright.first), int(lowerright.second));
  cv::rectangle(img, pt2, pt1, cv::Scalar(0, 0, 255));
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    for(auto y : data[x].neighbors) {
      auto start = GetPlotLocation(data[x].lat, data[x].lon);
      auto end = GetPlotLocation(data[y].lat, data[y].lon);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPointsOrder: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsOrder(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::putText(img, data[x].name, cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
  }
  // Plot dots and lines
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::arrowedLine(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsLabel(std::vector<std::string> &location_ids, std::string origin) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  int cnt = 1;
  auto result = GetPlotLocation(data[origin].lat, data[origin].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 255, 0), cv::FILLED);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::putText(img, std::to_string(cnt), cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
    cnt++;
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * CreateAnimation: Create the videos of the progress to get the path
 * 
 * @param  {std::vector<std::vector<std::string>>} path_progress : the progress to get the path
 */
void TrojanMap::CreateAnimation(std::vector<std::vector<std::string>> path_progress){
  cv::VideoWriter video("src/lib/output.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(1248,992));
  for(auto location_ids: path_progress) {
    std::string image_path = cv::samples::findFile("src/lib/input.jpg");
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
    cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
              cv::Scalar(0, 0, 255), cv::FILLED);
    for (auto i = 1; i < location_ids.size(); i++) {
      auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
      auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
      cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
                cv::Scalar(0, 0, 255), cv::FILLED);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
    video.write(img);
    cv::imshow("TrojanMap", img);
    cv::waitKey(1);
  }
	video.release();
}
/**
 * GetPlotLocation: Transform the location to the position on the map
 * 
 * @param  {double} lat         : latitude 
 * @param  {double} lon         : longitude
 * @return {std::pair<double, double>}  : position on the map
 */
std::pair<double, double> TrojanMap::GetPlotLocation(double lat, double lon) {
  std::pair<double, double> bottomLeft(34.01001, -118.30000);
  std::pair<double, double> upperRight(34.03302, -118.26502);
  double h = upperRight.first - bottomLeft.first;
  double w = upperRight.second - bottomLeft.second;
  std::pair<double, double> result((lon - bottomLeft.second) / w * 1248,
                                   (1 - (lat - bottomLeft.first) / h) * 992);
  return result;
}

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(std::string id) {
    return data[id].lat;
}


/**
 * GetLon: Get the longitude of a Node given its id. 
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(std::string id) { 
    return data[id].lon;
}

/**
 * GetName: Get the name of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(std::string id) { 
    return data[id].name;
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(std::string id) {
    return data[id].neighbors;
}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id, const std::string &b_id) {
  // Do not change this function
  // TODO: Use Haversine Formula:
  // dlon = lon2 - lon1;
  // dlat = lat2 - lat1;
  // a = (sin(dlat / 2)) ^ 2 + cos(lat1) * cos(lat2) * (sin(dlon / 2)) ^ 2;
  // c = 2 * arcsin(min(1, sqrt(a)));
  // distances = 3961 * c;

  // where 3961 is the approximate radius of the earth at the latitude of
  // Washington, D.C., in miles
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0;i < path.size()-1; i++) {
    sum += CalculateDistance(path[i], path[i+1]);
  }
  return sum;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
 std::vector<std::string> results;
  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  std::string present_name;
  for (auto pn : data) { 
    present_name = pn.second.name;
    std::transform(present_name.begin(), present_name.end(), present_name.begin(), ::tolower);
      if (name == present_name.substr(0, name.size())) {
        results.push_back(pn.second.name);
      }
  }
   return results;
}

/**
 * GetPosition: Given a location name, return the position.
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> results(-1, -1);
  std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  for (auto pn : data) { 
    std::string name_in_node = pn.second.name;
    std::transform(name_in_node.begin(), name_in_node.end(), name_in_node.begin(), ::tolower);
    if (name == name_in_node) { 
      results.first = GetLat(pn.first);
      results.second = GetLon(pn.first);
      break;
    }
  }
  return results;
}

/**
 * GetID: Given a location name, return the id. 
 * If the node does not exist, return an empty string. 
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(std::string name) {
  std::string res = "";
   std::transform(name.begin(), name.end(), name.begin(), ::tolower);
  for(const auto &node: this->data){
    std::string name_in_node = node.second.name;
    std::transform(name_in_node.begin(), name_in_node.end(), name_in_node.begin(), ::tolower);
    if(name_in_node==name){
      res=node.second.id;
      return res;
    }
  }
  std::cout<<"Node not found\n";
  return res;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(std::string location1_name, std::string location2_name) {
  std::string starting_location, finishing_location; 
  std::vector<std::string> path;
  std::map<const Node*, double> distance_start_to_present;
  std::map<const Node*, std::string> start; 
  std::map<const Node*, bool> visited;
  
  for (auto it = data.begin(); it != data.end(); it++) {
    distance_start_to_present[&it->second] = std::numeric_limits<int>::max();
  }

  starting_location = GetID(location1_name);
  finishing_location = GetID(location2_name);
  
  auto relative_distance_from_start = [&distance_start_to_present](const Node *a, const Node *b) { 
    return distance_start_to_present[a] > distance_start_to_present[b];
  }; 
  std::priority_queue<const Node*, std::vector<const Node*>, decltype(relative_distance_from_start)> distances(relative_distance_from_start);
  const Node *curr_node = &data[starting_location]; 
  distance_start_to_present[curr_node] = 0; 
  distances.push(curr_node);
  while (!distances.empty()) { 
    curr_node = distances.top();
    distances.pop();  
    if (curr_node->id == finishing_location) { 
      std::string loc = finishing_location;
      while (loc != starting_location) { 
        path.insert(path.begin(), loc);
        loc = start[&data[loc]];
      }
      path.insert(path.begin(), starting_location);
      return path;
    }
    visited[curr_node] = true; 
    for (const std::string &neighbouring_node : curr_node->neighbors) { 
      Node *dest_node = &data[neighbouring_node]; 
      if (visited[dest_node]) { 
        continue; 
      }
      double weight = CalculateDistance(curr_node->id, dest_node->id); 
      if (distance_start_to_present[dest_node] > distance_start_to_present[curr_node] + weight) { 
        start[dest_node] = curr_node->id;
        distance_start_to_present[dest_node] = distance_start_to_present[curr_node] + weight;
        distances.push(dest_node); 
      }
    }
  }
  return path;
}
/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
 std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(std::string location1_name, std::string location2_name){
  std::string start = GetID(location1_name);
  std::string end = GetID(location2_name);
  std::vector<std::string> path;
  std::map<std::string , std::string> travesral_route;
  std::map<std::string , double> weight;
  std::map<std::string , std::vector<std::string>> neighbouring_loc;

  Node start_node = data[start];
  Node end_node = data[end];
  if(location1_name.length()==0 || location2_name.length()==0){
    return {};
  }
  for(auto loc: data){
    neighbouring_loc[loc.second.id] = loc.second.neighbors;
    weight[loc.second.id] = DBL_MAX;    
  }
  weight[start_node.id]=0;
  for(auto i=0; i < (data.size() - 1); i++){
    for(auto present_data: data) {
      for(auto present_neighbour: neighbouring_loc[present_data.second.id]){
        if((weight[present_data.second.id] + CalculateDistance(present_data.second.id , present_neighbour)) < weight[present_neighbour]){
          weight[present_neighbour] = weight[present_data.second.id] + CalculateDistance(present_data.second.id , present_neighbour);
          travesral_route[present_neighbour] = present_data.second.id;
        }
      }
    }
  }
  std::string temp = travesral_route[end_node.id];
  path.push_back(end_node.id);
  while(temp!=start_node.id){
    path.push_back(temp);
    temp = travesral_route[temp];
  }
  path.push_back(start_node.id);
  std::reverse(path.begin() , path.end());
  return path;
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan(
                                    std::vector<std::string> &location_ids) {
                                    
 std::pair<double, std::vector<std::vector<std::string>>> results;
 std::vector<std::string> vis = location_ids;
 std::vector<std::string> x;
  double min = INT_MAX;
  vis.erase(vis.begin());
  std::sort(vis.begin(), vis.end());
 /* do{
    double current = 0;
    current = CalculatePathLength(vis);
    if(current < min){
      min = current;
      results.first = min;
      results.second.push_back(vis);
    }
  }
  while(next_permutation(vis.begin(),vis.end()));
  //std::string source_id = results.second[results.second.size()-1][0];
  results.second[results.second.size() - 1].push_back(location_ids[0]);	
  return results;*/ 
  while(next_permutation(vis.begin(),vis.end())){
     double current = 0;
     std::string pres = location_ids.front();
     for(auto i:vis){
       current = current + CalculateDistance(pres,i);
       pres=i;
     }
     current = current + CalculateDistance(pres,location_ids.front());
     if(min>current){
       x.clear();
       x.push_back(location_ids[0]);
       for(auto u:vis) x.push_back(u);
       x.push_back(location_ids[0]);
       results.second.push_back(x);
     }
     min = std::min(min,current);
   }
   results.first = min;
   return results;
}                                 

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> &location_ids){

  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector<std::string> updated_loc_ids;
  double pathlength_updated;
  double len_new = INT_MAX;
  int i,j,k;

  for(i=0; i< location_ids.size()-1; i++){
    for(j=i+1; j<location_ids.size(); j++){
      for(k = 0; k < i; k++)
        updated_loc_ids.push_back(location_ids[k]);
      for (k = j; k >= i; k--)
        updated_loc_ids.push_back(location_ids[k]);
      for (k = j+1; k < location_ids.size(); k++)
        updated_loc_ids.push_back(location_ids[k]);

      pathlength_updated = CalculatePathLength(updated_loc_ids);
      if(pathlength_updated<len_new){
        len_new = pathlength_updated;
        results.first = len_new;
        results.second.push_back(updated_loc_ids);
      }
    }
  }
  int res_size = results.second.size();
  results.second[res_size - 1].push_back(results.second[res_size - 1][0]);
  return results;
}

//////////////////////////////////////////////////////////////////////////////////////

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations 
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;
  std::string line;
  std::ifstream fileIn;
  fileIn.open(locations_filename);
  while (std::getline(fileIn, line,'\n'))
   {std::stringstream ss(line);
        while(getline(ss, line, ',')){
     location_names_from_csv.push_back(line);}}
  location_names_from_csv.erase(location_names_from_csv.begin());

  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::vector <std::string> record;
  std::string line,str;
  std::ifstream infile;
  infile.open(dependencies_filename);

    //  Read the file    
    while (getline(infile, line)) 
    {   std::istringstream ss (line);
        while (getline(ss, str, ',')) 
            record.push_back(str);
    }
    record.erase(record.begin());

    int n = (record.size())/2;

    std::vector<std::vector<std::string>> dep_temp(n);
    for (int i = 0; i < n; i++) {
       std::vector<std::string> & inner_vector = dep_temp[i];
        for (int j = 0; j < 2; j++) {
            inner_vector.push_back(record[2 * i + j]);
        }
    }
  dependencies_from_csv = dep_temp;
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
// std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
//                                                      std::vector<std::vector<std::string>> &dependencies){
//   std::vector<std::string> result;

//   return result;  
//}

//////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
                                                     std::vector<std::vector<std::string>> &dependencies){
  std::vector<std::string> result;
  std::vector<std::string> temp;
  std::unordered_map<std::string,bool> visited;
  std::unordered_map<std::string, std::vector<std::string>> adj;

  for(auto &loc: locations)
    adj[loc]=temp;
  
  for(auto &dep:dependencies)
    adj[dep[0]].push_back(dep[1]);
  
  for(auto &n: locations)
    visited[n]=false;

  for(auto &i: locations){
    if(visited[i]==false)
      DeliveringTrojan_Helper(i, visited, adj, result);
  }
  std::reverse(result.begin(), result.end());
  return result;  
}

void TrojanMap::DeliveringTrojan_Helper(std::string &id, std::unordered_map<std::string, bool> &visited, std::unordered_map<std::string, std::vector<std::string> > &adj, std::vector<std::string> &result)
{
  visited[id]=true;
  std::vector<std::string>::iterator start_DT = adj[id].begin();
  std::vector<std::string>::iterator end_DT = adj[id].end();
  std::vector<std::string>::iterator IT;

  for(IT=start_DT;IT!=end_DT;++IT)
    if(!visited[*IT])
      DeliveringTrojan_Helper(*IT, visited, adj, result);

  result.push_back(id);
}

//////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
//  * @param {std::vector<double>} square: four vertexes of the square area
//  * @return {bool}: whether there is a cycle or not
//  */
bool TrojanMap::CycleDetection(std::vector<double> &square)
{ 
  std::map <std::string,bool> visited;
  std::vector <std::string>location_ids;
  std::map <std::string,std::vector<std::string>> preceeding_val;
  double lat, lon;
  bool cycle_detected = false;
  for (const auto &node: this->data)
  { lat = node.second.lat;
    lon = node.second.lon;
    
    if (((lon > square[0]) && (lon < square[1]))&&((lat < square[2]) && (lat > square[3]))){
	    preceeding_val.emplace(node.first,std::vector<std::string>());
      visited.emplace(node.second.id,false);
      location_ids.push_back(node.second.id);
    }
  }

  for(const auto &nv: visited){
    if(!nv.second)
      cycle_detected = hasCycle(nv.first, visited, preceeding_val, nv.first, square);
  }
  if(cycle_detected)
  PlotPointsandEdges(location_ids,square);

  return cycle_detected;
}

bool TrojanMap::hasCycle( std::string current_id, std::map<std::string, bool> &visited, std::map<std::string, std::vector<std::string> > &preceeding_val, std::string parent_id, std::vector<double> &square)
{ 
  visited[current_id] = true;
  bool res = false;
  Node CN = data[current_id];
  for (const auto &n: CN.neighbors){
    Node NB = data[n];
	
	if (!(((NB.lon > square[0]) && (NB.lon < square[1]))&&((NB.lat < square[2]) && (NB.lat > square[3]))))
      continue;
    preceeding_val[n].push_back(current_id);

  if (!visited[n])
    res= hasCycle(n, visited, preceeding_val, current_id, square);
    
  if (visited[n] && n != parent_id){
    res = true; }
  }
 
return res;
}

/**
 * FindKClosetPoints: Given a location id and k, find the k closest points on the map
 * 
 * @param {std::string} name: the name of the location
 * @param {int} k: number of closest points
 * @return {std::vector<std::string>}: k closest points
 */

bool TrojanMap::SortFunction(const std::pair<std::string,int> &a, const std::pair<std::string,int> &b){
    return (a.second < b.second);
    }


std::vector<std::string> TrojanMap::FindKClosestPoints(std::string name, int k) {
   
   std::vector<std::string> res;
   std::vector<std::string> des;
   
   std::map<double, std::vector<std::string>> dis_des;
   
   std::string Source_ID =GetID(name) ;
   
   for(auto pres=data.begin(); pres!=data.end(); pres++){
   	if(pres->first == Source_ID){
   		break;
   	}
   	dis_des[CalculateDistance(Source_ID,pres->first)].push_back(pres->first);
   }
   
   for(auto x=dis_des.begin(); x!=dis_des.end(); x++){
   	std::cout<<"printttttttt:"<<x->first<<std::endl;
   	if(res.size()>=k){
   		break;
   	}
   	for(std::string insert_loc: x->second){
   		if(res.size()>=k){
   		break;
   	}
   		if(data[insert_loc].name != ""){
   			res.push_back(insert_loc);
   		}
  	 }
   
    }
    
   return res;
  }


std::vector<std::string> TrojanMap::FindKClosestPoints(std::string name, int k) {
   
   std::vector<std::string> res;
   double distance_val;
   std::priority_queue<std::pair <double,std::string>> des_dis ;

  if(GetID(name)=="" ||k<=0)
   return res;
  
  //We want to skip any nodes that do not have names, hence the continue function
  for(auto i=data.begin();i!=data.end();i++){ 
    distance_val= CalculateDistance((*i).first,GetID(name));
	  
    if((*i).first ==GetID(name){
	    if((*i).second.name.size()==0))
		 continue;
    
    if (des_dis.size()<k)
     
     des_dis.push(std::make_pair(CalculateDistance((*i).first,GetID(name)),(*i).first));
     else{
       
       while(distance_val<des_dis.top().first){
         des_dis.push(std::make_pair(diss,(*i).first));
         des_dis.pop();
         
       }
     }
  }
  while(!des_dis.empty()){
  res.push_back(des_dis.top().second);
  des_dis.pop();}

  std::reverse(res.begin(),res.end());
  return res;
}
  
