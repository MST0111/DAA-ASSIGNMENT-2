/**
 * @file seg.cpp
 * 
 * @brief This program implements a dynamic programming algorithm to find the best-fit line segments for given 2D points with minimum error. 
 */

#include <bits/stdc++.h>
#include <chrono>
#include"Point.hpp"
using namespace std;
/**
 * @brief Splits the given string into two integers, assuming a space between them
 * @param str The string to be split
 * @return The two integers as a pair of x and y coordinates
 */

Point splitstring(string str) {
  string s;
  Point ret;
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == ' ') {
      ret.first = stoi(s);
      s = "";
    } else {
      s += str[i];
    }
  }
  ret.second = stoi(s);
  return ret;
}

/**
 * @brief The main function to read input, calculate best-fit line segments, 
 *        and output the results.
 * @return 0 if the program executes successfully
 */

int main() {
  int N = 0, C, i, j, interval_len, x, y, k;

  string str;
  vector<Point> points;
  points.push_back({INT_MIN, INT_MIN});
  Point s;
  ifstream InputRead("input11.txt");
  while (getline(InputRead, str)) {
    s = splitstring(str);
    points.push_back(s);
    N++;
  }
  InputRead.close();

  cout << "Enter C: ";
  cin >> C;

  /**
   * Sorting the points on basis of x axis
   */
  sort(points.begin(), points.end());

  double slope[N + 1][N + 1], intercept[N + 1][N + 1], E[N + 1][N + 1] = {0};
  int cumx[N + 1], cumy[N + 1], cumxy[N + 1],cumxsqr[N + 1];  // cummulative arrays to store summation value
  cumx[0] = cumy[0] = cumxy[0] = cumxsqr[0] = 0;

  auto start_time = chrono::high_resolution_clock::now();
  
  /**
   * Finding error values for each segment
   */
  int x_seg_sum, y_seg_sum, xsqr_seg_sum;
  long long xy_seg_sum;
  for (j = 1; j <= N; j++) {
    cumx[j] = cumx[j - 1] + points[j].first;
    cumy[j] = cumy[j - 1] + points[j].second;
    cumxy[j] = cumxy[j - 1] + points[j].first * points[j].second;
    cumxsqr[j] = cumxsqr[j - 1] + points[j].first * points[j].first;
    for (i = 1; i <= j; i++) {
      x_seg_sum = cumx[j] - cumx[i - 1];
      y_seg_sum = cumy[j] - cumy[i - 1];
      xy_seg_sum = cumxy[j] - cumxy[i - 1];
      xsqr_seg_sum = cumxsqr[j] - cumxsqr[i - 1];
      int denominator = (j - i + 1) * xsqr_seg_sum - x_seg_sum * x_seg_sum;
      if (denominator == 0) {
        slope[i][j] = INT_MAX;  // infinity value
      } else {
        slope[i][j] = ((j - i + 1) * xy_seg_sum - x_seg_sum * y_seg_sum) /
                      (double(denominator));
      }
      intercept[i][j] =
          (y_seg_sum - slope[i][j] * x_seg_sum) / double((j - i + 1));
      for (k = i; k <= j; k++) {
        double error =
            points[k].second - (slope[i][j] * points[k].first +
                                intercept[i][j]);  //  y - yi  where yi = ax +b
        E[i][j] += error * error;
      }
    }
  }

  /**
   * Dynamic Programming to find the minimum cost
   */
  double OPT[N + 1];
  for (i = 1; i <= N; i++) {
    OPT[i] = INT_MAX;
  }
  OPT[0] = 0;
  int optimal_segment[N + 1];
  optimal_segment[0] = 0;
  int seg;
  for (j = 1; j <= N; j++) {
    double temp = INT_MAX;
    for (i = 1; i <= j; i++) {
      if (E[i][j] + C + OPT[i - 1] < temp) {
        temp = E[i][j] + C + OPT[i - 1];
        seg = i;
      }
    }
    optimal_segment[j] = seg;
    OPT[j] = temp;
  }
  auto end_time = chrono::high_resolution_clock::now();
  double elapsed_time = chrono::duration<double, std::milli>(end_time - start_time).count();
  /**
   * Printing points the line segment will cover and the error value
   */
  stack<int> temp_stack;
  for (i = N, j = optimal_segment[N]; i > 0;
       i = j - 1, j = optimal_segment[i]) {
    temp_stack.push(i);
    temp_stack.push(j);
  }
  int seg_count = 0;
  printf("\nAn optimal solution :\n");
  ofstream outfile;
  outfile.open("output.txt");
  while (!temp_stack.empty()) {
    seg_count++;
    i = temp_stack.top();
    temp_stack.pop();
    j = temp_stack.top();
    temp_stack.pop();

    string s = to_string(points[i].first) + " " + to_string(points[i].second) +
               ":" + to_string(points[j].first) + " " +
               to_string(points[j].second);
    outfile << s << endl;
    cout << "The line segment : y = " << slope[i][j] << "x + "
         << intercept[i][j] << " will cover points between " << '('
         << points[i].first << ',' << points[i].second << ')' << " to " << '('
         << points[j].first << ',' << points[j].second << ')' << endl;
    cout << "Error associated with above line segment is : " << E[i][j] << endl
         << endl;
  }

  /**
   * Printing Optimal Value
   */
  cout << "The optimal number of segments created : " << seg_count << endl;
  cout << "Optimal value is : " << OPT[N] << endl << endl;

  outfile << "#" << endl;
  outfile << OPT[N] << endl;
  outfile << elapsed_time<<endl;

  outfile.close();
  return 0;
}
