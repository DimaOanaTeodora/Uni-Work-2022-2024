package com.awbd.lab1b;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@Component
public class DiscountCalculatorImpl implements DiscountCalculator {

    @Value("${discount.percent}")
    double percent;


    public void setPercent(double percent) {
        this.percent = percent;
    }

    public double calculate(int price) {
        return price * (1- percent);
    }
}
