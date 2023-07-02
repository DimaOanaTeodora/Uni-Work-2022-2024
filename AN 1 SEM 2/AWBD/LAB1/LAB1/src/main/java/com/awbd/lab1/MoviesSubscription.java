package com.awbd.lab1;




public class MoviesSubscription implements Subscription{
    DiscountCalculator discountCalculator;

    public void setDiscountCalculator(DiscountCalculator discountCalculator) {
        this.discountCalculator = discountCalculator;
    }

    public double getPrice() {
        return discountCalculator.calculate(100);
    }

    public String getDescription() {
        return "monthly payment plan";
    }
}


