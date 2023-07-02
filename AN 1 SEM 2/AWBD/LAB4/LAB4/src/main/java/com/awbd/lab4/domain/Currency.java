package com.awbd.lab4.domain;

public enum Currency {
    USD("USD $"), EUR("EUR \u20ac"), GBP("GBP \u00a3");

    private String description;

    public String getDescription() {
        return description;
    }

    Currency(String description) {
        this.description = description;
    }
}
