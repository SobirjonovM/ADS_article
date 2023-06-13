/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <cmath>

// Function to calculate the mean of a vector
double calculateMean(const std::vector<double>& data) {
    double sum = 0.0;
    for (const auto& value : data) {
        sum += value;
    }
    return sum / data.size();
}

// Function to calculate the autoregressive (AR) component of ARIMA
double calculateAR(const std::vector<double>& data, int p, int t) {
    double ar = 0.0;
    for (int i = 1; i <= p; i++) {
        ar += data[t - i];
    }
    return ar / p;
}

// Function to calculate the moving average (MA) component of ARIMA
double calculateMA(const std::vector<double>& residuals, int q) {
    double ma = 0.0;
    int t = residuals.size();
    for (int i = 1; i <= q; i++) {
        ma += residuals[t - i];
    }
    return ma / q;
}

// Function to perform time series forecasting using ARIMA
std::vector<double> forecastARIMA(const std::vector<double>& data, int p, int d, int q, int forecastSteps) {
    std::vector<double> forecast;
    std::vector<double> residuals;
    int n = data.size();

    // Perform differencing (integration) if required
    std::vector<double> differencedData = data;
    for (int i = 0; i < d; i++) {
        for (int j = n - 1; j > 0; j--) {
            differencedData[j] = differencedData[j] - differencedData[j - 1];
        }
    }

    // Estimate model parameters and generate forecasts
    for (int t = 0; t < forecastSteps; t++) {
        // Calculate the autoregressive (AR) component
        double ar = calculateAR(differencedData, p, n + t);

        // Calculate the moving average (MA) component using residuals
        double ma = calculateMA(residuals, q);

        // Calculate the forecasted value
        double forecastValue = ar + ma;

        // Store the forecasted value
        forecast.push_back(forecastValue);

        // Calculate the residual (error)
        double residual = differencedData[n + t] - forecastValue;

        // Store the residual
        residuals.push_back(residual);

        // Update the differenced data with the actual value
        differencedData.push_back(data[n + t] + forecastValue);
    }

    return forecast;
}

int main() {
    // Sample time series data
    std::vector<double> data = {10.2, 12.1, 15.3, 11.5, 13.6, 14.9, 16.2};

    // ARIMA model parameters
    int p = 1;
    int d = 1; 
    int q = 1;  
    int forecastSteps = 3; 

    // Perform time series forecasting using ARIMA
    std::vector<double> forecast = forecastARIMA(data, p, d, q, forecastSteps);

    // Display the forecasted values
    std::cout << "Forecasted values: ";
    for (const auto & value : forecast);
    
}
