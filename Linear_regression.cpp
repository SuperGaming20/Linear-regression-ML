// Coded by Dharrun Sriman (SuperGaming20), Do not take full credit for this program.
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cmath>
#include <ctime>
using namespace std;

inline int custom_sort(double a, double b)
{
  double a1 = abs(a-0);
  double b1 = abs(b-0);
  return a1<b1;
}

int train_test_split(int a[], int b[], int size ,int pred, int actual_size, int epn)
{
  int train1 = 0;
  int train2 = 0;
  int test1 = 0;
  int test2 = 0;
  int m = size;
  for(int i = 0; i < m;i++)
  {
    cout << "Train Data: " << a[i] << ' ' << b[i]<< endl;
    train1 += a[i];
    train2 += b[i];
  }
  for(int j = m; j < actual_size; j++)
  {
    cout << "Test Data: " << a[j] << ' ' << b[j] << endl;
    test1 += a[j];
    test2 += b[j];
  }
  // Size of XY
  float xs;
  for(int s = 0; s < m; s++)
  {
    xs += a[s] * b[s];
  }
  float xy = xs;

  // Sum of X^2
  float y0;
  for(int z = 0; z < m; z++)
  {
    y0 += a[z] * a[z];
  }
  float y3 = y0;

  // Y-intercept
  float a1 = train2  * y3;
  float a2 = train1 * xy;
  float a3 = a1 - a2;
  float a4 = m * y3;
  float a5 = a4 - (train1 * train1);
  float a0  =  a3/a5;
  //Slope
  float b1 = m * xy;
  float b2 = train1 * train2;
  float b3 = b1 - b2;
  float b4 = m * y3;
  float b5 = b4 - (train1 * train1);
  float b0 = b3/b5;

  float predval = a0 + b0 * pred;
  cout << "Prediction for number: " << pred << endl;
  cout << "Flat prediction: " << predval << endl;
  cout << "Floored prediction: " << floor(predval) << endl;
  //Gradient descent
  cout << "Running Gradient descent to find local minimum...." << endl;
  vector<double> error;
  double devi;
  string line = "-----------------------------------------------------------------";
  double alpha = 0.005;
  for (int epoch = 0; epoch < epn; epoch++) {
      int index = epoch % m;              // This accesses the index after each epoch
      double p = a0 + b0 * a[index];  // calculating prediction in total
      if(b[index] > p)
      {
        devi = b[index] - p;
      }
      else if(p >= b[index])
      {
        devi = p - b[index];
      }
      b0 = b0 - alpha * devi;
      a0 = a0 - alpha * devi * a[index];
      cout << line << endl;
      cout << "Y-intercept="<<a0<<" "<<"Slope="<<b0<<" "<<"error="<<devi<<endl;// printing values after every update
      cout << "Prediction rate: " << p << endl;
      cout << "Actual outcome: " << b[index] << endl;
      error.push_back(devi);
  }
  sort(error.begin(), error.end(), custom_sort);
  cout << line << endl;
  cout << "Optimal end values are: "<<"Slope: "<<b0<<" "<<"Y-intercept: "<<a0<<" "<<"error="<<error[0]<<endl;
  auto newval = a0 + b0 * pred;
  cout << "updated prediction: " << newval << endl;
  for(int testrun = size; testrun < actual_size; testrun++)
  {
    double testcheck = a0 + b0 * a[testrun];
    cout << line << endl;
    cout << "Test set error = " <<  b[testrun] - testcheck << endl;
    cout << "Prediction for the following test set = " <<  testcheck << endl;
    cout << "Actual test set number = " << b[testrun] << endl << line << endl;
  }
  return 0;
}

int main()
{
  int total[7] = {1,2,3,4,5,6,7}; // Train / test set X
  int value[7] = {12,23,36,48,53,70,86}; // Train / test set Y
  int prediction = 1; // number to predict
  int size = 5; // size to train/test model
  int as = sizeof(total)/sizeof(total[0]);
  train_test_split(total, value, size, prediction, as, 13);
}
