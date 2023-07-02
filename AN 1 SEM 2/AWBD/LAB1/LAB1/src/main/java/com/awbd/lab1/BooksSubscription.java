package com.awbd.lab1;




public class BooksSubscription implements Subscription{

    DiscountCalculator discountCalculator;

    public double getPrice() {
        return discountCalculator.calculate(450);
    }

    public String getDescription() {
        return "yearly payment plan";
    }

    public BooksSubscription() {
    }

    public BooksSubscription(DiscountCalculator discountCalculator) {

        this.discountCalculator = discountCalculator;
    }


}
