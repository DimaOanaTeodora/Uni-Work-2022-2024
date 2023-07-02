package com.awbd.lab1b;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

@Component("mySportSubscription")
public class SportSubscription implements Subscription {

    @Autowired
    DiscountCalculator discountCalculator;

    public double getPrice() {
        return discountCalculator.calculate(1000);
    }

    public String getDescription() {
        return "go practice";
    }
}
