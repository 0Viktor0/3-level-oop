#include <QCoreApplication>
#include <QMainWindow>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <QApplication>


using namespace std;



double f(double x){
    return exp(x) + log(x) - 10 * x;
}

double pf(double x){
    return exp(x) + 1/x - 10;
}

double findroot(double a, double b, double eps){
    double x0 = (a + b) / 2;
    double x1 = x0 - f(x0) / pf(x0);
    while (fabs(x1 - x0) > eps) {
        x0 = x1;
        x1 = x0 - f(x0) / pf(x0);
    }
    return x1;
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    QWidget *centralWidget = new QWidget(&window);
    QFormLayout *formLayout = new QFormLayout(centralWidget);
    QLabel *aLabel = new QLabel("a:");
    QLineEdit *aLineEdit = new QLineEdit;
    QLabel *bLabel = new QLabel("b:");
    QLineEdit *bLineEdit = new QLineEdit;
    QLabel *epsLabel = new QLabel("Epsilon:");
    QLineEdit *epsLineEdit = new QLineEdit;
    QPushButton *calculateButton = new QPushButton("Calculate");
    QLabel *rootLabel = new QLabel;
    QLabel *fRootLabel = new QLabel;
    formLayout->addRow(aLabel, aLineEdit);
    formLayout->addRow(bLabel, bLineEdit);
    formLayout->addRow(epsLabel, epsLineEdit);
    formLayout->addRow(calculateButton);
    formLayout->addRow(rootLabel);
    formLayout->addRow(fRootLabel);
    QObject::connect(calculateButton, &QPushButton::clicked, [&]() {
        double a = aLineEdit->text().toDouble();
        double b = bLineEdit->text().toDouble();
        double eps = epsLineEdit->text().toDouble();
        double root = findroot(a, b, eps);
        std::ostringstream oss;  // Create a stringstream object
        oss << std::fixed << std::setprecision(5) << f(root);  // Format f(root) with precision 5
        std::string formattedResult = oss.str();
        rootLabel->setText("x: " + QString::number(root));
        fRootLabel->setText("f(x): " + QString::fromStdString(formattedResult));
    });
    window.setCentralWidget(centralWidget);
    window.show();
    return a.exec();
}
