#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <list>

#include "Vector.h"

using namespace std;

void foo( int& i)
{

}

int main()
{
    Vector<int> vs(5, 4);

    Vector<int>::iterator i;

//    vs.shrink_to_fit();

    Vector<string> tx;

    tx.push_back("txeynots");

  //  vs = tx;

    Vector<double> nx;

    try
    {
        cout << vs.at(5)<< endl << endl << endl << endl;
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }

    //  nx.test(nx.begin() + 5);

   // nx.erase(nx.begin() + 11);

    nx.push_back(65);
    nx.push_back(1);
    nx.push_back(2);
    nx.push_back(3);
    nx.pop_back();
    nx.push_back(4);
    nx.push_back(9);
    nx.push_back(5);
    nx.push_back(6);
    nx.push_back(3564);
    nx.push_back(564);
    nx.push_back(364);
    //nx.emplace_back(23, 45, 5,6);

    list<int> lis;


//    cout << *iter << endl << endl;

    Vector<int> xx(nx.cbegin(), nx.cend() );
    sort(xx.begin(), xx.end() );

   for(auto iter = xx.cbegin(); iter != xx.cend(); ++iter)
        cout << *iter << "  ";
    cout << endl;

    //nx.erase(nx.begin(), iter);


    try
    {
        //   nx.erase(iter);
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }

    //  nx.insert(iter, 8, 662);

    //for(auto iter = nx.cbegin(); iter != nx.cend(); ++iter)
        //cout << *iter << "  ";
    //cout << endl;

    cout << xx.capacity()<< endl;
    cout << xx.size()<< endl;
   // cout << endl << vs[2]<< endl;

    //cout << pow(2, 3) << endl;;

    cout << endl << "STL" << endl;

    vector<double> v, vc;

    //cout << endl << endl << "HH-> " << v[0] << endl;

    v.push_back(90);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    v.push_back(9);
    v.push_back(10);
    v.push_back(11);
    v.push_back(12);
    v.push_back(13);
    v.push_back(14);
    v.push_back(15);
    // v.push_back(16);
    v.push_back(345);

    v.front() = 5;

//   v.erase(v.begin() + 5);
vc = v;


    auto ite = v.begin();

    // cout << *ite << endl << endl;

      //v.insert(ite + 1, 10, 123);
    //  v.erase(ite);
    //  v.erase(ite);

  //  v.clear();

  v.resize(25, 3);

    try
    {
        cout << v.capacity()<< endl;

        cout << v.size()<< endl;

        cout << endl << v[15]<< endl;
        cout << endl << v.at(255)<< endl;

    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }
    //vc.insert(vc.begin(), nx.begin(), nx.begin() + 6);

    for(auto iter = vc.cbegin(); iter != vc.cend(); ++iter)
        cout << *iter << "  ";
    cout << endl;

    return 0;

}
