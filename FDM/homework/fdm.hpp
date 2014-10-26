#ifndef __FDM_HPP__
#define __FDM_HPP__

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

// �Ҷ���ͳ���ֵ�����ĺ���ָ������
// �����Ϊָ��  ���Կ��Ǻ������� 
typedef double (*SourceTerm)(double , double);
typedef double (*InitialBoundaryCond)(double);

class FDM {
public:
    FDM();
    FDM(double left, double right, double mu, SourceTerm sourceTerm);
    ~FDM();

    //void setMu(double mu);
    //void setLeft(double left);
    //void setRight(double right);
    void setLeftBoundaryCond(InitialBoundaryCond leftBoundaryCond);
    void setLeftNeumannCond(InitialBoundaryCond leftBoundaryCond);
    void setRightBoundaryCond(InitialBoundaryCond rightBoundaryCond);
    void setRightNeumannCond(InitialBoundaryCond rightBoundaryCond);
    void setInitialValueCond(InitialBoundaryCond initialValueCond);
    //void setSourceTerm(SourceTerm sourceTerm);
    void setFile(const char * fileName);
    void setParameter(int M, double stepT);
    void setNeumannOrder(int order);

    void initial(std::vector<double> &value);

    int solver_FTCS(std::vector<double> outputT);
    int FTCS_scheme(int n, std::vector<double> &uOld, std::vector<double> &uNew);
    
    void print(double currentTime, std::vector<double> &timeVect, std::vector<double> & u);
    bool isNeedStop(std::vector<double> & outTime);

    // ���Ĳ�ָ�ʽ  �� u �� �� k �� λ����������Ĳ��
    double centeredSecondDiff(std::vector<double> &u, int k);

private:
    double left_, right_; // [0, 1] [left, right];
    double mu_;
    InitialBoundaryCond leftBoundaryCond_; // a(t); leftBoundary
    InitialBoundaryCond leftNeumannCond_; // Ŧ���߽�����
    InitialBoundaryCond rightBoundaryCond_; // b(t); rightBoundary
    InitialBoundaryCond rightNeumannCond_;
    InitialBoundaryCond initialValueCond_;  // f(x);
    SourceTerm sourceTerm_;  // F(x, t); sourceTerm

    int M_;
    int neumannOrder_;
    double stepX_, stepT_;
    std::ofstream file_;
};

#endif
