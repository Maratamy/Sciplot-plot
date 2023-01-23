#include "csv/single_include/csv.hpp"
#include <sciplot/sciplot.hpp>
#include <iostream>
#include <cstring>
#include "Eigen/Dense"


#include <algorithm>
#include <chrono>
#include <cmath>

using namespace std;
using namespace csv;
using Eigen::VectorXd;
using namespace sciplot;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

template <class Function>
int64_t time_call(Function&& f)
{
    auto begin = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    f();
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - begin;
}

void func(VectorXd xmaxmin, VectorXd ymax, VectorXd ymin, VectorXd ycenter, VectorXd x, VectorXd y, int wsize, int t1, int t2, int v_size)
{
    Plot2D plot1, plot2, plot3, plot4, plot5, plot6;
    plot1.size(wsize, 1080);
    plot1.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
    plot2.size(wsize, 1080);
    plot2.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
    plot3.size(wsize, 1080);
    plot3.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
    plot4.size(wsize, 1080);
    plot4.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
    plot5.size(wsize, 1080);
    plot5.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
    plot6.size(wsize, 1080);
    plot6.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);

    plot1.drawErrorBarsY(xmaxmin, ycenter, ymin, ymax).label("y(x)").lineWidth(1);

    double c = (double)(t1 + t2) / 2;
    int size, temp, i, count, a, b;
    
    a = (int)((c - 1) * 8000 / 400);
    b = (int)((c + 1) * 8000 / 400);
    if (a < 0) a = 0;
    if (b > v_size / 400) b = v_size / 400;
    size = (int)(b - a);
    VectorXd xmaxmin1(size), ymax1(size), ymin1(size), ycenter1(size);
    temp = 0;
    for (count = a; count < b; count++)
    {
        xmaxmin1(temp) = xmaxmin(count);
        ymax1(temp) = ymax(count);
        ymin1(temp) = ymin(count);
        ycenter1(temp) = ycenter(count);
        temp++;
    }
    plot2.drawErrorBarsY(xmaxmin1, ycenter1, ymin1, ymax1).label("y(x)").lineWidth(1);

    a = (int)((c - 0.5) * 8000 / 400);
    b = (int)((c + 0.5) * 8000 / 400);
    if (a < 0) a = 0;
    if (b > v_size / 400) b = v_size / 400;
    size = (int)(b - a);
    xmaxmin1.resize(size), ymax1.resize(size), ymin1.resize(size), ycenter1.resize(size);
    temp = 0;
    for (count = a; count < b; count++)
    {
        xmaxmin1(temp) = xmaxmin(count);
        ymax1(temp) = ymax(count);
        ymin1(temp) = ymin(count);
        ycenter1(temp) = ycenter(count);
        temp++;
    }
    plot3.drawErrorBarsY(xmaxmin1, ycenter1, ymin1, ymax1).label("y(x)").lineWidth(1);

    a = (int)((c - 0.1) * 8000 / 400);
    b = (int)((c + 0.1) * 8000 / 400);
    if (a < 0) a = 0;
    if (b > v_size / 400) b = v_size / 400;
    size = (int)(b - a);
    xmaxmin1.resize(size), ymax1.resize(size), ymin1.resize(size), ycenter1.resize(size);
    temp = 0;
    for (count = a; count < b; count++)
    {
        xmaxmin1(temp) = xmaxmin(count);
        ymax1(temp) = ymax(count);
        ymin1(temp) = ymin(count);
        ycenter1(temp) = ycenter(count);
        temp++;
    }
    plot4.drawErrorBarsY(xmaxmin1, ycenter1, ymin1, ymax1).label("y(x)").lineWidth(1);
    //
    a = ((c - 0.05) * 8000);
    b = ((c + 0.05) * 8000);
    if (a < 0) a = 0;
    if (b > v_size) b = v_size;
    size = (int)(b - a);
    xmaxmin1.resize(size), ymax1.resize(size), ymin1.resize(size), ycenter1.resize(size);
    temp = 0;
    for (count = a; count < b; count++)
    {
        xmaxmin1(temp) = x(count);
        ycenter1(temp) = y(count);
        temp++;
    }
    plot5.drawCurve(xmaxmin1, ycenter1).label("y(x)").lineWidth(1);
    a = ((c - 0.01) * 8000);
    b = ((c + 0.01) * 8000);
    if (a < 0) a = 0;
    if (b > v_size) b = v_size;
    size = (int)(b - a);
    xmaxmin1.resize(size), ymax1.resize(size), ymin1.resize(size), ycenter1.resize(size);
    temp = 0;
    for (count = a; count < b; count++)
    {
        xmaxmin1(temp) = x(count);
        ycenter1(temp) = y(count);
        temp++;
    }
    plot6.drawCurve(xmaxmin1, ycenter1).label("y(x)").lineWidth(1);
    //
    Figure figure = { {plot1,plot2,plot3,plot4,plot5,plot6} };
    Canvas canvas = { {figure} };
    canvas.size(1920, 1080);
    canvas.show();
    canvas.save("t1_t2.jpeg");
}

int main()
{
    string FileName = "data.csv";
    int i, count, v_size;
    i = 0;
    v_size = 400000;
    CSVReader reader(FileName);
    VectorXd vT(v_size), vx(v_size), vy(v_size);
    for (CSVRow& row : reader)
    {
        count = 0;
        for (CSVField& field : row)
        {
            if (count == 0) vT(i) = stod(field.get<>());
            if (count == 1) vx(i) = stod(field.get<>());
            if (count == 2) vy(i) = stod(field.get<>());
            count++;
        }
        i++;
    }

    VectorXd xmaxmin(v_size / 400), ymax(v_size / 400), ymin(v_size / 400), ycenter(v_size / 400);
    i = 0;
    count = 0;
    while (i < v_size)
    {
        xmaxmin(count) = vT(i + 200);
        ymax(count) = -1000;
        ymin(count) = 1000;
        for (int ii = 0; ii < 400; ii++)
        {
            if (vx(i) > ymax(count)) ymax(count) = vx(i);
            if (vx(i) < ymin(count)) ymin(count) = vx(i);
            i++;
        }
        ycenter(count) = (ymax(count) + ymin(count)) / 2;
        count++;
    }

    int t1, t2, wsize;
    do
    {
        cout << "Enter function argument bounds from 0 to 50" << endl;
        cin >> t1 >> t2;
    } while (t1 >= t2 || t1 < 0 || t2>50);
    cout << "Input size" << endl;
    cin >> wsize;

    auto time = time_call([&]
        {
            func(xmaxmin, ymax, ymin, ycenter, vT, vx, wsize, t1, t2, v_size);
        });
    cout << endl << "Elapsed time: " << time / 1000.0 << endl;

    return 0;
}