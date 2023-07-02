package com.awbd.lab1;

public class DiscountCalculatorImpl implements DiscountCalculator{

    double percent;

    public void setPercent(double percent) {
        this.percent = percent;
    }

    public double calculate(int price) {
        return price * (1- percent);
    }
}
