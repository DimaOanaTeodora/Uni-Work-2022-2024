package com.awbd.lab1b;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

@Component("myBooksSubscription")
public class BooksSubscription implements Subscription {

    DiscountCalculator discountCalculator;

    public double getPrice() {
        return discountCalculator.calculate(450);
    }

    public String getDescription() {
        return "yearly payment plan";
    }


    public BooksSubscription() {
    }

    @Autowired
    public BooksSubscription(@Qualifier("discountCalculatorImpl") DiscountCalculator discountCalculator) {

        this.discountCalculator = discountCalculator;
    }


}
